/*
 * Copyright 2003-2018 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_URI_SONG_FILTER_HXX
#define MPD_URI_SONG_FILTER_HXX

#include "ISongFilter.hxx"
#include "StringFilter.hxx"

class UriSongFilter final : public ISongFilter {
	StringFilter filter;

	bool negated;

	friend ISongFilterPtr OptimizeSongFilter(ISongFilterPtr) noexcept;

public:
	template<typename V>
	UriSongFilter(V &&_value, bool fold_case, bool _negated)
		:filter(std::forward<V>(_value), fold_case),
		 negated(_negated) {}

	const auto &GetValue() const noexcept {
		return filter.GetValue();
	}

	bool GetFoldCase() const {
		return filter.GetFoldCase();
	}

	bool IsNegated() const noexcept {
		return negated;
	}

	ISongFilterPtr Clone() const noexcept override {
		return std::make_unique<UriSongFilter>(*this);
	}

	std::string ToExpression() const noexcept override;
	bool Match(const LightSong &song) const noexcept override;
};

#endif

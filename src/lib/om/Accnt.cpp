/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <swirly/om/Accnt.hpp>

using namespace std;

namespace swirly {

Accnt::~Accnt() noexcept = default;

Accnt::Accnt(Accnt&&) = default;

PosnPtr Accnt::posn(Id64 marketId, Mnem contr, JDay settlDay) throw(bad_alloc)
{
  PosnSet::Iterator it;
  bool found;
  tie(it, found) = posns_.findHint(marketId);
  if (!found) {
    it = posns_.insertHint(it, Posn::make(marketId, contr, settlDay, mnem_));
  }
  return &*it;
}

} // swirly

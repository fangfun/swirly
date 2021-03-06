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
#include <swirly/fin/Market.hpp>

#include <swirly/util/Date.hpp>

#include <cassert>

using namespace std;

namespace swirly {
namespace {
template <typename FnT>
void toJsonLevels(LevelSet::ConstIterator it, LevelSet::ConstIterator end, ostream& os, FnT fn)
{
  for (size_t i{0}; i < MaxLevels; ++i) {
    if (i > 0) {
      os << ',';
    }
    if (it != end) {
      os << fn(*it);
      ++it;
    } else {
      os << "null";
    }
  }
}
} // anonymous

Market::~Market() noexcept = default;

Market::Market(Market&&) = default;

void Market::toJson(ostream& os) const
{
  os << "{\"id\":" << id_ //
     << ",\"contr\":\"" << contr_ //
     << "\",\"settlDate\":";
  if (settlDay_ != 0_jd) {
    os << jdToIso(settlDay_);
  } else {
    os << "null";
  }
  os << ",\"state\":" << state_;
  if (lastLots_ != 0_lts) {
    os << ",\"lastLots\":" << lastLots_ //
       << ",\"lastTicks\":" << lastTicks_ //
       << ",\"lastTime\":" << lastTime_;
  } else {
    os << ",\"lastLots\":null,\"lastTicks\":null,\"lastTime\":null";
  }

  const auto& bidLevels = bidSide_.levels();
  os << ",\"bidTicks\":[";
  toJsonLevels(bidLevels.begin(), bidLevels.end(), os,
               [](const auto& level) { return level.ticks(); });
  os << "],\"bidResd\":[";
  toJsonLevels(bidLevels.begin(), bidLevels.end(), os,
               [](const auto& level) { return level.resd(); });
  os << "],\"bidCount\":[";
  toJsonLevels(bidLevels.begin(), bidLevels.end(), os,
               [](const auto& level) { return level.count(); });

  const auto& offerLevels = offerSide_.levels();
  os << "],\"offerTicks\":[";
  toJsonLevels(offerLevels.begin(), offerLevels.end(), os,
               [](const auto& level) { return level.ticks(); });
  os << "],\"offerResd\":[";
  toJsonLevels(offerLevels.begin(), offerLevels.end(), os,
               [](const auto& level) { return level.resd(); });
  os << "],\"offerCount\":[";
  toJsonLevels(offerLevels.begin(), offerLevels.end(), os,
               [](const auto& level) { return level.count(); });
  os << "]}";
}

} // swirly

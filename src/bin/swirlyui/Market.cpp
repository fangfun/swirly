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
#include "Market.hpp"

#include <QJsonArray>
#include <QJsonObject>

using namespace std;

namespace swirly {
namespace ui {
namespace {

void toLevels(const QJsonArray& ticks, const QJsonArray& resd, const QJsonArray& count,
              Market::Levels& levels)
{
  for (size_t i{0}; i < MaxLevels; ++i) {
    levels[i] = {fromJson<Ticks>(ticks[i]), fromJson<Lots>(resd[i]), fromJson<int>(count[i])};
  }
}

} // anonymous

Market Market::fromJson(const Contr& contr, const QJsonObject& obj)
{
  using swirly::ui::fromJson;

  Market market{fromJson<Id64>(obj["id"]),           contr,
                fromJson<QDate>(obj["settlDate"]),   fromJson<MarketState>(obj["state"]),
                fromJson<Lots>(obj["lastLots"]),     fromJson<Ticks>(obj["lastTicks"]),
                fromJson<QDateTime>(obj["lastTime"])};

  const auto bidTicks = obj["bidTicks"].toArray();
  const auto bidResd = obj["bidResd"].toArray();
  const auto bidCount = obj["bidCount"].toArray();
  toLevels(bidTicks, bidResd, bidCount, market.bids_);

  const auto offerTicks = obj["offerTicks"].toArray();
  const auto offerResd = obj["offerResd"].toArray();
  const auto offerCount = obj["offerCount"].toArray();
  toLevels(offerTicks, offerResd, offerCount, market.offers_);

  return market;
}

QDebug operator<<(QDebug debug, const Market& market)
{
  debug.nospace() << "Market{id=" << market.id() //
                  << ",contr=" << market.contr().mnem() //
                  << ",settlDate=" << market.settlDate() //
                  << ",state=" << market.state() //
                  << ",lastLots=" << market.lastLots() //
                  << ",lastTicks=" << market.lastTicks() //
                  << ",lastTime=" << market.lastTime() //
                  << ",bestBid=" << market.bids().front() //
                  << ",bestOffer=" << market.offers().front() //
                  << '}';
  return debug;
}

} // ui
} // swirly

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
#include "Exec.hpp"

#include "Json.hpp"

#include <QDebug>
#include <QJsonObject>

namespace swirly {
namespace ui {

Exec Exec::fromJson(const QJsonObject& obj)
{
  using swirly::ui::fromJson;
  return Exec{fromJson<QString>(obj["accnt"]),    fromJson<Id64>(obj["marketId"]),
              fromJson<QString>(obj["contr"]),    fromJson<QDate>(obj["settlDate"]),
              fromJson<Id64>(obj["id"]),          fromJson<QString>(obj["ref"]),
              fromJson<Id64>(obj["orderId"]),     fromJson<State>(obj["state"]),
              fromJson<Side>(obj["side"]),        fromJson<Lots>(obj["lots"]),
              fromJson<Ticks>(obj["ticks"]),      fromJson<Lots>(obj["resd"]),
              fromJson<Lots>(obj["exec"]),        fromJson<Cost>(obj["cost"]),
              fromJson<Lots>(obj["lastLots"]),    fromJson<Ticks>(obj["lastTicks"]),
              fromJson<Lots>(obj["minLots"]),     fromJson<Id64>(obj["matchId"]),
              fromJson<LiqInd>(obj["liqInd"]),    fromJson<QString>(obj["cpty"]),
              fromJson<QDateTime>(obj["created"])};
}

QDebug operator<<(QDebug debug, const Exec& exec)
{
  debug.nospace() << "Exec{accnt=" << exec.accnt() //
                  << ",marketId=" << exec.marketId() //
                  << ",contr=" << exec.contr() //
                  << ",settlDate=" << exec.settlDate() //
                  << ",id=" << exec.id() //
                  << ",ref=" << exec.ref() //
                  << ",orderId=" << exec.orderId() //
                  << ",state=" << exec.state() //
                  << ",side=" << exec.side() //
                  << ",lots=" << exec.lots() //
                  << ",ticks=" << exec.ticks() //
                  << ",resd=" << exec.resd() //
                  << ",exec=" << exec.exec() //
                  << ",cost=" << exec.cost() //
                  << ",lastLots=" << exec.lastLots() //
                  << ",lastTicks=" << exec.lastTicks() //
                  << ",minLots=" << exec.minLots() //
                  << ",matchId=" << exec.matchId() //
                  << ",liqInd=" << exec.liqInd() //
                  << ",cpty=" << exec.cpty() //
                  << ",created=" << exec.created() //
                  << '}';
  return debug;
}

} // ui
} // swirly

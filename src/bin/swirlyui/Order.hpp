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
#ifndef SWIRLYUI_ORDER_HPP
#define SWIRLYUI_ORDER_HPP

#include "Contr.hpp"

namespace swirly {
namespace ui {
namespace order {

enum class Column : int { //
  CheckState, //
  MarketId, //
  Contr, //
  SettlDate, //
  Id, //
  Accnt, //
  Ref, //
  State, //
  Side, //
  Lots, //
  Price, //
  Resd, //
  Exec, //
  AvgPrice, //
  LastLots, //
  LastPrice, //
  MinLots, //
  Created, //
  Modified
};
constexpr int ColumnCount{unbox(Column::Modified) + 1};

} // order

class Order {
 public:
  Order(Id64 marketId, const Contr& contr, QDate settlDate, Id64 id, const QString& accnt,
        const QString& ref, State state, Side side, Lots lots, Ticks ticks, Lots resd, Lots exec,
        Cost cost, Lots lastLots, Ticks lastTicks, Lots minLots, const QDateTime& created,
        const QDateTime& modified);
  Order() = default;
  ~Order() noexcept = default;

  static Order fromJson(const Contr& contr, const QJsonObject& obj);

  Id64 marketId() const noexcept { return marketId_; }
  const Contr& contr() const noexcept { return contr_; }
  QDate settlDate() const noexcept { return settlDate_; }
  Id64 id() const noexcept { return id_; }
  const QString& accnt() const noexcept { return accnt_; }
  const QString& ref() const noexcept { return ref_; }
  State state() const noexcept { return state_; }
  Side side() const noexcept { return side_; }
  Lots lots() const noexcept { return lots_; }
  Ticks ticks() const noexcept { return ticks_; }
  Lots resd() const noexcept { return resd_; }
  Lots exec() const noexcept { return exec_; }
  Cost cost() const noexcept { return cost_; }
  Lots lastLots() const noexcept { return lastLots_; }
  Ticks lastTicks() const noexcept { return lastTicks_; }
  Lots minLots() const noexcept { return minLots_; }
  const QDateTime& created() const noexcept { return created_; }
  const QDateTime& modified() const noexcept { return modified_; }

 private:
  Id64 marketId_{};
  Contr contr_{};
  QDate settlDate_{};
  Id64 id_{};
  QString accnt_{};
  QString ref_{};
  State state_{};
  Side side_{};
  Lots lots_{};
  Ticks ticks_{};
  Lots resd_{};
  Lots exec_{};
  Cost cost_{};
  Lots lastLots_{};
  Ticks lastTicks_{};
  Lots minLots_{};
  QDateTime created_{};
  QDateTime modified_{};
};

QDebug operator<<(QDebug debug, const Order& order);

inline bool isModified(const Order& prev, const Order& next) noexcept
{
  return prev.state() != next.state() //
    || prev.lots() != next.lots() //
    || prev.resd() != next.resd() //
    || prev.exec() != next.exec() //
    || prev.cost() != next.cost() //
    || prev.lastLots() != next.lastLots() //
    || prev.lastTicks() != next.lastTicks() //
    || prev.modified() != next.modified();
}

} // ui
} // swirly

Q_DECLARE_METATYPE(swirly::ui::Order)

#endif // SWIRLYUI_ORDER_HPP

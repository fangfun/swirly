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
#ifndef SWIRLY_FIR_REST_HPP
#define SWIRLY_FIR_REST_HPP

#include <swirly/fir/EntitySet.hpp>

#include <swirly/fig/Serv.hpp>

namespace swirly {

/**
 * @addtogroup Rest
 * @{
 */

class SWIRLY_API Rest {
 public:
  explicit Rest(Journ& journ) : serv_{journ} {}
  ~Rest() noexcept;

  // Copy.
  Rest(const Rest&) = delete;
  Rest& operator=(const Rest&) = delete;

  // Move.
  Rest(Rest&&);
  Rest& operator=(Rest&&);

  void load(const Model& model, Millis now) { serv_.load(model, now); }

  void getRec(EntitySet es, Millis now, std::ostream& out) const;

  void getAsset(Millis now, std::ostream& out) const;

  void getAsset(std::string_view mnem, Millis now, std::ostream& out) const;

  void getContr(Millis now, std::ostream& out) const;

  void getContr(std::string_view mnem, Millis now, std::ostream& out) const;

  void getMarket(Millis now, std::ostream& out) const;

  void getMarket(std::string_view mnem, Millis now, std::ostream& out) const;

  void getTrader(Millis now, std::ostream& out) const;

  void getTrader(std::string_view mnem, Millis now, std::ostream& out) const;

  void getSess(std::string_view trader, EntitySet es, Millis now, std::ostream& out) const;

  void getOrder(std::string_view trader, Millis now, std::ostream& out) const;

  void getOrder(std::string_view trader, std::string_view market, Millis now,
                std::ostream& out) const;

  void getOrder(std::string_view trader, std::string_view market, Iden id, Millis now,
                std::ostream& out) const;

  void getTrade(std::string_view trader, Millis now, std::ostream& out) const;

  void getTrade(std::string_view trader, std::string_view market, Millis now,
                std::ostream& out) const;

  void getTrade(std::string_view trader, std::string_view market, Iden id, Millis now,
                std::ostream& out) const;

  void getPosn(std::string_view trader, Millis now, std::ostream& out) const;

  void getPosn(std::string_view trader, std::string_view contr, Millis now,
               std::ostream& out) const;

  void getPosn(std::string_view trader, std::string_view contr, IsoDate settlDate, Millis now,
               std::ostream& out) const;

  void getView(Millis now, std::ostream& out) const;

  void getView(ArrayView<std::string_view> markets, Millis now, std::ostream& out) const;

  void postMarket(std::string_view mnem, std::string_view display, std::string_view contr,
                  IsoDate settlDate, IsoDate expiryDate, MarketState state, Millis now,
                  std::ostream& out);

  void putMarket(std::string_view mnem, std::optional<std::string_view> display,
                 std::optional<MarketState> state, Millis now, std::ostream& out);

  void postTrader(std::string_view mnem, std::string_view display, std::string_view email,
                  Millis now, std::ostream& out);

  void putTrader(std::string_view mnem, std::string_view display, Millis now, std::ostream& out);

  void postOrder(std::string_view trader, std::string_view market, std::string_view ref, Side side,
                 Lots lots, Ticks ticks, Lots minLots, Millis now, std::ostream& out);

  void putOrder(std::string_view trader, std::string_view market, ArrayView<Iden> ids, Lots lots,
                Millis now, std::ostream& out);

  void deleteOrder(std::string_view market, ArrayView<Iden> ids, Millis now, std::ostream& out);

  void postTrade(std::string_view market, Millis now, std::ostream& out);

  void deleteTrade(std::string_view market, ArrayView<Iden> ids, Millis now, std::ostream& out);

 private:
  Serv serv_;
};

/** @} */

} // swirly

#endif // SWIRLY_FIR_REST_HPP

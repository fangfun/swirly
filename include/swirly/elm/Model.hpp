/*
 * Swirly Order-Book and Matching-Engine.
 * Copyright (C) 2013, 2015 Swirly Cloud Limited.
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
#ifndef SWIRLY_ELM_MODEL_HPP
#define SWIRLY_ELM_MODEL_HPP

#include <swirly/elm/Rec.hpp>

namespace swirly {

class Factory;

/**
 * @addtogroup IO
 * @{
 */

class SWIRLY_API Model {
protected:
    virtual RecSet doReadAsset(const Factory& factory) const = 0;

    virtual RecSet doReadContr(const Factory& factory) const = 0;

    virtual RecSet doReadMarket(const Factory& factory) const = 0;

    virtual RecSet doReadTrader(const Factory& factory) const = 0;

public:
    Model() noexcept = default;
    virtual ~Model() noexcept;

    // Copy.
    constexpr Model(const Model&) noexcept = default;
    Model& operator =(const Model&) noexcept = default;

    // Move.
    constexpr Model(Model&&) noexcept = default;
    Model& operator =(Model&&) noexcept = default;

    RecSet readAsset(const Factory& factory) const
    {
        return doReadAsset(factory);
    }
    RecSet readContr(const Factory& factory) const
    {
        return doReadContr(factory);
    }
    RecSet readMarket(const Factory& factory) const
    {
        return doReadMarket(factory);
    }
    RecSet readTrader(const Factory& factory) const
    {
        return doReadTrader(factory);
    }
};

/** @} */

} // swirly

#endif // SWIRLY_ELM_MODEL_HPP

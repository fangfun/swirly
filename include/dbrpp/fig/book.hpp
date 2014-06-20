/*
 *  Copyright (C) 2013, 2014 Mark Aylett <mark.aylett@gmail.com>
 *
 *  This file is part of Doobry written by Mark Aylett.
 *
 *  Doobry is free software; you can redistribute it and/or modify it under the terms of the GNU
 *  General Public License as published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  Doobry is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 *  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this program; if
 *  not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA.
 */
#ifndef DBRPP_FIG_BOOK_HPP
#define DBRPP_FIG_BOOK_HPP

#include <dbrpp/fig/side.hpp>

#include <dbrpp/elm/rec.hpp>

#include <dbr/fig/book.h>

#include <iostream>

namespace dbr {

/**
 * @addtogroup Book
 * @{
 */

class Book {
    mutable DbrBook impl_;
public:
    ~Book() noexcept
    {
        dbr_book_term(&impl_);
    }
    explicit
    Book(DbrRec& crec, DbrJd settl_day, DbrPool pool) noexcept
    {
        dbr_book_init(&impl_, &crec, settl_day, pool);
    }
    operator DbrBook&() noexcept
    {
        return impl_;
    }
    DbrBook*
    c_arg() noexcept
    {
        return &impl_;
    }

    // Copy semantics.

    Book(const Book&) = delete;

    Book&
    operator =(const Book&) = delete;

    bool
    operator ==(const Book& rhs) const noexcept
    {
        return key() == rhs.key();
    }
    bool
    operator !=(const Book& rhs) const noexcept
    {
        return key() != rhs.key();
    }
    DbrKey
    key() const noexcept
    {
        return dbr_book_key(impl_.crec->id, impl_.settl_day);
    }
    ContrRecRef
    crec() const noexcept
    {
        return ContrRecRef{*dbr_book_crec(&impl_)};
    }
    DbrJd
    settl_day() const noexcept
    {
        return dbr_book_settl_day(&impl_);
    }
    SideRef
    bid_side() const noexcept
    {
        return SideRef{*dbr_book_bid_side(&impl_)};
    }
    SideRef
    offer_side() const noexcept
    {
        return SideRef{*dbr_book_offer_side(&impl_)};
    }
};

inline std::ostream&
operator <<(std::ostream& os, const Book& book)
{
    return os << "key=" << book.key()
              << ",crec=" << book.crec().mnem()
              << ",settl_day" << book.settl_day();
}

class BookRef {
    DbrBook* impl_;
public:
    explicit
    BookRef(DbrBook& impl) noexcept
        : impl_{&impl}
    {
    }
    operator DbrBook&() const noexcept
    {
        return *impl_;
    }
    DbrBook*
    c_arg() const noexcept
    {
        return impl_;
    }
    bool
    operator ==(BookRef rhs) const noexcept
    {
        return key() == rhs.key();
    }
    bool
    operator !=(BookRef rhs) const noexcept
    {
        return key() != rhs.key();
    }
    DbrKey
    key() const noexcept
    {
        return dbr_book_key(impl_->crec->id, impl_->settl_day);
    }
    ContrRecRef
    crec() const noexcept
    {
        return ContrRecRef{*dbr_book_crec(impl_)};
    }
    DbrJd
    settl_day() const noexcept
    {
        return dbr_book_settl_day(impl_);
    }
    SideRef
    bid_side() const noexcept
    {
        return SideRef{*dbr_book_bid_side(impl_)};
    }
    SideRef
    offer_side() const noexcept
    {
        return SideRef{*dbr_book_offer_side(impl_)};
    }
};

inline std::ostream&
operator <<(std::ostream& os, BookRef book)
{
    return os << "key=" << book.key()
              << ",crec=" << book.crec().mnem()
              << ",settl_day" << book.settl_day();
}

/** @} */

} // dbr

#endif // DBRPP_FIG_BOOK_HPP
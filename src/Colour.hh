//
// Colour.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//
// This file is part of Rubik.
//
// Rubik is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Rubik is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rubik.  If not, see <http://www.gnu.org/licenses/>

#pragma once

struct Colour
{
    enum Type
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,

        Undefined
    } _t;

    Colour (Type t) : _t(t) { }
    operator Type () const { return _t; }

    // Number the colour starting from 1
    unsigned GetNumber () const;

private:
    template <typename T>
    operator T () const;
};

// vim: set et ts=4 sw=4:

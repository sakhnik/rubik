//
// Colour.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

struct Colour
{
    enum Type
    {
        N, A, B, C, D, E, F
    } _t;

    Colour (Type t) : _t(t) { }
    operator Type () const { return _t; }

    char const* GetChar () const;

private:
    template <typename T>
    operator T () const;
};

// vim: set et ts=4 sw=4:

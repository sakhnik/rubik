//
// Cell.cc
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

#include "Cell.hh"
#include <stdexcept>

using namespace std;

cCell::cCell (cVector const& pos,
              cVector const& i,
              cVector const& j,
              cVector const& k)
    : _pos (pos)
    , _i (i)
    , _j (j)
    , _k (k)
{
}

Colour cCell::GetColour (cVector const& direction) const
{
    // We calculate which edge the given direction points to,
    // and return the colour assigned to that edge.
    int pi = direction * _i;
    if (pi == 1)
        return Colour::A;
    if (pi == -1)
        return Colour::B;
    int pj = direction * _j;
    if (pj == 1)
        return Colour::C;
    if (pj == -1)
        return Colour::D;
    int pk = direction * _k;
    if (pk == 1)
        return Colour::E;
    if (pk == -1)
        return Colour::F;
    throw runtime_error ("Bug");
}

void cCell::RotateX (bool clockwise)
{
    _pos.RotateX (clockwise);
    _i.RotateX (clockwise);
    _j.RotateX (clockwise);
    _k.RotateX (clockwise);
}

void cCell::RotateY (bool clockwise)
{
    _pos.RotateY (clockwise);
    _i.RotateY (clockwise);
    _j.RotateY (clockwise);
    _k.RotateY (clockwise);
}

void cCell::RotateZ (bool clockwise)
{
    _pos.RotateZ (clockwise);
    _i.RotateZ (clockwise);
    _j.RotateZ (clockwise);
    _k.RotateZ (clockwise);
}

bool cCell::DirEquals (cCell const& o) const
{
    return _i == o._i && _j == o._j && _k == o._k;
}

// vim: set et ts=4 sw=4:

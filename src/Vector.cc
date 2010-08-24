//
// Vector.cc
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

#include "Vector.hh"
#include <iostream>

using namespace std;

cVector::cVector (int x, int y, int z)
    : _x (x)
    , _y (y)
    , _z (z)
{
}

int cVector::operator* (cVector const& o) const
{
    return _x*o._x + _y*o._y + _z*o._z;
}

bool cVector::operator== (cVector const& o) const
{
    return _x == o._x && _y == o._y && _z == o._z;
}

void cVector::RotateX (bool clockwise)
{
    // Rotation matrix for 90-degree turn CCW is the following:
    //   |0 -1|
    //   |1  0|
    // So this is the matrix product:
    int old_y = _y;
    _y = clockwise ? _z : -_z;
    _z = clockwise ? -old_y : old_y;
}

void cVector::RotateY (bool clockwise)
{
    int old_z = _z;
    _z = clockwise ? _x : -_x;
    _x = clockwise ? -old_z : old_z;
}

void cVector::RotateZ (bool clockwise)
{
    int old_x = _x;
    _x = clockwise ? _y : -_y;
    _y = clockwise ? -old_x : old_x;
}

ostream& operator<< (ostream& os, cVector const& vect)
{
    return os << "(" << vect._x << "," << vect._y << "," << vect._z << ")";
}

// vim: set et ts=4 sw=4:

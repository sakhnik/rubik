//
// Vector.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

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

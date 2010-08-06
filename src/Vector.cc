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

void cVector::RotateX ()
{
    int old_y = _y;
    _y = -_z;
    _z = old_y;
}

void cVector::RotateY ()
{
    int old_z = _z;
    _z = -_x;
    _x = old_z;
}

void cVector::RotateZ ()
{
    int old_x = _x;
    _x = -_y;
    _y = old_x;
}

ostream& operator<< (ostream& os, cVector const& vect)
{
    return os << "(" << vect._x << "," << vect._y << "," << vect._z << ")";
}

// vim: set et ts=4 sw=4:

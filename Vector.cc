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

ostream& operator<< (ostream& os, cVector const& vect)
{
    return os << "(" << vect._x << "," << vect._y << "," << vect._z << ")";
}

// vim: set et ts=4 sw=4:

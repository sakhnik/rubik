//
// Cell.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

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

// vim: set et ts=4 sw=4:

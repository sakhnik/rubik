//
// Cube.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#include "Cube.hh"
#include "Canvas.hh"
#include <string>
#include <stdexcept>

using namespace std;

cCube::cCube (int n)
    : _n (n)
    , _lo (1 - n)
    , _hi (n - 1)
{
    if (n <= 0)
        throw invalid_argument ("n must be greather than 0");

    cVector i (1, 0, 0);
    cVector j (0, 1, 0);
    cVector k (0, 0, 1);

    for (int x = _lo; x <= _hi; x += 2)
        for (int y = _lo; y <= _hi; y += 2)
            for (int z = _lo; z <= _hi; z += 2)
            {
                if (_lo < x && x < _hi &&
                    _lo < y && y < _hi &&
                    _lo < z && z < _hi)
                    continue;
                cVector pos (x, y, z);
                cCell cell (pos, i, j, k);
                _cells.push_back (cell);
            }
}

unsigned cCube::_Space2Canvas (int coord) const
{
    return (_n + coord - 1) >> 1;
}

int cCube::_Canvas2Space (unsigned coord) const
{
    return (coord << 1) - _n - 1;
}

bool cCube::_IsFront (cCell const& cell) const
{
    return cell.GetPos().GetX() == _lo;
}

bool cCube::_IsBack (cCell const& cell) const
{
    return cell.GetPos().GetX() == _hi;
}

bool cCube::_IsLeft (cCell const& cell) const
{
    return cell.GetPos().GetZ() == _lo;
}

bool cCube::_IsRight (cCell const& cell) const
{
    return cell.GetPos().GetZ() == _hi;
}

bool cCube::_IsTop (cCell const& cell) const
{
    return cell.GetPos().GetY() == _lo;
}

bool cCube::_IsBottom (cCell const& cell) const
{
    return cell.GetPos().GetY() == _hi;
}

void cCube::Draw (cCanvas& canvas) const
{
    for (_CellsT::const_iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        cCell const& cell = *i;
        cVector const& pos = cell.GetPos();
        if (_IsFront (cell))
        {
            cVector view (1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetZ()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsTop (cell))
        {
            cVector view (0, 1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetZ()),
                             2*_n + _Space2Canvas (pos.GetX()),
                             colour);
        }
        if (_IsLeft (cell))
        {
            cVector view (0, 0, 1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_hi - _Space2Canvas (pos.GetX()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsBack (cell))
        {
            cVector view (-1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (3*_n + _hi - _Space2Canvas (pos.GetZ()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsBottom (cell))
        {
            cVector view (0, -1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetZ()),
                             _hi - _Space2Canvas (pos.GetX()),
                             colour);
        }
        if (_IsRight (cell))
        {
            cVector view (0, 0, -1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (2*_n + _Space2Canvas (pos.GetX()),
                             1*_n + _Space2Canvas (pos.GetY()),
                             colour);
        }
    }
}

void cCube::TurnFront (int slice)
{
    if (slice < 1 || slice > _n)
        throw invalid_argument ("Incorrect slice");

    int x = _Canvas2Space (slice);

    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetX() == x)
            i->RotateX ();
    }
}

void cCube::TurnTop (int slice)
{
    if (slice < 1 || slice > _n)
        throw invalid_argument ("Incorrect slice");

    int y = _Canvas2Space (slice);

    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetY() == y)
            i->RotateY ();
    }
}

void cCube::TurnSide (int slice)
{
    if (slice < 1 || slice > _n)
        throw invalid_argument ("Incorrect slice");

    int z = _Canvas2Space (slice);

    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetZ() == z)
            i->RotateZ ();
    }
}

// vim: set et ts=4 sw=4:

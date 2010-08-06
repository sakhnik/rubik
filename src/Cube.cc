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
#include <iostream>

using namespace std;

cCube::cCube (int n)
    : _n (n)
{
    if (n <= 0)
        throw invalid_argument ("n must be greather than 0");

    cVector i (1, 0, 0);
    cVector j (0, 1, 0);
    cVector k (0, 0, 1);

    for (int x = 1 - n; x <= n - 1; x += 2)
        for (int y = 1 - n; y <= n - 1; y += 2)
            for (int z = 1 - n; z <= n - 1; z += 2)
            {
                if (1 - n < x && x < n - 1 &&
                    1 - n < y && y < n - 1 &&
                    1 - n < z && z < n - 1)
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

void cCube::Draw (cCanvas& canvas) const
{
    for (size_t i = 0; i != _cells.size(); ++i)
    {
        cCell const& cell = _cells[i];
        cVector const& pos = cell.GetPos();
        if (pos.GetX() == 1 - _n)
        {
            cVector view (1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetY()),
                             _n + _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (pos.GetY() == 1 - _n)
        {
            cVector view (0, 1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_Space2Canvas (pos.GetX()),
                             _n + _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (pos.GetZ() == 1 - _n)
        {
            cVector view (0, 0, 1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetX()),
                             _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (pos.GetX() == _n - 1)
        {
            cVector view (-1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (3*_n + _Space2Canvas (pos.GetY()),
                             _n + _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (pos.GetY() == _n - 1)
        {
            cVector view (0, -1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (2*_n + _Space2Canvas (pos.GetX()),
                             _n + _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (pos.GetZ() == _n - 1)
        {
            cVector view (0, 0, -1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetX()),
                             2*_n + _Space2Canvas (pos.GetY()),
                             colour);
        }
    }
}

// vim: set et ts=4 sw=4:

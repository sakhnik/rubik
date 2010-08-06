//
// Cube.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#include "Cube.hh"
#include "Canvas.hh"
#include <string>

using namespace std;

cCube::cCube (unsigned n)
    : _n (n)
{
    cVector i (1, 0, 0);
    cVector j (0, 1, 0);
    cVector k (0, 0, 1);

    for (unsigned x = 0; x != n; ++x)
        for (unsigned y = 0; y != n; ++y)
            for (unsigned z = 0; z != n; ++z)
            {
                if (x != 0 && x != n - 1 &&
                    y != 0 && y != n - 1 &&
                    z != 0 && z != n - 1)
                    continue;
                cVector pos (x, y, z);
                cCell cell (pos, i, j, k);
                _cells.push_back (cell);
            }
}

void cCube::Draw (cCanvas& canvas) const
{
    for (size_t i = 0; i != _cells.size(); ++i)
    {
        cCell const& cell = _cells[i];
        cVector const& pos = cell.GetPos();
        if (pos.GetX() == 0)
        {
            cVector view (1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetY() + _n,
                             pos.GetZ() + _n,
                             colour);
        }
        if (pos.GetY() == 0)
        {
            cVector view (0, 1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetX(),
                             pos.GetZ() + _n,
                             colour);
        }
        if (pos.GetZ() == 0)
        {
            cVector view (0, 0, 1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetX() + _n,
                             pos.GetY(),
                             colour);
        }
        if (pos.GetX() == static_cast<int> (_n) - 1)
        {
            cVector view (-1, 0, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetY() + 3*_n,
                             pos.GetZ() + _n,
                             colour);
        }
        if (pos.GetY() == static_cast<int> (_n) - 1)
        {
            cVector view (0, -1, 0);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetX() + 2*_n,
                             pos.GetZ() + _n,
                             colour);
        }
        if (pos.GetZ() == static_cast<int> (_n) - 1)
        {
            cVector view (0, 0, -1);
            Colour colour = cell.GetColour (view);
            canvas.SetPixel (pos.GetX() + _n,
                             pos.GetY() + 2*_n,
                             colour);
        }
    }
}

// vim: set et ts=4 sw=4:

//
// Cell.hh
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

#pragma once

#include "Vector.hh"
#include "Colour.hh"

// A Rubik cube cell is a positioned, directed cube 1x1, each edge of which
// has a distinct colour.
class cCell
{
public:
    cCell (cVector const& pos,       // Position
           cVector const& i,         // Orthogonal vectors of direction
           cVector const& j,
           cVector const& k);

    cVector const& GetPos() const { return _pos; }

    // Given direction of view, calculate the colour of the cell.
    Colour GetColour (cVector const& direction) const;

    // Turn the cell around the X-axis by 90 degrees
    void RotateX (bool clockwise);
    // Turn the cell around the Y-axis by 90 degrees
    void RotateY (bool clockwise);
    // Turn the cell around the Z-axis by 90 degrees
    void RotateZ (bool clockwise);

    // Check if two cells' directions are equal
    bool DirEquals (cCell const& o) const;

private:
    cVector _pos;

    cVector _i;
    cVector _j;
    cVector _k;
};

// vim: set et ts=4 sw=4:

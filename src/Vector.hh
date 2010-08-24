//
// Vector.hh
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

#include <iosfwd>

// Simple vector in the 3d-space given by integer coordinates
class cVector
{
public:
    cVector (int x, int y, int z);

    int GetX () const { return _x; }
    int GetY () const { return _y; }
    int GetZ () const { return _z; }

    // Scalar product
    int operator* (cVector const& o) const;
    bool operator== (cVector const& o) const;

    // Turn around by 90 degrees the X-axis in the given direction
    void RotateX (bool clockwise);
    // Turn around by 90 degrees the Y-axis in the given direction
    void RotateY (bool clockwise);
    // Turn around by 90 degrees the Z-axis in the given direction
    void RotateZ (bool clockwise);

private:
    int _x;
    int _y;
    int _z;

    friend std::ostream& operator<< (std::ostream& os, cVector const& vect);
};

// vim: set et ts=4 sw=4:

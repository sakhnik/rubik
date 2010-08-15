//
// Vector.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

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

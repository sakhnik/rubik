//
// Vector.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

#include <iosfwd>

class cVector
{
public:
    cVector (int x, int y, int z);

    int GetX () const { return _x; }
    int GetY () const { return _y; }
    int GetZ () const { return _z; }

    int operator* (cVector const& o) const;

private:
    int _x;
    int _y;
    int _z;

    friend std::ostream& operator<< (std::ostream& os, cVector const& vect);
};

// vim: set et ts=4 sw=4:

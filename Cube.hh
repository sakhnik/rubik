//
// Cube.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

#include "Cell.hh"
#include <vector>

class cCanvas;

class cCube
{
public:
    cCube (unsigned n);

    unsigned GetN () const { return _n; }

    void Draw (cCanvas& canvas) const;

private:
    unsigned _n;

    typedef std::vector<cCell> _CellsT;
    _CellsT _cells;
};

// vim: set et ts=4 sw=4:

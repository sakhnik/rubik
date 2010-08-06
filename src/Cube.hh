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
    cCube (int n);

    int GetN () const { return _n; }

    void Draw (cCanvas& canvas) const;

private:
    int _n;

    typedef std::vector<cCell> _CellsT;
    _CellsT _cells;

    unsigned _Space2Canvas (int coord) const;
};

// vim: set et ts=4 sw=4:

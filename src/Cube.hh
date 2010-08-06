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

    void TurnFront (int slice, bool clockwise);
    void TurnTop (int slice, bool clockwise);
    void TurnSide (int slice, bool clockwise);

    void Shuffle (unsigned count);

    void Roll (bool clockwise);
    void Yaw (bool clockwise);
    void Pitch (bool clockwise);

private:
    int _n;
    int _lo;
    int _hi;

    typedef std::vector<cCell> _CellsT;
    _CellsT _cells;

    unsigned _Space2Canvas (int coord) const;
    int _Canvas2Space (unsigned coord) const;

    bool _IsFront (cCell const& cell) const;
    bool _IsBack (cCell const& cell) const;
    bool _IsLeft (cCell const& cell) const;
    bool _IsRight (cCell const& cell) const;
    bool _IsTop (cCell const& cell) const;
    bool _IsBottom (cCell const& cell) const;
};

// vim: set et ts=4 sw=4:

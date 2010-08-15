//
// Cube.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

#include "Cell.hh"
#include <list>
#include <stack>

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

    int Undo (unsigned count = 1);

    bool IsComplete () const;

private:
    int _n;
    int _lo;
    int _hi;

    typedef std::list<cCell> _CellsT;
    _CellsT _cells;

    enum _eTurnCode
    {
        _TC_FRONT = 0,
        _TC_TOP,
        _TC_SIDE
    };

    struct _sUndo
    {
        _eTurnCode turn_code;
        int slice;
        bool clockwise;
    };

    typedef std::stack<_sUndo> _UndoStackT;
    _UndoStackT _undo_stack;

    unsigned _Space2Canvas (int coord) const;
    int _Canvas2Space (unsigned coord) const;

    void _DoTurnFront (int slice, bool clockwise);
    void _DoTurnTop (int slice, bool clockwise);
    void _DoTurnSide (int slice, bool clockwise);

    bool _IsFront (cCell const& cell) const;
    bool _IsBack (cCell const& cell) const;
    bool _IsLeft (cCell const& cell) const;
    bool _IsRight (cCell const& cell) const;
    bool _IsTop (cCell const& cell) const;
    bool _IsDown (cCell const& cell) const;
};

// vim: set et ts=4 sw=4:

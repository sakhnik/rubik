//
// Cube.hh
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
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>

#pragma once

#include "Cell.hh"
#include <list>
#include <stack>

class cCanvas;

// Rubik cube is a collection of directioned coloured cells in face edges.
class cCube
{
public:
    // Create a cube with n cells in a row
    cCube (int n);

    int GetN () const { return _n; }

    // Draw unfolded cube on the canvas
    void Draw (cCanvas& canvas) const;

    // Rotate given front slice counting from the nearest in given direction
    void TurnFront (int slice, bool clockwise);
    // Rotate given horizontal slice counting from top in given direction
    void TurnTop (int slice, bool clockwise);
    // Rotate given side slice counting from left in given direction
    void TurnSide (int slice, bool clockwise);

    // Shuffle the cube by random count rotations
    void Shuffle (unsigned count);

    // Rotate the whole cube, change point direction
    void Roll (bool clockwise);
    void Yaw (bool clockwise);
    void Pitch (bool clockwise);

    // Undo last count moves
    int Undo (unsigned count = 1);

    // Check if the cube is complete
    bool IsComplete () const;

private:
    int _n;
    // Lowest coordinate of a cell
    int _lo;
    // Highest coordinate of a cell
    int _hi;

    // List of outer cube cells
    typedef std::list<cCell> _CellsT;
    _CellsT _cells;

    // Turn codes for the undo list
    enum _eTurnCode
    {
        _TC_FRONT = 0,
        _TC_TOP,
        _TC_SIDE
    };

    // Undo node
    struct _sUndo
    {
        _eTurnCode turn_code;
        int slice;
        bool clockwise;
    };

    // Stack of undo actions
    typedef std::stack<_sUndo> _UndoStackT;
    _UndoStackT _undo_stack;

    // Translate coordinates to and from the canvas system
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

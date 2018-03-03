//
// Cube.cc
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

#include "Cube.hh"
#include "Canvas.hh"

#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cassert>

using namespace std;

// To perform turns simply, we should have center of every face in
// the origin of system of coordinates. Thus, for a n-cube, coordinates
// would be in the range [-n/2 .. n/2]. To work with integer numbers,
// we use doulbed coordinates, thus translating cells to
// [_lo, _lo + 2 .. _hi]
//
// The axis are oriented in the following way (right threesome):
//
//     y│
//      │
//      └─────
//    z╱     x
//
cCube::cCube (int n)
    : _n (n)
    , _lo (1 - n)
    , _hi (n - 1)
{
    if (n <= 0)
        throw invalid_argument ("n must be greather than 0");

    // Initially all the cells are oriented in the same direction
    cVector i (1, 0, 0);
    cVector j (0, 1, 0);
    cVector k (0, 0, 1);

    // Iterate over all the cells in a cube
    for (int x = _lo; x <= _hi; x += 2)
        for (int y = _lo; y <= _hi; y += 2)
            for (int z = _lo; z <= _hi; z += 2)
            {
                // Ignore inner cells, since they won't be ever visible
                if (_lo < x && x < _hi &&
                    _lo < y && y < _hi &&
                    _lo < z && z < _hi)
                    continue;
                cVector pos (x, y, z);
                cCell cell (pos, i, j, k);
                _cells.push_back (cell);
            }
}

// Translate coordinates: [_lo, _lo + 2 .. _hi] -> [0 .. n-1]
unsigned cCube::_Space2Canvas (int coord) const
{
    return (_n + coord - 1) >> 1;
}

// Translate coordinates: [0 .. n-1] -> [_lo, _lo + 2 .. _hi]
int cCube::_Canvas2Space (unsigned coord) const
{
    return (coord << 1) - _n + 1;
}

const cVector FRONT_VIEW (0, 0, -1);
const cVector BACK_VIEW (0, 0, 1);
const cVector LEFT_VIEW (1, 0, 0);
const cVector RIGHT_VIEW (-1, 0, 0);
const cVector TOP_VIEW (0, 1, 0);
const cVector DOWN_VIEW (0, -1, 0);

void cCube::Draw (cCanvas& canvas) const
{
    for (_CellsT::const_iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        cCell const& cell = *i;
        cVector const& pos = cell.GetPos();
        // Put every cell on its place in the canvas with the outer
        // color.
        if (_IsVisible (cell, FRONT_VIEW))
        {
            // Front cells are in the center:
            //  0
            // 0X00
            //  0
            Colour colour = cell.GetColour (FRONT_VIEW);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetX()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsVisible (cell, TOP_VIEW))
        {
            // Top face
            //  X
            // 0000
            //  0
            Colour colour = cell.GetColour (TOP_VIEW);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetX()),
                             _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (_IsVisible (cell, LEFT_VIEW))
        {
            // Left face
            //  0
            // X000
            //  0
            Colour colour = cell.GetColour (LEFT_VIEW);
            canvas.SetPixel (_Space2Canvas (pos.GetZ()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsVisible (cell, BACK_VIEW))
        {
            // Back face
            //  0
            // 000X
            //  0
            Colour colour = cell.GetColour (BACK_VIEW);
            canvas.SetPixel (3*_n + _hi - _Space2Canvas (pos.GetX()),
                             _n + _Space2Canvas (pos.GetY()),
                             colour);
        }
        if (_IsVisible (cell, DOWN_VIEW))
        {
            // Down face
            //  0
            // 0000
            //  X
            Colour colour = cell.GetColour (DOWN_VIEW);
            canvas.SetPixel (_n + _Space2Canvas (pos.GetX()),
                             2*_n + _hi - _Space2Canvas (pos.GetZ()),
                             colour);
        }
        if (_IsVisible (cell, RIGHT_VIEW))
        {
            // Right face
            //  0
            // 00X0
            //  0
            Colour colour = cell.GetColour (RIGHT_VIEW);
            canvas.SetPixel (2*_n + _hi - _Space2Canvas (pos.GetZ()),
                             1*_n + _Space2Canvas (pos.GetY()),
                             colour);
        }
    }
}

void cCube::TurnFront (int slice, bool clockwise)
{
    if (slice < -_n || slice > _n - 1)
        throw invalid_argument ("Incorrect slice");

    // Allow numbering from the back side like in python lists
    if (slice < 0)
        slice += _n;

    // Perform the turn
    _DoTurnFront (slice, clockwise);

    // Push contra action into the undo stack
    _sUndo undo = { _TC_FRONT, slice, !clockwise };
    _undo_stack.push (undo);
}

void cCube::_DoTurnFront (int slice, bool clockwise)
{
    int z = -_Canvas2Space (slice);

    // Rotate only the face selected by slice
    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetZ() == z)
            i->RotateZ (!clockwise);
    }
}

void cCube::TurnTop (int slice, bool clockwise)
{
    if (slice < -_n || slice > _n - 1)
        throw invalid_argument ("Incorrect slice");

    if (slice < 0)
        slice += _n;

    _DoTurnTop (slice, clockwise);

    _sUndo undo = { _TC_TOP, slice, !clockwise };
    _undo_stack.push (undo);
}

void cCube::_DoTurnTop (int slice, bool clockwise)
{
    int y = _Canvas2Space (slice);

    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetY() == y)
            i->RotateY (clockwise);
    }
}

void cCube::TurnSide (int slice, bool clockwise)
{
    if (slice < -_n || slice > _n - 1)
        throw invalid_argument ("Incorrect slice");

    if (slice < 0)
        slice += _n;

    _DoTurnSide (slice, clockwise);

    _sUndo undo = { _TC_SIDE, slice, !clockwise };
    _undo_stack.push (undo);
}

void cCube::_DoTurnSide (int slice, bool clockwise)
{
    int x = _Canvas2Space (slice);

    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        if (i->GetPos().GetX() == x)
            i->RotateX (clockwise);
    }
}

void cCube::Shuffle (unsigned count)
{
    // TODO: The shuffle creates undo stack, should this be changed?
    for (unsigned i = 0; i != count; ++i)
    {
        unsigned slice = rand() % _n;
        bool clockwise = rand() & 1;
        switch (rand() % 3)
        {
        case 0:
            TurnFront (slice, clockwise);
            break;
        case 1:
            TurnSide (slice, clockwise);
            break;
        case 2:
            TurnTop (slice, clockwise);
            break;
        }
    }
}

void cCube::Roll (bool clockwise)
{
    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        i->RotateZ (clockwise);
    }
}

void cCube::Yaw (bool clockwise)
{
    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        i->RotateY (clockwise);
    }
}

void cCube::Pitch (bool clockwise)
{
    for (_CellsT::iterator i = _cells.begin(); i != _cells.end(); ++i)
    {
        i->RotateX (clockwise);
    }
}

int cCube::Undo (unsigned count)
{
    // Apply the count last undo actions
    for (unsigned i = 0; i != count; ++i)
    {
        if (_undo_stack.empty())
            return i;

        _sUndo const& undo = _undo_stack.top();
        switch (undo.turn_code)
        {
        case _TC_FRONT:
            _DoTurnFront (undo.slice, undo.clockwise);
            break;
        case _TC_TOP:
            _DoTurnTop (undo.slice, undo.clockwise);
            break;
        case _TC_SIDE:
            _DoTurnSide (undo.slice, undo.clockwise);
            break;
        default:
            throw runtime_error ("Unsupported turn code for undo");
        }
        _undo_stack.pop ();
    }
    return count;
}

bool cCube::_IsVisible (cCell const& cell,
                        cVector const& view) const
{
    assert (abs(view.GetX()) + abs(view.GetY()) + abs(view.GetZ()) == 1 ||
            "View should be a 1 vector");

    cVector const& pos = cell.GetPos ();
    return (!view.GetX() || pos.GetX() == _lo * view.GetX()) &&
           (!view.GetY() || pos.GetY() == _lo * view.GetY()) &&
           (!view.GetZ() || pos.GetZ() == _lo * view.GetZ());
}

static bool _CheckFaceColour (cCell const& cell,
                              Colour& face_colour,
                              cVector const& view)
{
    Colour cell_colour = cell.GetColour (view);
    if (face_colour == Colour(Colour::Undefined))
        face_colour = cell_colour;
    else if (face_colour != cell_colour)
        return false;
    return true;
}

bool cCube::IsComplete () const
{
    Colour front = Colour::Undefined;
    Colour back = Colour::Undefined;
    Colour left = Colour::Undefined;
    Colour right = Colour::Undefined;
    Colour top = Colour::Undefined;
    Colour down = Colour::Undefined;

    for (_CellsT::const_iterator i = _cells.begin();
         i != _cells.end(); ++i)
    {
        cCell const& cell = *i;
        if (_IsVisible (cell, FRONT_VIEW) &&
            !_CheckFaceColour (cell, front, FRONT_VIEW))
            return false;
        if (_IsVisible (cell, BACK_VIEW) &&
            !_CheckFaceColour (cell, back, BACK_VIEW))
            return false;
        if (_IsVisible (cell, LEFT_VIEW) &&
            !_CheckFaceColour (cell, left, LEFT_VIEW))
            return false;
        if (_IsVisible (cell, RIGHT_VIEW) &&
            !_CheckFaceColour (cell, right, RIGHT_VIEW))
            return false;
        if (_IsVisible (cell, TOP_VIEW) &&
            !_CheckFaceColour (cell, top, TOP_VIEW))
            return false;
        if (_IsVisible (cell, DOWN_VIEW) &&
            !_CheckFaceColour (cell, down, DOWN_VIEW))
            return false;
    }
    return true;
}

int cCube::TrackTurn (int start_x,
                      int start_y,
                      int end_x,
                      int end_y)
{
    // Movement vector
    int dx = end_x - start_x;
    int dy = end_y - start_y;

    // No movement gives no result
    if (dx == 0 && dy == 0)
        return -1;

    // We expect only parallel moves
    if (dx != 0 && dy != 0)
        return -2;

    // Analyze horizontal strokes
    if (dy == 0)
    {
        // Quadrant (quotient) defines direction of the turn, and
        // the rest defines slice to turn.
        unsigned q_y = start_y / _n;
        switch (q_y)
        {
        case 0:
            TurnFront (_n - 1 - start_y % _n,
                       start_x < end_x);
            return 0;
        case 1:
            TurnTop (start_y % _n,
                     start_x > end_x);
            return 0;
        case 2:
            TurnFront (start_y % _n,
                       start_x > end_x);
            return 0;
        }
        return -1;
    }

    // Analyze vertical strokes
    if (dx == 0)
    {
        unsigned q_x = start_x / _n;
        switch (q_x)
        {
        case 0:
            TurnFront (_n - 1 - start_x % _n,
                       start_y > end_y);
            return 0;
        case 1:
            TurnSide (start_x % _n,
                      start_y < end_y);
            return 0;
        case 2:
            TurnFront (start_x % _n,
                       start_y < end_y);
            return 0;
        case 3:
            TurnSide (_n - 1 - start_x % _n,
                      start_y > end_y);
            return 0;
        }
        return -1;
    }

    return -1;
}

// vim: set et ts=4 sw=4:

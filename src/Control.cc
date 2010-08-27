//
// Control.cc
//
//     Created: 24.08.2010
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

#include "Control.hh"
#include "Cube.hh"
#include "Canvas.hh"

#include <stdexcept>

using namespace std;

cControl::cControl ()
    : _wnd (::newwin (3, COLS, 0, 0))
{
    if (!_wnd)
        throw runtime_error ("Couldn't create control window");

    ::mousemask (BUTTON1_PRESSED | BUTTON1_RELEASED, 0);
    ::keypad (_wnd, TRUE);
}

cControl::~cControl ()
{
    ::delwin (_wnd);
}

int cControl::Process (cCube& cube,
                       cCanvas const& canvas)
{
    ::mvwprintw (_wnd, 0, 0, cube.IsComplete () ? "Complete!"
                                                : "         ");
    ::mvwprintw (_wnd, 1, 0, "Move:               ");
    ::wmove (_wnd, 1, 6);
    ::wrefresh (_wnd);

    unsigned count (0);

    while (true)
    {
        int ch = ::wgetch (_wnd);
        if (ch == 'q' || ch == 'Q')
            return -1;

        if (ch == KEY_MOUSE)
            return _ProcessMouse (cube, canvas);

        // Stack first digits together for repetition
        if (::isdigit (ch) && count < 999)
        {
            count *= 10;
            count += ch - '0';
            if (count > 0)
            {
                int y, x;
                getyx (_wnd, y, x);
                ::waddch (_wnd, ch);
                ::wmove (_wnd, y, x + 1);
                ::wrefresh (_wnd);
            }
        }

        switch (ch)
        {
        case 27:     // Escape
            return 0;
        case '#':
            if (!count)
                cube.Shuffle (20);
            else
                cube.Shuffle (count);
            return 0;
        case 'f':
        case 'F':
            cube.TurnFront (0, islower(ch));
            return 0;
        case 'b':
        case 'B':
            cube.TurnFront (-1, !islower(ch));
            return 0;
        //case 's':
        //case 'S':
        //    sscanf (move.c_str() + 1, "%d", &splice);
        //    cube.TurnSide (splice, islower(ch));
        //    break;
        case 't':
        case 'T':
            cube.TurnTop (0, islower(ch));
            return 0;
        case 'l':
        case 'L':
            cube.TurnSide (0, islower(ch));
            return 0;
        case 'r':
        case 'R':
            cube.TurnSide (-1, !islower(ch));
            return 0;
        case 'd':
        case 'D':
            cube.TurnTop (-1, !islower(ch));
            return 0;
        case 'x':
        case 'X':
            cube.Pitch (islower(ch));
            return 0;
        case 'y':
        case 'Y':
            cube.Yaw (islower(ch));
            return 0;
        case 'z':
        case 'Z':
            cube.Roll (islower(ch));
            return 0;
        case 'u':
            if (!count)
                cube.Undo (1);
            else
                cube.Undo (count);
            return 0;
        default:
            return 0;
        }
    }
}

int cControl::_ProcessMouse (cCube& cube, cCanvas const& canvas)
{
    MEVENT event;
    if (::getmouse (&event) != OK)
        return 0;

    if (!::wmouse_trafo (canvas.GetWnd(), &event.y, &event.x, FALSE))
        return 0;

    if (event.bstate & BUTTON1_PRESSED)
    {
        ::mvwprintw (_wnd, 2, 0, "Press Y:%d  X:%d    ", event.y, event.x);
        ::wrefresh (_wnd);
    }
    if (event.bstate & BUTTON1_RELEASED)
    {
        ::mvwprintw (_wnd, 2, 0, "Release Y:%d  X:%d   ", event.y, event.x);
        ::wrefresh (_wnd);
    }
    return 0;
}

// vim: set et ts=4 sw=4:

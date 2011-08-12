//
// Control.hh
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
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>

#pragma once

#ifndef WIN32
#  include <ncurses.h>
#else
#  include <curses.h>
#endif //WIN32

class cCube;
class cCanvas;

class cControl
{
public:
    cControl ();
    ~cControl ();

    int Process (cCube& cube,
                 cCanvas const& canvas);

private:
    WINDOW* _wnd;
    int _start_y;
    int _start_x;

    int _ProcessMouse (cCube& cube,
                       cCanvas const& canvas);
};

// vim: set et ts=4 sw=4:

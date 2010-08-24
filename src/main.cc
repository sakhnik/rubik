//
// main.cc
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
#include "Control.hh"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <ncursesw/ncurses.h>

using namespace std;

int main (int argc, char* argv[])
{
    srand ((unsigned)time(NULL));
    ::setlocale (LC_CTYPE, "");

    WINDOW* main_wnd = ::initscr();
    if (!main_wnd)
    {
        cerr << "Couldn't init screen" << endl;
        return 1;
    }

    // Destroy the window automatically
    struct sScopeExit
    {
        ~sScopeExit () { ::endwin (); }
    } scope_exit;

    if (!::has_colors())
    {
        cerr << "Your terminal doesn't support colours" << endl;
        return 1;
    }

    ::keypad (main_wnd, TRUE);
    ::raw ();
    ::noecho ();
    ::start_color ();
    ::init_pair (1, COLOR_RED, COLOR_BLACK);
    ::init_pair (2, COLOR_BLUE, COLOR_BLACK);
    ::init_pair (3, COLOR_GREEN, COLOR_BLACK);
    ::init_pair (4, COLOR_YELLOW, COLOR_BLACK);
    ::init_pair (5, COLOR_MAGENTA, COLOR_BLACK);
    ::init_pair (6, COLOR_CYAN, COLOR_BLACK);

    try
    {
        cCube cube (3);
        cCanvas canvas (cube.GetN(), 5, 0);
        cControl control;
        while (true)
        {
            cube.Draw (canvas);
            canvas.Render ();
            if (control.Process (cube))
                break;
        }
    }
    catch (std::exception const& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

// vim: set et ts=4 sw=4:

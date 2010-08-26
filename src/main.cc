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
#include <time.h>
#include <getopt.h>
#ifndef WIN32
#  include <ncursesw/ncurses.h>
#else
#  include <curses.h>
#endif //WIN32

using namespace std;

void Usage ()
{
    cerr << "rubik [--size|-s n]\n";
    cerr << "Play Rubik's cube of size n (default 3)" << endl;
}

int main (int argc, char* argv[])
{
    srand ((unsigned)time(NULL));
    ::setlocale (LC_CTYPE, "");

    unsigned size (3);

    while (true)
    {
        static struct option long_options[] =
        {
            { "help", no_argument, 0, 'h' },
            { "size", required_argument, 0, 's' },
            { 0, 0, 0, 0 }
        };

        int option_index = 0;
        int c = ::getopt_long (argc, argv, "h?s:",
                               long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
        case 'h':
        case '?':
            Usage ();
            return 1;
        case 's':
            if (1 != sscanf (optarg, "%u", &size))
            {
                cerr << "Invalid size `" << optarg << "'" << endl;
                return 1;
            }
            break;
        default:
            return 1;
        }
    }

    if (optind < argc)
    {
        cerr << "Unexpected arguments" << endl;
        return 1;
    }

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
        cCube cube (size);
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

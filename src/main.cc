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
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>

using namespace std;

void Usage ()
{
    cerr << "rubik [--size|-s n]\n";
    cerr << "Play Rubik's cube of size n (default 3)" << endl;
}

int main (int argc, char* argv[])
{
    srand ((unsigned)time(NULL));

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

    try
    {
        cCube cube (size);
        cCanvas canvas (cube.GetN());

        while (true)
        {
            cout << endl;
            if (cube.IsComplete())
                cout << "Complete!" << endl;
            cube.Draw (canvas);
            canvas.Render ();
            cout << "Move: ";
            string move;
            cin >> move;
            if (move.size() < 1)
                continue;
            char cmd = move[0];
            if (cmd == 'q' || cmd == 'Q')
                break;
            int splice (0);
            switch (cmd)
            {
            case '#':
                {
                    unsigned count = 20;
                    sscanf (move.c_str() + 1, "%d", &count);
                    cube.Shuffle (count);
                }
            case 'f':
            case 'F':
                sscanf (move.c_str() + 1, "%d", &splice);
                cube.TurnFront (splice, islower(cmd));
                break;
            case 'b':
            case 'B':
                sscanf (move.c_str() + 1, "%d", &splice);
                cube.TurnFront (-1, !islower(cmd));
                break;
            case 's':
            case 'S':
                sscanf (move.c_str() + 1, "%d", &splice);
                cube.TurnSide (splice, islower(cmd));
                break;
            case 't':
            case 'T':
                sscanf (move.c_str() + 1, "%d", &splice);
                cube.TurnTop (splice, islower(cmd));
                break;
            case 'l':
            case 'L':
                cube.TurnSide (0, islower(cmd));
                break;
            case 'r':
            case 'R':
                cube.TurnSide (-1, !islower(cmd));
                break;
            case 'd':
            case 'D':
                cube.TurnTop (-1, !islower(cmd));
                break;
            case 'x':
            case 'X':
                cube.Pitch (islower(cmd));
                break;
            case 'y':
            case 'Y':
                cube.Yaw (islower(cmd));
                break;
            case 'z':
            case 'Z':
                cube.Roll (islower(cmd));
                break;
            case 'u':
                {
                    unsigned count = 1;
                    sscanf (move.c_str() + 1, "%d", &count);
                    int c = cube.Undo (count);
                    if (c != count)
                        cout << "Reverted " << c << " moves" << endl;
                    break;
                }
            default:
                cout << "Huh?" << endl;
            }
        }
        cout << "Good bye!" << endl;
    }
    catch (std::exception const& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

// vim: set et ts=4 sw=4:

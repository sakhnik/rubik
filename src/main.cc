//
// main.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#include "Cube.hh"
#include "Canvas.hh"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main (int argc, char* argv[])
{
    srand ((unsigned)time(NULL));
    try
    {
        cCube cube (3);
        cCanvas canvas (cube.GetN());
        while (true)
        {
            cout << endl;
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

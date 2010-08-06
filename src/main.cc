//
// main.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#include "Cube.hh"
#include "Canvas.hh"
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
    try
    {
        cCube cube (3);
        cCanvas canvas (3);
        cube.Draw (canvas);
        canvas.Render ();
    }
    catch (std::exception const& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}

// vim: set et ts=4 sw=4:
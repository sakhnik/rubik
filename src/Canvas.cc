//
// Canvas.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#include "Canvas.hh"
#include <iostream>

using namespace std;

cCanvas::cCanvas (unsigned n)
    : _width (n * 4)
    , _height (n * 3)
    , _pixels (_width * _height, Colour::N)
{
}

void cCanvas::Render () const
{
    for (size_t i = 0; i != _pixels.size(); ++i)
    {
        char const* str = _pixels[i].GetChar();
        cout << str;
        if (i % _width == _width - 1)
            cout << "\n";
    }
    cout << endl;
}

void cCanvas::SetPixel (unsigned x, unsigned y, Colour colour)
{
    _pixels[y * _width + x] = colour;
}

// vim: set et ts=4 sw=4:

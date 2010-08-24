//
// Canvas.cc
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

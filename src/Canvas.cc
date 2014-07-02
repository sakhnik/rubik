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

#include <stdexcept>

using namespace std;

cCanvas::cCanvas (unsigned n,
                  unsigned y,
                  unsigned x,
                  const char *face)
    : _width (n * 4)
    , _height (n * 3)
    , _wnd (0)
    , _face (face)
{
    _wnd = ::newwin (_height, _width * 2, y, (COLS - 2*_width)/2);
    if (!_wnd)
        throw runtime_error ("Couldn't create canvas");
}

cCanvas::~cCanvas ()
{
    ::delwin (_wnd);
}

void cCanvas::Render () const
{
    ::wmove (_wnd, 0, 0);
    ::wrefresh (_wnd);
}

void cCanvas::SetPixel (unsigned x, unsigned y, Colour colour)
{
    ::wattron (_wnd, COLOR_PAIR (colour.GetNumber ()));
    ::mvwprintw (_wnd, y, x * 2, "%s ", _face);
    ::wattroff (_wnd, COLOR_PAIR (colour.GetNumber ()));
}

// vim: set et ts=4 sw=4:

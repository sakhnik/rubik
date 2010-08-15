//
// Colour.cc
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
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>

#include "Colour.hh"

using namespace std;

char const* Colour::GetChar () const
{
    switch (_t)
    {
    case N: return "  ";
    case A: return "\033[49;31m█▌\033[0m";
    case B: return "\033[49;32m█▌\033[0m";
    case C: return "\033[49;33m█▌\033[0m";
    case D: return "\033[49;34m█▌\033[0m";
    case E: return "\033[49;35m█▌\033[0m";
    case F: return "\033[49;36m█▌\033[0m";
    }
    return "  ";
}

// vim: set et ts=4 sw=4:

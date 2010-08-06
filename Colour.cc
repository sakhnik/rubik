//
// Colour.cc
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

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

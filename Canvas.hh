//
// Canvas.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

#include "Colour.hh"
#include <vector>

class cCanvas
{
public:
    cCanvas (unsigned n);

    void Render () const;
    void SetPixel (unsigned x, unsigned y, Colour colour);

private:
    unsigned _width;
    unsigned _height;
    std::vector<Colour> _pixels;
};

// vim: set et ts=4 sw=4:

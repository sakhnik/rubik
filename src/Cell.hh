//
// Cell.hh
//
//     Created: 04.08.2010
//      Author: A. Sakhnik
//

#pragma once

#include "Vector.hh"
#include "Colour.hh"

class cCell
{
public:
    cCell (cVector const& pos,
           cVector const& i,
           cVector const& j,
           cVector const& k);

    cVector const& GetPos() const { return _pos; }

    Colour GetColour (cVector const& direction) const;

    void RotateX ();
    void RotateY ();
    void RotateZ ();

private:
    cVector _pos;

    cVector _i;
    cVector _j;
    cVector _k;
};

// vim: set et ts=4 sw=4:

//
//  Cell.cpp
//  Fluid
//
//  Created by Tellart on 12/13/13.
//
//

#include "Cell.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

using namespace ci;
using std::vector;

Cell::Cell( Vec2f topLeft, Vec2i indices, float cellSize )
{
    mTopLeft = topLeft;
    mBottomRight = Vec2f( mTopLeft.x + cellSize, mTopLeft.y + cellSize );
    mIndices = indices;
}

void Cell::draw()
{
    Rectf rect( mTopLeft.x, mTopLeft.y, mBottomRight.x, mBottomRight.y );
    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
    gl::drawSolidRect( rect );
}

void Cell::addParticle()
{
    
}

void Cell::deleteParticle()
{
    
}
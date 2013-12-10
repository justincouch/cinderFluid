//
//  Particle.cpp
//  Fluid
//
//  Created by Tellart on 12/10/13.
//
//

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

using namespace ci;
using std::vector;

Particle::Particle()
{
    float x = Rand::randFloat( app::getWindowWidth() );
    float y = Rand::randFloat( app::getWindowHeight() );
    
    mPos = Vec2f( x, y );
    mVel = Rand::randVec2f();
    mAcc = Vec2f::zero();
    
    mRadius = 1.0f;
}

void Particle::update( const ci::Vec2i &windowSize )
{
    mPos += mVel;
    
    if ( mPos.x < mRadius || mPos.x > windowSize.x-mRadius ){
        if ( mPos.x < mRadius ) mPos.x = mRadius;
        if ( mPos.x > windowSize.x-mRadius ) mPos.x = windowSize.x-mRadius;
        mVel.x *= -1;
    }
    if ( mPos.y < mRadius || mPos.y > windowSize.y-mRadius ){
        if ( mPos.y < mRadius ) mPos.y = mRadius;
        if ( mPos.y > windowSize.y-mRadius ) mPos.y = windowSize.y-mRadius;
        mVel.y *= -1;
    }
}

void Particle::draw()
{
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    gl::drawSolidCircle( mPos, mRadius );
}
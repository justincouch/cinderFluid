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
using std::list;
using namespace std;

Particle::Particle()
{
    float x = Rand::randFloat( app::getWindowWidth()/2 );
    float y = Rand::randFloat( app::getWindowHeight() );
    
    mPos = Vec2f( x, y );
    mPrevPos = mPos;
    mVel = Rand::randVec2f() * 1.0f;
    mAcc = Vec2f::zero();
    
    mDecay = 0.99f;
    
    mRadius = 4.0f;
}

void Particle::update()
{
    mPos += mVel;
}

void Particle::saveLastPosition()
{
    mPrevPos = mPos;
}

void Particle::computeNextVelocity( const ci::Vec2i &windowSize )
{
    mVel = ( mPos - mPrevPos );
    
    if ( mPos.x < mRadius || mPos.x > windowSize.x-mRadius ){
        if ( mPos.x < mRadius ) mPos.x = mRadius;
        if ( mPos.x > windowSize.x-mRadius ) mPos.x = windowSize.x-mRadius;
        mVel.x *= -0.25;
    }
    if ( mPos.y < mRadius || mPos.y > windowSize.y-mRadius ){
        if ( mPos.y < mRadius ) mPos.y = mRadius;
        if ( mPos.y > windowSize.y-mRadius ) mPos.y = windowSize.y-mRadius;
        mVel.y *= -0.25;
    }
    //mVel *= mDecay;
}

void Particle::addNeighbor( Particle *p )
{
    mNeighbors.push_back( *p );
}

void Particle::addForwardNeighbor( Particle *p )
{
    mForwardNeighbors.push_back( *p );
}

void Particle::draw( float neighborhood, float restDensity )
{
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    for ( list<Particle>::iterator p = mNeighbors.begin(); p != mNeighbors.end(); ++p ){
        //gl::drawLine( mPos, p->mPos );
    }
    
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    gl::drawSolidCircle( mPos, mRadius );
    
    glColor4f( 0.25f, 0.25f, 1.0f, 1.0f );
    gl::drawStrokedCircle( mPos, abs(mDensity * 1) );
    
    glColor4f( 0.25f, 0.25f, 1.0f, 1.0f );
    gl::drawStrokedCircle( mPos, abs(restDensity * 1) );
    
    glColor4f( 0.25f, 1.0f, 1.0f, 1.0f );
    gl::drawStrokedCircle( mPos, mNearDensity * 1 );
    
    glColor4f( 1.0f, 0.25f, 0.25f, 1.0f );
    gl::drawStrokedCircle( mPos, abs(mPressure * 10) );
    
    glColor4f( 0.25f, 1.0f, 0.25f, 1.0f );
    gl::drawStrokedCircle( mPos, mNearPressure * 100 );
    
    glColor4f( 0.5f, 0.5f, 0.5f, 0.25f );
    //gl::drawStrokedCircle( mPos, neighborhood );
    
    mNeighbors.clear();
    mForwardNeighbors.clear();
}

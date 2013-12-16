//
//  Spring.cpp
//  Fluid
//
//  Created by Tellart on 12/14/13.
//
//

#include "Spring.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

using namespace ci;
using std::vector;
using std::list;
using namespace std;

Spring::Spring()
{
}

Spring::Spring( Particle *particleA, Particle *particleB )
{
    pA = particleA;
    pB = particleB;
    
    mRestLength = 100.0f;
    mRestLengthSqrd = mRestLength * mRestLength;
    mSpringStrength = 0.1f;
    
    mIsActive = false;
}

void Spring::update( float springStrength )
{
    //std::cout << "updating spring";
    mSpringStrength = springStrength;
    ci::Vec2f dir = pA->mPos - pB->mPos;
    float dirLength = dir.length();
    //float dirLengthSqrd = dir.lengthSquared();
    ci::Vec2f D = mSpringStrength * ( 1 - mRestLength / dirLength ) * ( mRestLength - dirLength ) * dir.normalized();
    //pA->mPos -= D/2;
    //pB->mPos += D/2;
    
    //this->draw();
}

void Spring::draw()
{
    //std::cout << pA->mPos;
    glColor4f( 1.0f, 0.25f, 0.25f, 1.0f );
    gl::drawLine( this->pA->mPos, this->pB->mPos );
}

void Spring::makeActive()
{
    //std::cout << "making active";
    mIsActive = true;
    //std::cout << mIsActive;
}

void Spring::kill()
{
    //std::cout << "KILLING!";
    mIsActive = false;
}

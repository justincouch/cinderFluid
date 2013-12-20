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

Spring::Spring( Particle *particleA, Particle *particleB, float neighborhood )
{
    this->particleA = particleA;
    this->particleB = particleB;
    
    
    mRestLength = neighborhood;
    mRestLengthSqrd = mRestLength * mRestLength;
    mSpringStrength = 0.3f;
    mYieldRatio = 0.01f;
    mPlasticityConstant = 0.3f;
    
    mIsActive = false;
}

void Spring::update( float springStrength, float neighborhood )
{
    mSpringStrength = springStrength;
    //std::cout << "restLengthPRE: " << mRestLength << "\n";
    ci::Vec2f dir = particleA->mPos - particleB->mPos;
    float dirLength = dir.length();
    float dirLengthSqrd = dir.lengthSquared();
    
    
    float d = mYieldRatio * mRestLength;
    if ( dirLength > mRestLength + d ){
        mRestLength += mPlasticityConstant * ( dirLength - mRestLength - d );
    }
    else if ( dirLength < mRestLength - d ){
        mRestLength -= mPlasticityConstant * ( mRestLength - d - dirLength );
    }
    
    
    ci::Vec2f D = mSpringStrength * ( 1 - mRestLength / neighborhood ) * ( mRestLength - dirLength ) * dir.normalized();
    //ci::Vec2f D = mSpringStrength * ( mRestLength - dirLength ) * dir.normalized();
    
    //std::cout << "dist: " << dirLength << ", restLength: " << mRestLength << ", d+: " << mRestLength+d << ", d-: " << mRestLength-d << ", D: " << D << "\n";
    
    particleA->mPos -= D/2;
    particleB->mPos += D/2;
    
    //this->draw();
}

void Spring::draw()
{
    //std::cout << "AAAAAAAAAAA" << mIsActive << "\n";
    glColor4f( 1.0f, 0.25f, 0.25f, 1.0f );
    gl::drawLine( particleA->mPos, particleB->mPos );
}

void Spring::makeActive()
{
    mIsActive = 1;
    std::cout << "making active->" << mIsActive << "\n";
}

void Spring::kill()
{
    mIsActive = 0;
    std::cout << "KILLING!->" << mIsActive << "\n";
}

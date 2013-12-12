//
//  ParticleController.cpp
//  Fluid
//
//  Created by Tellart on 12/10/13.
//
//

#include "ParticleController.h"
#include "cinder/Vector.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}

void ParticleController::update( const ci::Vec2i &windowSize, float gravity, float neighborhood )
{
    applyGravity( gravity );
    
    applyViscosity( neighborhood );
    
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->update( windowSize );
    }
}

void ParticleController::draw()
{
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw();
    }
}

void ParticleController::addParticles( int amt )
{
    for( int i=0; i<amt; i++ ){
        mParticles.push_back( Particle( ) );
    }
}

void ParticleController::applyGravity( float gravity )
{
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->mVel.y += gravity;
    }
}

void ParticleController::applyViscosity( float neighborhood )
{
    float neighborhoodSqrd = neighborhood * neighborhood;
    float viscosityAlpha = 0.1;
    float viscosityBeta = 0.001;
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
        list<Particle>::iterator p2 = p1;
		for( ++p2; p2 != mParticles.end(); ++p2 ) {
            Vec2f rij = p1->mPos - p2->mPos;
            float rijSqrd = rij.lengthSquared();
            float q = rijSqrd / neighborhoodSqrd;
            if ( q < 1.0f ){
                float u = ( p1->mVel - p2->mVel ).dot( rij.normalized() );
                if ( u > 0 ){
                    Vec2f I = ( 1 - q ) * ( ( viscosityAlpha * u ) + ( viscosityBeta * u * u ) ) * rij.normalized();
                    p1->mVel -= I/2;
                    p2->mVel += I/2;
                }
            }
        }
    }
}





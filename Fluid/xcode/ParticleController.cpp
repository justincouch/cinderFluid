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

void ParticleController::update( const ci::Vec2i &windowSize )
{
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





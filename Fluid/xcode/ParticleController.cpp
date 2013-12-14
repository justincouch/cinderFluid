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

void ParticleController::update( const ci::Vec2i &windowSize, float gravity, float neighborhood, float viscositySigma, float viscosityBeta, float mRestDensity, float mStiffnessParameter, float mStiffnessParameterNear )
{
    checkForNeighbors( neighborhood );
    
    applyGravity( gravity );
    
    applyViscosity( neighborhood, viscositySigma, viscosityBeta );
    
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->saveLastPosition();
    }
    
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->update();
    }
    
    //adjustSprings
    //applySpringDisplacements
    doubleDensityRelaxation( neighborhood, mRestDensity, mStiffnessParameter, mStiffnessParameterNear );
    //resolveCollisions
    
    //p->updateVelocity();
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->computeNextVelocity( windowSize );
    }
}

void ParticleController::doubleDensityRelaxation( float neighborhood, float restDensity, float stiffnessParameter, float stiffnessParameterNear )
{
    float neighborhoodSqrd = neighborhood * neighborhood;
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
		p1->mDensity = 0.0f;
        p1->mNearDensity = 0.0f;
        for ( list<Particle>::iterator p2 = p1->mNeighbors.begin(); p2 != p1->mNeighbors.end(); ++p2 ){
            Vec2f rij = p1->mPos - p2->mPos;
            float rijSqrd = rij.lengthSquared();
            float q = rijSqrd / neighborhoodSqrd;
            p1->mDensity += ( 1-q ) * ( 1-q );
            p1->mNearDensity += ( 1-q ) * ( 1-q ) * ( 1-q );
        }
        p1->mPressure = stiffnessParameter * ( p1->mDensity - restDensity );
        p1->mNearPressure = stiffnessParameterNear * p1->mNearDensity;
        Vec2f dpos = Vec2f::zero();
        for ( list<Particle>::iterator p2 = p1->mNeighbors.begin(); p2 != p1->mNeighbors.end(); ++p2 ){
            Vec2f rij = p1->mPos - p2->mPos;
            float rijSqrd = rij.lengthSquared();
            float q = rijSqrd / neighborhoodSqrd;
            Vec2f DPos = rij.normalized() * ( p1->mPressure * ( 1-q ) + p1->mNearPressure * ( 1-q ) * ( 1-q ) );
            p2->mPos += DPos/2;
            dpos -= DPos/2;
        }
        p1->mPos += dpos;
    }

}

void ParticleController::checkForNeighbors( float neighborhood )
{
    float neighborhoodSqrd = neighborhood * neighborhood;
    Particle *it;
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
        list<Particle>::iterator p2 = p1;
		for( ++p2; p2 != mParticles.end(); ++p2 ) {
            Vec2f rij = p1->mPos - p2->mPos;
            float rijSqrd = rij.lengthSquared();
            float q = rijSqrd / neighborhoodSqrd;
            it = &*p2;
            if ( q < 1.0f ){
                p1->addNeighbor( *it );
            }
        }
    }
}

void ParticleController::draw( float neighborhood )
{
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw( neighborhood );
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

void ParticleController::applyViscosity( float neighborhood, float viscositySigma, float viscosityBeta )
{
    float neighborhoodSqrd = neighborhood * neighborhood;
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
		for ( list<Particle>::iterator p2 = p1->mNeighbors.begin(); p2 != p1->mNeighbors.end(); ++p2 ){
            Vec2f rij = p1->mPos - p2->mPos;
            float rijSqrd = rij.lengthSquared();
            float u = ( p1->mVel - p2->mVel ).dot( rij.normalized() );
            float q = rijSqrd / neighborhoodSqrd;
            if ( u > 0 ){
                Vec2f I = ( 1 - q ) * ( ( viscositySigma * u ) + ( viscosityBeta * u * u ) ) * rij.normalized();
                p1->mVel -= I/2;
                p2->mVel += I/2;
            }
        }
    }
}





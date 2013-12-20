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
using std::vector;

ParticleController::ParticleController()
{
}

void ParticleController::update( const ci::Vec2i &windowSize, float gravity, float neighborhood, float viscositySigma, float viscosityBeta, float mRestDensity, float mStiffnessParameter, float mStiffnessParameterNear, float mSpringStiffness )
{
    checkForNeighbors( neighborhood );
    //updateSprings( mSpringStiffness, neighborhood );
    applyGravity( gravity );
    
    applyViscosity( neighborhood, viscositySigma, viscosityBeta );
    
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->saveLastPosition();
    }
    
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->update();
    }
    
    updateSprings( mSpringStiffness, neighborhood );
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

void ParticleController::updateSprings( float springStrength, float neighborhood )
{
    //std::cout << "mSpring size: " << mSprings.size();
    /*
    for ( int i=0; i<mSprings.size(); i++ ){
        Spring s = mSprings.at( i );
        std::cout << i << ": " << s.pA->mPos << ": " << s.pB->mPos << ": " << s.mIsActive << "\n";
        //if ( s.mIsActive == 1 ){
            //std::cout << "YAY";
            s.update( springStrength );
            //s->draw();
        //}
    }
    */
    for ( vector<Spring*>::iterator s = mSprings.begin(); s != mSprings.end(); ++s ){
        //std::cout << s->mIsActive;
        //if ( s->mIsActive == true ){
        //std::cout << "YAY";
        (*s)->update( springStrength, neighborhood );
        if ( (*s)->mRestLength > neighborhood ){
            destroySpring( *s );
        }
        //(*s)->draw();
        //}
    }
}

void ParticleController::checkForNeighbors( float neighborhood )
{
    int ctr1 = 0;
    int ctr2 = 0;
    float neighborhoodSqrd = neighborhood * neighborhood;
    int scnt = 0;
    Spring *s1;
    Particle *it;
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
        if ( ctr1 < mParticles.size() - 1 ){
            
        
        for ( list<Particle>::iterator p2 = mParticles.begin(); p2 != mParticles.end(); ++p2 ){
            //std::cout << "s: " << scnt << "\n";
            //std::cout << "1: " << ctr1 << "\n";
            //std::cout << "2: " << ctr2 << "\n";
            if ( ctr1 != ctr2 ){
                Vec2f rij = p1->mPos - p2->mPos;
                float rijSqrd = rij.lengthSquared();
                float q = rijSqrd / neighborhoodSqrd;
                it = &*p2;
                //s1 = mSprings.at( scnt );
                //std::cout << "before: " << s1.mIsActive << "\n";
                /*
                std::cout << "p1: ";
                std::cout << p1->mPos;
                std::cout << " p2: ";
                std::cout << p2->mPos << "\n";
                std::cout << "sA: ";
                std::cout << s1.pA->mPos;
                std::cout << " sb: ";
                std::cout << s1.pB->mPos << "\n\n";
                 */
                Particle *part1 = &*p1;
                Particle *part2 = &*p2;
                
                if ( q < 1.0f ){
                    p1->addNeighbor( it );
                    if ( ctr2 > ctr1 ){
                        p1->addForwardNeighbor( it );
                        //std::cout << scnt << "\n";
                        s1 = new Spring( part1, part2, neighborhood );
                        //std::cout << scnt << ": " << s1->particleA->mPos << ": " << s1->particleB->mPos << "\n";
                        addSpring( s1 );
                        //s1.makeActive();
                        //s1.mIsActive = true;
                    }
                }
                else {
                    //std::cout << "FALSE";
                    if ( ctr2 > ctr1 ){
                        //std::cout << scnt << "\n";
                        //s1 = new Spring( part1, part2, neighborhood );
                        //destroySpring( s1 );
                        //s1.kill();
                        //s1.mIsActive = false;
                    }
                }
                //std::cout << "after: " << s1.mIsActive << "\n";
                
                if ( ctr2 > ctr1 ){
                   scnt++; // springs are forward counting
                }
            }
            ctr2++;
        }
        }
        ctr1++;
        ctr2 = 0;
        //scnt++;
    }
}

void ParticleController::draw( float neighborhood, float restDensity )
{
    for ( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
        p->draw( neighborhood, restDensity );
    }
    
    //std::cout << "mSpring size: " << mSprings.size() << "\n";
    //std::cout << mSprings.at(281).mIsActive << "\n";
    for ( vector<Spring*>::iterator s = mSprings.begin(); s != mSprings.end(); ++s ){
        //std::cout << s->mIsActive;
        //if ( s->mIsActive == true ){
            //std::cout << "YAY";
            //(*s)->update( springStrength );
            (*s)->draw();
        //}
    }
}

void ParticleController::addParticles( int amt )
{
    for( int i=0; i<amt; i++ ){
        mParticles.push_back( Particle( ) );
    }
}

void ParticleController::addSprings()
{
    for ( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
        Particle *itA = &*p1;
        list<Particle>::iterator p2 = p1;
		for( ++p2; p2 != mParticles.end(); ++p2 ) {
            Particle *itB = &*p2;
            //mSprings.push_back( Spring( itA, itB ) );
        }
    }
}

void ParticleController::addSpring( Spring *spring )
{
    //std::vector<Spring*>::iterator it = std::find( mSprings.begin(), mSprings.end(), spring );
    //std::cout << *it;
    //mSprings.push_back( spring );
    bool sprAlreadyExists = false;
    
    for ( vector<Spring*>::iterator s = mSprings.begin(); s != mSprings.end(); ++s ){
        //std::cout << spring->particleA->mPos;
        //std::cout << (*s)->particleA->mPos;
        if ( ( spring->particleA->mPos == (*s)->particleA->mPos ) && ( spring->particleB->mPos == (*s)->particleB->mPos ) ){
            sprAlreadyExists = true;
            break;
        }
    }
     
    
    if ( sprAlreadyExists == true ) {
        //std::cout << "spring already exists" << "\n";
    }
    else if ( sprAlreadyExists == false ) {
        //std::cout << "adding spring" << "\n";
        mSprings.push_back( spring );
    }
}

void ParticleController::destroySpring( Spring *spring )
{
    bool sprAlreadyExists = false;
    vector<Spring*>::iterator sIT;
    for ( vector<Spring*>::iterator s = mSprings.begin(); s != mSprings.end(); ++s ){
        //std::cout << spring->particleA->mPos;
        //std::cout << (*s)->particleA->mPos;
        if ( ( spring->particleA->mPos == (*s)->particleA->mPos ) && ( spring->particleB->mPos == (*s)->particleB->mPos ) ){
            sprAlreadyExists = true;
            sIT = s;
            break;
        }
    }
    if ( sprAlreadyExists == true ) {
        //std::cout << "mSpring size before: " << mSprings.size() << "\n";
        //std::cout << "TERMINATE!!!" << "\n";
        mSprings.erase( sIT );
        //std::cout << "mSpring size after: " << mSprings.size() << "\n";
    }
    else if ( sprAlreadyExists == false ) {
        //std::cout << "can't destroy. not there" << "\n";
    }
    
    /*
    std::vector<Spring*>::iterator it = std::find( mSprings.begin(), mSprings.end(), spring );
    //delete *it;
    //mSprings.erase( it );
    
    if( it != mSprings.end() ) {
        std::cout << "mSpring size before: " << mSprings.size() << "\n";
        std::cout << "TERMINATE!!!" << "\n";
        mSprings.erase( it );
        std::cout << "mSpring size after: " << mSprings.size() << "\n";
    } else {
        std::cout << "can't destroy. not there" << "\n";
    }
     */
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





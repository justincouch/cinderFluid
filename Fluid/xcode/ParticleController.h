//
//  ParticleController.h
//  Fluid
//
//  Created by Tellart on 12/10/13.
//
//

#ifndef __Fluid__ParticleController__
#define __Fluid__ParticleController__

#include <iostream>
#include <list>

#include "Particle.h"
#include "Spring.h"


class ParticleController {
  public:
    ParticleController();
    
    void update( const ci::Vec2i &windowSize, float gravity, float neighborhood, float viscositySigma, float viscosityBeta, float mRestDensity, float mStiffnessParameter, float mStiffnessParameterNear, float mSpringStiffness );
    void draw( float neighborhood, float restDensity );
    
    void addParticles( int amt );
    void addSprings();
    void updateSprings( float springStrength );
    void checkForNeighbors( float neighborhood );
    void applyGravity( float gravity );
    void applyViscosity( float neighborhood, float viscositySigma, float viscosityBeta );
    void doubleDensityRelaxation( float neighborhood, float restDensity, float stiffnessParameter, float stiffnessParameterNear );
    
    int mNumParticles;
    int mNumSprings;
    std::list<Particle>	mParticles;
    std::list<Spring>	mSprings;
};

#endif /* defined(__Fluid__ParticleController__) */

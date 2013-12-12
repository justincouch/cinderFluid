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

#endif /* defined(__Fluid__ParticleController__) */

class ParticleController {
public:
    ParticleController();
    
    void update( const ci::Vec2i &windowSize, float gravity, float neighborhood );
    void draw();
    
    void addParticles( int amt );
    
    void applyGravity( float gravity );
    void applyViscosity( float neighborhood );
    
    int mNumParticles;
    std::list<Particle>	mParticles;
};

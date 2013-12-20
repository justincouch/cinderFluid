//
//  Spring.h
//  Fluid
//
//  Created by Tellart on 12/14/13.
//
//

#ifndef __Fluid__Spring__
#define __Fluid__Spring__

#include <iostream>

#include "cinder/Vector.h"
#include "Particle.h"


class Spring {
  public:
    Spring();
    Spring( Particle *particleA, Particle *particleB, float neighborhood );
    
    void update( float springStiffness, float neighborhood );
    void draw();
    
    void makeActive();
    void kill();
    
    Particle *particleA;
    Particle *particleB;
    
    float   mRestLength;
    float   mRestLengthSqrd;
    float   mYieldRatio;
    float   mSpringStrength;
    float   mPlasticityConstant;
    bool    mIsActive;
};

#endif /* defined(__Fluid__Spring__) */

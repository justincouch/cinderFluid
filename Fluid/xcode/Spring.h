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
    Spring( Particle *pA, Particle *pB );
    
    void update( float springStiffness );
    void draw();
    
    void makeActive();
    void kill();
    
    Particle *pA;
    Particle *pB;
    
    float   mRestLength;
    float   mRestLengthSqrd;
    float   mSpringStrength;
    bool    mIsActive;
};

#endif /* defined(__Fluid__Spring__) */

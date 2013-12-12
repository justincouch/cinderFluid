//
//  Particle.h
//  Fluid
//
//  Created by Tellart on 12/10/13.
//
//

#ifndef __Fluid__Particle__
#define __Fluid__Particle__

#include <iostream>

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <vector>

#endif /* defined(__Fluid__Particle__) */

class Particle {
public:
    Particle();
    
    void update( const ci::Vec2i &windowSize );
    void draw();
    
    ci::Vec2f   mPos;
    ci::Vec2f   mVel;
    ci::Vec2f   mAcc;
    
    float       mRadius;
};

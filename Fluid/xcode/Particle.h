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
#include <algorithm>

#endif /* defined(__Fluid__Particle__) */

class Particle {
  public:
    Particle();
    
    void update();
    void draw( float neighborhood );
    void addNeighbor( Particle p );
    void saveLastPosition();
    void computeNextVelocity( const ci::Vec2i &windowSize );
    
    ci::Vec2f   mPos;
    ci::Vec2f   mPrevPos;
    ci::Vec2f   mVel;
    ci::Vec2f   mAcc;
    
    float       mDensity;
    float       mNearDensity;
    float       mPressure;
    float       mNearPressure;
    
    float       mRadius;
    
    std::list<Particle>	mNeighbors;
};

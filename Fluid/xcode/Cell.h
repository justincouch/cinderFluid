//
//  Cell.h
//  Fluid
//
//  Created by Tellart on 12/13/13.
//
//

#ifndef __Fluid__Cell__
#define __Fluid__Cell__

#include <iostream>
#include <list>
#include <vector>

#include "Particle.h"

#endif /* defined(__Fluid__Cell__) */

class Cell {
  public:
    Cell();
    Cell( ci::Vec2f topLeft, ci::Vec2i indices, float cellSize );
    
    void draw();
    
    void addParticle();
    void deleteParticle();
    
    ci::Vec2f mTopLeft;
    ci::Vec2f mBottomRight;
    ci::Vec2i mIndices;
    
    std::list<Particle>	mParticles;
};

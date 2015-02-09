//
//  Mover.h
//  NOC_w2_4
//
//  Created by Nick on 2/8/15.
//
//

#ifndef __NOC_w2_4__Mover__
#define __NOC_w2_4__Mover__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
//#include "Attractor.h"
#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class Mover {
public:
    Mover(float m, float x, float y, float z);
    
    ci::Vec3f mPos, mVel, mAcc;
    gl::Material gMat;
    float mMass;
    void update();
    void applyForce(ci::Vec3f force);
    void render();
    void avoidAtt();
    void avoidWalls();
};


#endif /* defined(__NOC_w2_4__Mover__) */

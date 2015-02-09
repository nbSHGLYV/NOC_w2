//
//  Attractor.h
//  NOC_w2_4
//
//  Created by Nick on 2/8/15.
//
//

#ifndef __NOC_w2_4__Attractor__
#define __NOC_w2_4__Attractor__

#include <stdio.h>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
#include "cinder/Perlin.h"
#include "Mover.h"

class Attractor {
public:
    Attractor(float m, float x, float y, float z);
    
    ci::Vec3f aPos;
    ci::Vec3f attract(const Mover &mMovers);
    ci::Vec3f noise;
    Perlin mPerlin;
    ci::gl::Material aMat;
    float aMass;
    float aGrav;
    void update();
    void obeyBounds();
    void render();
};

#endif /* defined(__NOC_w2_4__Attractor__) */

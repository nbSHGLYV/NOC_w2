//
//  Mover.cpp
//  NOC_w2_4
//
//  Created by Nick on 2/8/15.
//
//

#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
//#include "Attractor.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Mover::Mover(float m, float x, float y, float z):
    mMass(m),
    mPos(Vec3f(x,y,z)),
    mVel(Vec3f(0.f, 0.f, 0.f)),
    mAcc(Vec3f(0.f, 0.f, 0.f))
{
    gMat.setDiffuse( ColorA( 1.0f, 1.0f, 0.0f, 0.25f ) );
    gMat.setSpecular( Color::white() );
    gMat.setEmission( Color::black() );
    gMat.setShininess( 32.0f );
}

void Mover::applyForce(Vec3f force){
    Vec3f f = force/mMass;
    mAcc += f;
}

void Mover::update(){
    mVel += mAcc;
    float x = mVel.x;
    x = constrain(x, -10.f, 10.f);
    float y = mVel.y;
    y = constrain(y, -10.f, 10.f);
    float z = mVel.z;
    z = constrain(z, -10.f, 10.f);
    mVel = Vec3f(x,y,z);
    mPos += mVel;
    mAcc *= 0;
}

void Mover::render(){
    gl::color( Color(0, 0, 0) );
    gl::drawSphere(mPos, mMass/2, 50);
}

void Mover::avoidWalls(){
    
    float w = getWindowWidth();
    float h = getWindowHeight();
    if (mPos.x > w){
        mVel.x *= -1.;
        mPos.x = w;
    }
    else if (mPos.x < 0){
        mVel.x *= -1.;
        mPos.x = 0;
    }
    if (mPos.y > h){
        mVel.y *= -1.;
        mPos.y = h;
    }
    else if (mPos.y < 0){
        mVel.y *= -1.;
        mPos.y = 0;
    }
    if (mPos.z > 200){
        mVel.z *= -1.;
        mPos.z = 200;
    }
    else if (mPos.z < -200){
        mVel.z *= -200;
    }
    
}

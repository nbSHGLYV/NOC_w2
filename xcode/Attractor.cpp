//
//  Attractor.cpp
//  NOC_w2_4
//
//  Created by Nick on 2/8/15.
//
//

#include "cinder/app/AppNative.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"
#include "cinder/Perlin.h"
#include "Attractor.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Attractor::Attractor(float m, float x, float y, float z):
    aMass(m),
    aGrav(float(1.5f)),
    aPos(Vec3f(x, y, z))
    //noise(Vec3f(0.f,0.f,0.f));
{
    aMat.setDiffuse(ColorA(1, 1, 1, 1));
    aMat.setSpecular(Color::white());
    aMat.setEmission(Color::black());
    aMat.setShininess(16.0f);
    mPerlin = Perlin();

}

Vec3f Attractor::attract(const Mover &mMovers){
    Vec3f force = aPos - mMovers.mPos;
    float d = force.length();
    d = constrain(d, 5.f, 15.f);
    force.normalize();
    float strength = (aGrav * aMass * mMovers.mMass)/(d*d);
    force *= strength;
    return force;
}

void Attractor::update(){
    float nX = aPos.x * 0.005f;
    float nY = aPos.y * 0.005f;
    float nZ = app::getElapsedSeconds() * 0.1f;
    Vec3f v(nX, nY, nZ);
    float noise = mPerlin.fBm(v) * 200.f;
    aPos.x += noise;
    aPos.y += noise;
    aPos.z += noise;
}

void Attractor::render(){
    gl::drawSphere(aPos, aMass/32, 100);
    
}
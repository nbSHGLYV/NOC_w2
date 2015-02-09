#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "Mover.h"
#include "Attractor.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_w2_4App : public AppNative {
public:
    void prepareSettings( Settings *settings );
    void setup();
    void update();
    void draw();
    void keyDown( KeyEvent event );
    vector<Attractor> mAttractors;
    vector<Mover> mMovers;
    vector<float> attractorDist;
    int numMov = 128;
    int numAtt = 3;
    float camX = 0;
    float camY = 0;
    float camZ = -1000;
};

void NOC_w2_4App::prepareSettings( Settings *settings ){
    
    settings->setWindowSize(800, 600);
    settings->enableHighDensityDisplay();
    //gl::enableAlphaBlending();
    
}

void NOC_w2_4App::setup() {
    int w = getWindowWidth();
    int h = getWindowHeight();
    
    camX = w;
    camY = h;
    
    mAttractors = vector<Attractor>();
    mMovers = vector<Mover>();
    attractorDist = vector<float>(9);
    for (int i = 0; i < numAtt; i++){
        mAttractors.push_back(Attractor(128,
                                        Rand::randFloat((h/8),((7*h)/8)),
                                        Rand::randFloat((w/8),((7*w)/8)),
                                        Rand::randFloat(-10,10)));
    }
    
    for (int i = 0; i < mAttractors.size(); i++){
        console() << mAttractors[i].aMass << std::endl;
    }
    
    for (int i = 0; i < numMov; i++){
        mMovers.push_back(Mover(randFloat(4,32),
                                randFloat(0.f,getWindowWidth()),
                                randFloat(getWindowHeight()/2,getWindowHeight()),
                                randFloat(-10.f,10.f)));
    }
    
}

void NOC_w2_4App::update() {
    
    console() << "# attractror distances" << attractorDist.size() << std::endl;
    
    
    attractorDist[0] = abs(mAttractors[0].aPos.x - mAttractors[1].aPos.x); //d01x
    attractorDist[1] = abs(mAttractors[0].aPos.y - mAttractors[1].aPos.y); //d01y
    attractorDist[2] = abs(mAttractors[0].aPos.z - mAttractors[1].aPos.z); //d01z
    attractorDist[3] = abs(mAttractors[0].aPos.x - mAttractors[2].aPos.x); //d02x
    attractorDist[4] = abs(mAttractors[0].aPos.y - mAttractors[2].aPos.y); //d02y
    attractorDist[5] = abs(mAttractors[0].aPos.z - mAttractors[2].aPos.z); //do2z
    attractorDist[6] = abs(mAttractors[1].aPos.x - mAttractors[2].aPos.x); //d12x
    attractorDist[7] = abs(mAttractors[1].aPos.y - mAttractors[2].aPos.y); //d12y
    attractorDist[8] = abs(mAttractors[1].aPos.z - mAttractors[2].aPos.z); //d12z
    
    
    // d01x
    if (attractorDist[0] >= 20.f && mAttractors[0].aPos.x > mAttractors[1].aPos.x){
        mAttractors[1].aPos.x ++;
    }
    if (attractorDist[0] >= 20.f && mAttractors[0].aPos.x > mAttractors[1].aPos.x){
        mAttractors[1].aPos.x ++;
    }
    else{
       mAttractors[1].aPos.x --;
    }
    // d01y
    if (attractorDist[1] >= 20.f && mAttractors[0].aPos.y > mAttractors[1].aPos.y){
        mAttractors[1].aPos.y ++;
    }
    else{
        mAttractors[1].aPos.y --;
    }
    // d01z
    if (attractorDist[2] >= 20.f && mAttractors[0].aPos.z > mAttractors[1].aPos.z){
        mAttractors[1].aPos.z ++;
    }
    else{
        mAttractors[1].aPos.z --;
    }
    
    
    
    // d02x
    if (attractorDist[3] >= 20.f && mAttractors[0].aPos.x > mAttractors[2].aPos.x){
        mAttractors[2].aPos.x ++;
    }
    else{
        mAttractors[2].aPos.x --;
    }
    // d02y
    if (attractorDist[4] >= 20.f && mAttractors[0].aPos.y > mAttractors[2].aPos.y){
        mAttractors[2].aPos.y ++;
    }
    else{
        mAttractors[2].aPos.y --;
    }
    // d02z
    if (attractorDist[5] >= 20.f && mAttractors[0].aPos.z > mAttractors[2].aPos.z){
        mAttractors[2].aPos.z ++;
    }
    else{
        mAttractors[2].aPos.z --;
    }
    
    
    
    // d12x
    if (attractorDist[6] >= 20.f && mAttractors[1].aPos.x > mAttractors[2].aPos.x){
        mAttractors[2].aPos.x ++;
    }
    else{
        mAttractors[2].aPos.x --;
    }
    // d12y
    if (attractorDist[7] >= 20.f && mAttractors[1].aPos.y > mAttractors[2].aPos.y){
        mAttractors[2].aPos.y ++;
    }
    else{
        mAttractors[2].aPos.y --;
    }
    // d12z
    if (attractorDist[8] >= 20.f && mAttractors[1].aPos.z > mAttractors[2].aPos.z){
        mAttractors[2].aPos.z ++;
    }
    else{
        mAttractors[2].aPos.z --;
    }
    
    for (int i = 0; i < mAttractors.size(); i++){
        mAttractors[i].update();
    }

    
    for (int j = 0; j < mAttractors.size(); j++){
        for (int i = 0; i < mMovers.size(); i++){
            Vec3f grav = mAttractors[j].attract(mMovers[i]);
            mMovers[i].applyForce(grav);
            Vec3f wind = Vec3f(Rand::randFloat(-4.f,4.f), Rand::randFloat(-4.f,4.f), Rand::randFloat(-4.f,4.f));
            mMovers[i].applyForce(wind);
            mMovers[i].update();
        }
    }

    console() << "camX: " << camX << std::endl;
    console() << "camY: " << camY << std::endl;
    console() << "camZ " << camZ << std::endl;
    console() << " " << std::endl;
    
}

void NOC_w2_4App::keyDown(KeyEvent event) {
    
    if (event.getCode() == KeyEvent::KEY_c) {
        camZ += 10;
    }
    if (event.getCode() == KeyEvent::KEY_d) {
        camZ -= 10;
    }
    if (event.getCode() == KeyEvent::KEY_RIGHT) {
        camX += 10;
    }
    if (event.getCode() == KeyEvent::KEY_LEFT) {
        camX -= 10;
    }
    if (event.getCode() == KeyEvent::KEY_UP) {
        camY += 10;
    }
    if (event.getCode() == KeyEvent::KEY_DOWN) {
        camY -= 10;
    }
    
}

void NOC_w2_4App::draw() {
    
    gl::clear( ColorA( 0, 0, 0, 0.7) );
    // gl::setMatricesWindowPersp( getWindowWidth(), getWindowHeight() );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPushMatrix();
    gl::translate(getWindowWidth()/2, getWindowHeight()/2);
    gl::rotate(Vec3f(camX, camY, camZ/2));
    
//    for(int i = 0; i < mAttractors.size(); i++){
//        mAttractors[i].aMat.apply();
//        mAttractors[i].render();
//    }
    
    for (int i = 0; i < mMovers.size(); i++){
        mMovers[i].gMat.apply();
        mMovers[i].render();
    }

    glPopMatrix();

}

CINDER_APP_NATIVE( NOC_w2_4App, RendererGl )
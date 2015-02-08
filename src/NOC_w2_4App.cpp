#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_w2_4App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_w2_4App::setup()
{
}

void NOC_w2_4App::mouseDown( MouseEvent event )
{
}

void NOC_w2_4App::update()
{
}

void NOC_w2_4App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( NOC_w2_4App, RendererGl )

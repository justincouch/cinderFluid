#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_INITIAL_PARTICLES 2000

class FluidApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void prepareSettings( Settings *settings );
    
    float mGravity;
    
    Vec2i mWindowSize;
    
    ParticleController  mParticleController;
};

void FluidApp::setup()
{
    mWindowSize     = Vec2i( getWindowWidth(), getWindowHeight() );
    
    gravity = 9.8f/60.0f;
    
    mParticleController.addParticles( NUM_INITIAL_PARTICLES );
}

void FluidApp::mouseDown( MouseEvent event )
{
}

void FluidApp::update()
{
    mParticleController.update( mWindowSize );
    mParticleController.applyGravity( mGravity );
}

void FluidApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    mParticleController.draw();
}

void FluidApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 900, 600 );
	settings->setFrameRate( 60.0f );
}

CINDER_APP_NATIVE( FluidApp, RendererGl )

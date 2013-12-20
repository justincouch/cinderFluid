#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Vector.h"
#include "ParticleController.h"
#include <array>

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_INITIAL_PARTICLES 200

class FluidApp : public AppNative {
  public:
	void prepareSettings( Settings *settings );
    
    void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
    
    int NUM_SPRINGS;
    
    Vec2i   mWindowSize;
    float   mNeighborhood;
    Vec2i   mCellIndices;
    
    float   mGravity;
    float   mViscositySigma;
    float   mViscosityBeta;
    float   mRestDensity;
    float   mStiffnessParameter;
    float   mStiffnessParameterNear;
    float   mSpringStiffness;
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // PARTICLE CONTROLLER
    ParticleController  mParticleController;
};

void FluidApp::setup()
{
    mWindowSize     = Vec2i( getWindowWidth(), getWindowHeight() );
    mGravity = 0.1f;
    mNeighborhood = 40.0f;
    mViscositySigma = 0.001f;
    mViscosityBeta = 0.01f;
    mRestDensity = 10.0f;
    mStiffnessParameter = 0.004f;
    mStiffnessParameterNear = 0.01f;
    mSpringStiffness = 0.3f;
    
    NUM_SPRINGS = NUM_INITIAL_PARTICLES * ( NUM_INITIAL_PARTICLES - 1 ) / 2;
    
    mCellIndices = Vec2i( int( ceil( mWindowSize.x / mNeighborhood ) ), int( ceil( mWindowSize.y / mNeighborhood ) ) );
    
    // SETUP PARAMS
	mParams = params::InterfaceGl( "Fluid Simulation", Vec2i( 220, 400 ) );
    mParams.addParam( "Neighborhood", &mNeighborhood, "min=5.0 max=100.0 step=0.1" );
    mParams.addSeparator();
    mParams.addParam( "Gravity", &mGravity, "min=0.0 max=2.0 step=0.0001" );
    mParams.addSeparator();
    mParams.addParam( "Viscosity Sigma", &mViscositySigma, "min=0.0 max=0.3 step=0.0001" );
    mParams.addParam( "Viscosity Beta", &mViscosityBeta, "min=0.0 max=0.3 step=0.0001" );
    mParams.addSeparator();
    mParams.addParam( "Rest Density", &mRestDensity, "min=0.0 max=100.0 step=0.1" );
    mParams.addParam( "Stiffness", &mStiffnessParameter, "min=0.0 max=0.5 step=0.001" );
    mParams.addParam( "Near Stiffness", &mStiffnessParameterNear, "min=0.0 max=0.5 step=0.001" );
    mParams.addSeparator();
    mParams.addParam( "Spring Stiffness", &mSpringStiffness, "min=0.0 max=5.0 step=0.001" );
    
    mParticleController.addParticles( NUM_INITIAL_PARTICLES );
    
    //mParticleController.addSprings();
}

void FluidApp::mouseDown( MouseEvent event )
{
}

void FluidApp::update()
{
    mParticleController.update( mWindowSize, mGravity, mNeighborhood, mViscositySigma, mViscosityBeta, mRestDensity, mStiffnessParameter, mStiffnessParameterNear, mSpringStiffness );
}

void FluidApp::draw()
{
	// clear out the window with black
	gl::clear( ColorA( 0.0f, 0.0f, 0.0f, 0.25f ) );
    
    mParticleController.draw( mNeighborhood, mRestDensity );
    
    // DRAW PARAMS WINDOW
    mParams.draw();
    
    gl::drawString( "FPS: " + to_string( getAverageFps() ), Vec2f( 10.0f, 10.0f ) );
}

void FluidApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 900, 600 );
	settings->setFrameRate( 60.0f );
}

CINDER_APP_NATIVE( FluidApp, RendererGl )

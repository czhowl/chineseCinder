#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class chineseApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void chineseApp::setup()
{
}

void chineseApp::mouseDown( MouseEvent event )
{
}

void chineseApp::update()
{
}

void chineseApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( chineseApp, RendererGl )

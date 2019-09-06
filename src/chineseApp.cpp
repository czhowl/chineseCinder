#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include "cinder/Text.h"
#include "cinder/Unicode.h"
#include "jsoncpp/json.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class chineseApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void keyDown( KeyEvent event ) override;
	void mouseDrag( MouseEvent event ) override;
	void update() override;
	void draw() override;
	static void prepare(Settings *settings);

	void render();

	string				mText;
	gl::TextureRef		mTextTexture;
	vec2				mSize;
	Font				mFont;
	string				mChinese;
};

void chineseApp::setup()
{
	Json::Value root;
	Json::Reader reader;
	string path = getAssetPath( "chinese.json" ).u8string();
	ifstream json(path, ifstream::binary);
	bool parsingSuccessful = reader.parse(json, root);
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		console()  << "Failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
		//return;
	}
	mChinese = root.get("username", "null" ).asString();
	console() << mChinese << endl;
	mText = "username: ";
	mText += mChinese;
	mFont = Font( loadAsset( "MFPuYue_Noncommercial-Regular.ttf" ), 24 );
	mSize = vec2( 250, 40 );
	render();
}

void chineseApp::keyDown( KeyEvent event )
{
	if( event.getCharUtf32() ) {
		std::u32string strUtf32( 1, event.getCharUtf32() );
		std::string str = ci::toUtf8( strUtf32 );

		mText += str;
		render();
	}
}

void chineseApp::mouseDrag( MouseEvent event )
{
	mSize = event.getPos();
	render();
}

void chineseApp::render()
{
	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( mFont ).size( ivec2( mSize.x, TextBox::GROW ) ).text( mText );
	tbox.setColor( Color( 1.0f, 0.65f, 0.35f ) );
	tbox.setBackgroundColor( ColorA( 0.5, 0, 0, 1 ) );
	ivec2 sz = tbox.measure();
	CI_LOG_I( "text size: " << sz );
	mTextTexture = gl::Texture2d::create( tbox.render() );
}

void chineseApp::mouseDown( MouseEvent event )
{
}

void chineseApp::update()
{
}

void chineseApp::draw()
{
	gl::setMatricesWindow( getWindowSize() );
	gl::enableAlphaBlending();
	gl::clear( Color( 0, 0, 0 ) );

	if( mTextTexture )
		gl::draw( mTextTexture );
}

void chineseApp::prepare(Settings *settings)
{
	settings->setTitle("Display Chinese");
	settings->setWindowSize(1024, 1024);
}

CINDER_APP( chineseApp, RendererGl(RendererGl::Options().msaa(16)), &chineseApp::prepare)

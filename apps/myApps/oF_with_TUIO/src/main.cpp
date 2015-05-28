#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "TouchManager.h"
#include "DrawManager.h"

//========================================================================
int main(){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

	DrawManager::GetInstance()->Init();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new TouchManager());

  	DrawManager::GetInstance()->Close();
}

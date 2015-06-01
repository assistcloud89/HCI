#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "TouchManager.h"
#include "DrawManager.h"

//========================================================================
int main(){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 512,384, OF_WINDOW);			// <-------- setup the GL context

	DrawManager::GetInstance()->Init();
	DrawManager::GetInstance()->SendData();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new TouchManager());

  	//DrawManager::GetInstance()->Close();
}

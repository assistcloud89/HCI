#ifndef _TOUCH_MANAGER_
#define _TOUCH_MANAGER_

#include "ofMain.h"
#include "ofxTuioClient.h"

class TouchManager : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);

private:
	ofxTuioClient myTuio;
};

#endif
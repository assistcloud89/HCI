#include "TouchManager.h"
#include "DrawManager.h"

//--------------------------------------------------------------
void TouchManager::setup()
{
	ofBackground(200, 200, 200);
	ofSetVerticalSync(true);

	//Connect to Port
	myTuio.connect(3333);

	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown, this, &TouchManager::touchDown);
	ofAddListener(ofEvents().touchUp, this, &TouchManager::touchUp);
	ofAddListener(ofEvents().touchMoved, this, &TouchManager::touchMoved);
}

//--------------------------------------------------------------
void TouchManager::update()
{

}

//--------------------------------------------------------------
void TouchManager::draw()
{

	//render TUIO Cursors and Objects
	//myTuio.drawCursors();
	//myTuio.drawObjects();


	std::list<TuioCursor*> cursorList = myTuio.client->getTuioCursors();
	std::list<TuioCursor*>::iterator tit;
	myTuio.client->lockCursorList();
	for(tit = cursorList.begin(); tit != cursorList.end(); tit++)
	{
		TuioCursor * cur = (*tit);
		//if(tcur!=0){
		//TuioCursor cur = *tcur;
		glColor3f(1.0, 0.0, 0.0);
		ofEllipse(cur->getX()*ofGetWidth(), cur->getY()*ofGetHeight(), 20.0, 20.0);
		glColor3f(0.0, 0.0, 0.0);
		string str = "SessionId: " + ofToString(( int )(cur->getSessionID()));
		ofDrawBitmapString(str, cur->getX()*ofGetWidth() - 10.0, cur->getY()*ofGetHeight() + 25.0);
		str = "CursorId: " + ofToString(( int )(cur->getCursorID()));
		ofDrawBitmapString(str, cur->getX()*ofGetWidth() - 10.0, cur->getY()*ofGetHeight() + 40.0);
		//}
	}
	myTuio.client->unlockCursorList();


}

//--------------------------------------------------------------
void TouchManager::keyPressed(int key)
{

}

//--------------------------------------------------------------
void TouchManager::keyReleased(int key)
{

}

//--------------------------------------------------------------
void TouchManager::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void TouchManager::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void TouchManager::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void TouchManager::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void TouchManager::windowResized(int w, int h)
{

}


void TouchManager::touchDown(ofTouchEventArgs & touch)
{
	cout << " cursor added: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< endl;


	cout << "Cursor ID : " << myTuio.client->getTuioCursor(touch.id)->getCursorID() << endl;
}

void TouchManager::touchUp(ofTouchEventArgs & touch)
{
	cout << " cursor removed: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< endl;
}

void TouchManager::touchMoved(ofTouchEventArgs & touch)
{
	cout << " cursor updated: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< endl;

}


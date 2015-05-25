#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(200, 200, 200);
	ofSetVerticalSync(true);
	
	//Connect to Port
	myTuio.connect(3333);
	
	
	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown,this,&testApp::touchDown);
	ofAddListener(ofEvents().touchUp,this,&testApp::touchUp);
	ofAddListener(ofEvents().touchMoved,this,&testApp::touchMoved);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	//render TUIO Cursors and Objects
	//myTuio.drawCursors();
	//myTuio.drawObjects();
    
    
    std::list<TuioCursor*> cursorList = myTuio.client->getTuioCursors();
    std::list<TuioCursor*>::iterator tit;
    myTuio.client->lockCursorList();
    for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
        TuioCursor * cur = (*tit);
        //if(tcur!=0){
        //TuioCursor cur = *tcur;
        glColor3f(1.0,0.0,0.0);
        ofEllipse(cur->getX()*ofGetWidth(), cur->getY()*ofGetHeight(), 20.0, 20.0);
        glColor3f(0.0,0.0,0.0);
        string str = "SessionId: "+ofToString((int)(cur->getSessionID()));
        ofDrawBitmapString(str, cur->getX()*ofGetWidth()-10.0, cur->getY()*ofGetHeight()+25.0);
        str = "CursorId: "+ofToString((int)(cur->getCursorID()));
        ofDrawBitmapString(str, cur->getX()*ofGetWidth()-10.0, cur->getY()*ofGetHeight()+40.0);
        //}
    }
    myTuio.client->unlockCursorList();
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}


void testApp::touchDown(ofTouchEventArgs & touch){
	cout << " cursor added: " + ofToString(touch.id)+
	" X: "+ofToString(touch.x)+
	" Y: "+ofToString(touch.y)
	<< endl;
    
    
    cout << "Cursor ID : " << myTuio.client->getTuioCursor(touch.id)->getCursorID() << endl;

}

void testApp::touchUp(ofTouchEventArgs & touch){
	cout << " cursor removed: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;
}

void testApp::touchMoved(ofTouchEventArgs & touch){
	cout << " cursor updated: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;
    
}


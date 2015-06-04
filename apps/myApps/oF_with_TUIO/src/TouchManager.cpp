#include "TouchManager.h"
#include "DrawManager.h"

//--------------------------------------------------------------
void TouchManager::setup()
{
	ofBackground(200, 200, 200);
	ofSetVerticalSync(true);

	//Connect to Port
	mMyTuio.connect(3333);

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
	mMyTuio.drawCursors();
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


void TouchManager::touchDown(ofTouchEventArgs& touch)
{
	std::cout << " cursor added: " + 
		ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< std::endl;

	TouchedSectionHandle(TOUCH_DOWN, touch);
}

void TouchManager::touchMoved(ofTouchEventArgs& touch)
{
	std::cout << " cursor updated: " +
		ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< std::endl;

	TouchedSectionHandle(TOUCH_MOVED, touch);
}

void TouchManager::touchUp(ofTouchEventArgs& touch)
{
	std::cout << " cursor removed: " +
		ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y)
		<< std::endl;

	TouchedSectionHandle(TOUCH_UP, touch);
}

void TouchManager::TouchedSectionHandle(TouchEvent event,
										ofTouchEventArgs& touch)
{
	if(IsInLEDSection(touch.x, touch.y))
	{
		LEDManager::GetInstance()->TouchHandle(event,
											   touch.id,
											   touch.x,
											   touch.y);
		return;
	}

	if(IsInEditorSection(touch.x, touch.y))
	{
		EditorManager::GetInstance()->TouchHandle(event,
												  touch.id,
												  touch.x,
												  touch.y);
		return;
	}

	if(IsInColorChipSection(touch.x, touch.y))
	{
		ColorChipManager::GetInstance()->TouchHandle(event,
													 touch.id,
													 touch.x,
													 touch.y);
		return;
	}
}

bool TouchManager::IsInLEDSection(float x, float y)
{
	if((PIXEL_X_0 <= x && x <= PIXEL_X_END) &&
	   (PIXEL_Y_0 <= y && y <= PIXEL_Y_END))
		return true;
	else
		return false;
}

bool TouchManager::IsInEditorSection(float x, float y)
{
	if((DRAW_START_X <= x && x <= CLEAR_END_X) &&
	   (DRAW_START_Y <= y && y <= DRAW_END_Y))
		return true;
	else
		return false;
}

bool TouchManager::IsInColorChipSection(float x, float y)
{
	if((CHIP_X_0_START <= x && x <= CHIP_X_8_END) &&
	   (CHIP_Y_0_START <= y && y <= CHIP_Y_12_END))
		return true;
	else
		return false;
}


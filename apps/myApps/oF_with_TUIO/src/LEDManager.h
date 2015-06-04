#ifndef _LED_MANAGER_
#define _LED_MANAGER_

#include "Define.h"
#include "Coordinate.h"
#include "DrawManager.h"
#include "TouchHistory.h"
#include "ColorChipManager.h"

struct PixelInfo
{
	int id;
	ColorInfo color;
	bool visible;
};

class LEDManager
{
private:
	LEDManager();
	~LEDManager();

public:
	static LEDManager* GetInstance();

	void TouchHandle(TouchEvent event,
					 int id,
					 float x,
					 float y);
	void DrawMode(TouchEvent event,
				  int id,
				  float x,
				  float y);
	void MoveMode(TouchEvent event,
				  int id,
				  float x,
				  float y);
	void DeleteMode(TouchEvent event,
					int id,
					float x,
					float y);

	Pixel FindTouchLocation(float x, float y);
	int FindTouchLocationX(float x);
	int FindTouchLocationY(float y);

	EditorMode GetEditor() { return mEditor; }
	void SetEditor(EditorMode editor) { mEditor = editor; }

	ColorInfo GetColor() { return mColor; }
	void SetColor(ColorInfo color) { mColor = color; }

	void HandleEditor(EditorMode editor);

	void BackEdit();
	void DrawBack(int id);
	void MoveBack(int id);
	void DeleteBack(int id);

	void ForwardEdit();
	void DrawForward(int id);
	void MoveForward(int id);
	void DeleteForward(int id);

	void ClearEdit();

	int GetLEDLock() { return LEDLock; }

private:
	std::vector<PixelInfo*>* mPixelTable[29][32]; // mPixelTable[y][x]

	EditorMode mEditor;
	ColorInfo mColor;

	int LEDLock; // Need to change to semaphore!!!!!
};

#endif
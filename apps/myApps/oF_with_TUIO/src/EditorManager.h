#ifndef _EDITOR_MANAGER_
#define _EDITOR_MANAGER_

#include <iostream>
#include "Define.h"
#include "DrawManager.h"
#include "LEDManager.h"
#include "TouchHistory.h"
#include "ColorChipManager.h"

class EditorManager
{
private:
	EditorManager();
	~EditorManager();

public:
	static EditorManager* GetInstance();

	void TouchHandle(TouchEvent event,
					 int id,
					 float x,
					 float y);

	EditorMode FindTouchLocation(float x, float y);
};

#endif
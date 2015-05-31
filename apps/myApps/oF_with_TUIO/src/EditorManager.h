#ifndef _EDITOR_MANAGER_
#define _EDITOR_MANAGER_

#include "Define.h"
#include <iostream>

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
};

#endif
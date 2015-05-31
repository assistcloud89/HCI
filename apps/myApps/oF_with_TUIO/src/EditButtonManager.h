#ifndef _EDIT_BUTTON_MANAGER_
#define _EDIT_BUTTON_MANAGER_

#include "Define.h"
#include <iostream>

class EditButtonManager
{
private:
	EditButtonManager();
	~EditButtonManager();

public:
	static EditButtonManager* GetInstance();

	void TouchHandle(TouchEvent event,
					 int id,
					 float x,
					 float y);
};

#endif
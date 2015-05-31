#ifndef _LED_MANAGER_
#define _LED_MANAGER_

#include "Define.h"
#include <iostream>

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
};

#endif
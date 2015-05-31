#ifndef _COLOR_CHIP_MANAGER_
#define _COLOR_CHIP_MANAGER_

#include "Define.h"
#include <iostream>

class ColorChipManager
{
private:
	ColorChipManager();
	~ColorChipManager();

public:
	static ColorChipManager* GetInstance();

	void TouchHandle(TouchEvent event,
					 int id,
					 float x,
					 float y);
};

#endif
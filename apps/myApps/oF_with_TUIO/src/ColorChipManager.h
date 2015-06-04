#ifndef _COLOR_CHIP_MANAGER_
#define _COLOR_CHIP_MANAGER_

#include <iostream>
#include "Define.h"
#include "Coordinate.h"
#include "LEDManager.h"
#include "DrawManager.h"

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

	ColorChip FindTouchLocation(float x, float y);
	int FindTouchLocationX(float x);
	int FindTouchLocationY(float y);

	ColorInfo GetColorInfoOfColorChip(ColorChip colorChip);
	ColorChip GetColorChipOfColorInfo(ColorInfo colorInfo);

	void ClearEdit();
};

#endif
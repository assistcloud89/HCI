#include "ColorChipManager.h"

static ColorChipManager* pColorChipManager = nullptr;

ColorChipManager::ColorChipManager()
{
}


ColorChipManager::~ColorChipManager()
{
}

ColorChipManager* ColorChipManager::GetInstance()
{
	if(pColorChipManager == nullptr)
		pColorChipManager = new ColorChipManager;

	return pColorChipManager;
}

void ColorChipManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "ColorChip" << std::endl;

	if(event == TOUCH_UP)
		return;

	// Find touched color chip's location.
	ColorChip colorChip = FindTouchLocation(x, y);
	std::cout << "ColorChip(" << colorChip.x << ", " << colorChip.y << ")" << std::endl;
	if(colorChip.x == -1 || colorChip.y == -1)
		return;

	// Update current color info at LEDManager.
	ColorInfo colorInfo = GetColorInfoOfColorChip(colorChip);
	if(colorInfo == LEDManager::GetInstance()->GetColor())
		return;
	else
		LEDManager::GetInstance()->SetColor(colorInfo);

	// Draw touched color chip's color on color zone.
	char buffer[4];
	buffer[0] = COLOR_DATA + '0';
	buffer[1] = colorChip.x + '0';
	buffer[2] = colorChip.y / 10 + '0';
	buffer[3] = colorChip.y % 10 + '0';

	DrawManager::GetInstance()->WriteData(buffer, 4);
}

ColorChip ColorChipManager::FindTouchLocation(float x, float y)
{
	ColorChip colorChip;
	colorChip.x = FindTouchLocationX(x);
	colorChip.y = FindTouchLocationY(y);

	return colorChip;
}

int ColorChipManager::FindTouchLocationX(float x)
{
	if(CHIP_X_0_START <= x && x < CHIP_X_4_END)
	{
		if(CHIP_X_0_START <= x && x < CHIP_X_0_END)
			return 0;
		else if(CHIP_X_1_START <= x && x < CHIP_X_1_END)
			return 1;
		else if(CHIP_X_2_START <= x && x < CHIP_X_2_END)
			return 2;
		else if(CHIP_X_3_START <= x && x < CHIP_X_3_END)
			return 3;
		else if(CHIP_X_4_START <= x && x < CHIP_X_4_END)
			return 4;
		else
			return -1;
	}
	else
	{
		if(CHIP_X_5_START <= x && x < CHIP_X_5_END)
			return 5;
		else if(CHIP_X_6_START <= x && x < CHIP_X_6_END)
			return 6;
		else if(CHIP_X_7_START <= x && x < CHIP_X_7_END)
			return 7;
		else if(CHIP_X_8_START <= x && x < CHIP_X_8_END)
			return 8;
		else
			return -1;
	}
}

int ColorChipManager::FindTouchLocationY(float y)
{
	if(CHIP_Y_0_START <= y && y < CHIP_Y_3_END)
	{
		if(CHIP_Y_0_START <= y && y < CHIP_Y_0_END)
			return 0;
		else if(CHIP_Y_1_START <= y && y < CHIP_Y_1_END)
			return 1;
		else if(CHIP_Y_2_START <= y && y < CHIP_Y_2_END)
			return 2;
		else if(CHIP_Y_3_START <= y && y < CHIP_Y_3_END)
			return 3;
		else
			return -1;
	}
	else if(CHIP_Y_4_START <= y && y < CHIP_Y_7_END)
	{
		if(CHIP_Y_4_START <= y && y < CHIP_Y_4_END)
			return 4;
		else if(CHIP_Y_5_START <= y && y < CHIP_Y_5_END)
			return 5;
		else if(CHIP_Y_6_START <= y && y < CHIP_Y_6_END)
			return 6;
		else if(CHIP_Y_7_START <= y && y < CHIP_Y_7_END)
			return 7;
		else
			return -1;
	}
	else
	{
		if(CHIP_Y_8_START <= y && y < CHIP_Y_8_END)
			return 8;
		else if(CHIP_Y_9_START <= y && y < CHIP_Y_9_END)
			return 9;
		else if(CHIP_Y_10_START <= y && y < CHIP_Y_10_END)
			return 10;
		else if(CHIP_Y_11_START <= y && y < CHIP_Y_11_END)
			return 11;
		else if(CHIP_Y_12_START <= y && y < CHIP_Y_12_END)
			return 12;
		else
			return -1;
	}
}

ColorInfo ColorChipManager::GetColorInfoOfColorChip(ColorChip colorChip)
{
	switch(colorChip.y)
	{
	case 0:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_0_0;
		case 1:
			return COLOR_0_1;
		case 2:
			return COLOR_0_2;
		case 3:
			return COLOR_0_3;
		case 4:
			return COLOR_0_4;
		case 5:
			return COLOR_0_5;
		case 6:
			return COLOR_0_6;
		case 7:
			return COLOR_0_7;
		case 8:
			return COLOR_0_8;
		}
		break;
	case 1:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_1_0;
		case 1:			 
			return COLOR_1_1;
		case 2:			 
			return COLOR_1_2;
		case 3:			 
			return COLOR_1_3;
		case 4:			 
			return COLOR_1_4;
		case 5:			 
			return COLOR_1_5;
		case 6:			 
			return COLOR_1_6;
		case 7:			 
			return COLOR_1_7;
		case 8:			 
			return COLOR_1_8;
		}
		break;
	case 2:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_2_0;
		case 1:			 
			return COLOR_2_1;
		case 2:			 
			return COLOR_2_2;
		case 3:			 
			return COLOR_2_3;
		case 4:			 
			return COLOR_2_4;
		case 5:			 
			return COLOR_2_5;
		case 6:			 
			return COLOR_2_6;
		case 7:			 
			return COLOR_2_7;
		case 8:			 
			return COLOR_2_8;
		}
		break;
	case 3:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_3_0;
		case 1:			 
			return COLOR_3_1;
		case 2:			 
			return COLOR_3_2;
		case 3:			 
			return COLOR_3_3;
		case 4:			 
			return COLOR_3_4;
		case 5:			 
			return COLOR_3_5;
		case 6:			 
			return COLOR_3_6;
		case 7:			 
			return COLOR_3_7;
		case 8:			 
			return COLOR_3_8;
		}
		break;
	case 4:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_4_0;
		case 1:			 
			return COLOR_4_1;
		case 2:			 
			return COLOR_4_2;
		case 3:			 
			return COLOR_4_3;
		case 4:			 
			return COLOR_4_4;
		case 5:			 
			return COLOR_4_5;
		case 6:			 
			return COLOR_4_6;
		case 7:			 
			return COLOR_4_7;
		case 8:			 
			return COLOR_4_8;
		}
		break;
	case 5:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_5_0;
		case 1:			 
			return COLOR_5_1;
		case 2:			 
			return COLOR_5_2;
		case 3:			 
			return COLOR_5_3;
		case 4:			 
			return COLOR_5_4;
		case 5:			 
			return COLOR_5_5;
		case 6:			 
			return COLOR_5_6;
		case 7:			 
			return COLOR_5_7;
		case 8:			 
			return COLOR_5_8;
		}
		break;
	case 6:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_6_0;
		case 1:			 
			return COLOR_6_1;
		case 2:			 
			return COLOR_6_2;
		case 3:			 
			return COLOR_6_3;
		case 4:			 
			return COLOR_6_4;
		case 5:			 
			return COLOR_6_5;
		case 6:			 
			return COLOR_6_6;
		case 7:			 
			return COLOR_6_7;
		case 8:			 
			return COLOR_6_8;
		}
		break;
	case 7:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_7_0;
		case 1:			 
			return COLOR_7_1;
		case 2:			 
			return COLOR_7_2;
		case 3:			 
			return COLOR_7_3;
		case 4:			 
			return COLOR_7_4;
		case 5:			 
			return COLOR_7_5;
		case 6:			 
			return COLOR_7_6;
		case 7:			 
			return COLOR_7_7;
		case 8:			 
			return COLOR_7_8;
		}
		break;
	case 8:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_8_0;
		case 1:			 
			return COLOR_8_1;
		case 2:			 
			return COLOR_8_2;
		case 3:			 
			return COLOR_8_3;
		case 4:			 
			return COLOR_8_4;
		case 5:			 
			return COLOR_8_5;
		case 6:			 
			return COLOR_8_6;
		case 7:			 
			return COLOR_8_7;
		case 8:			 
			return COLOR_8_8;
		}
		break;
	case 9:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_9_0;
		case 1:			 
			return COLOR_9_1;
		case 2:			 
			return COLOR_9_2;
		case 3:			 
			return COLOR_9_3;
		case 4:			 
			return COLOR_9_4;
		case 5:			 
			return COLOR_9_5;
		case 6:			 
			return COLOR_9_6;
		case 7:			 
			return COLOR_9_7;
		case 8:			 
			return COLOR_9_8;
		}
		break;
	case 10:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_10_0;
		case 1:			 
			return COLOR_10_1;
		case 2:			 
			return COLOR_10_2;
		case 3:			 
			return COLOR_10_3;
		case 4:			 
			return COLOR_10_4;
		case 5:			 
			return COLOR_10_5;
		case 6:			 
			return COLOR_10_6;
		case 7:			 
			return COLOR_10_7;
		case 8:			 
			return COLOR_10_8;
		}
		break;
	case 11:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_11_0;
		case 1:			 
			return COLOR_11_1;
		case 2:			 
			return COLOR_11_2;
		case 3:			 
			return COLOR_11_3;
		case 4:			 
			return COLOR_11_4;
		case 5:			 
			return COLOR_11_5;
		case 6:			 
			return COLOR_11_6;
		case 7:			 
			return COLOR_11_7;
		case 8:			 
			return COLOR_11_8;
		}
		break;
	case 12:
		switch(colorChip.x)
		{
		case 0:
			return COLOR_12_0;
		case 1:			 
			return COLOR_12_1;
		case 2:			 
			return COLOR_12_2;
		case 3:			 
			return COLOR_12_3;
		case 4:			 
			return COLOR_12_4;
		case 5:			 
			return COLOR_12_5;
		case 6:			 
			return COLOR_12_6;
		case 7:			 
			return COLOR_12_7;
		case 8:			 
			return COLOR_12_8;
		}
		break;
	}
}

ColorChip ColorChipManager::GetColorChipOfColorInfo(ColorInfo colorInfo)
{
	ColorChip colorChip;

	colorChip.x = colorInfo % 10;
	colorChip.y = colorInfo / 10;

	return colorChip;
}

void ColorChipManager::ClearEdit()
{
	ColorInfo colorInfo = COLOR_0_4;
	LEDManager::GetInstance()->SetColor(colorInfo);
	ColorChip colorChip = GetColorChipOfColorInfo(colorInfo);

	// Draw touched color chip's color on color zone.
	char buffer[4];
	buffer[0] = COLOR_DATA + '0';
	buffer[1] = colorChip.x + '0';
	buffer[2] = colorChip.y / 10 + '0';
	buffer[3] = colorChip.y % 10 + '0';

	DrawManager::GetInstance()->WriteData(buffer, 4);
}

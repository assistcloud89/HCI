#ifndef _DEFINE_
#define _DEFINE_

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

struct Pixel
{
	int x;
	int y;
};

struct ColorChip
{
	int x;
	int y;
};

enum TouchEvent
{
	TOUCH_DOWN,
	TOUCH_MOVED,
	TOUCH_UP,
};

enum EditorMode
{
	EDIT_DRAW = 0,
	EDIT_MOVE = 1,
	EDIT_DELETE = 2,
	EDIT_BACK = 3,
	EDIT_FORWARD = 4,
	EDIT_CLEAR = 5,

	EDIT_NOT_TOUCHED,
};

enum DataType
{
	COLOR_DATA = 9,
	EDIT_DATA = 8,
};

enum ColorInfo
{
	COLOR_0_0,
	COLOR_0_1,
	COLOR_0_2,
	COLOR_0_3,
	COLOR_0_4,
	COLOR_0_5,
	COLOR_0_6,
	COLOR_0_7,
	COLOR_0_8,

	COLOR_1_0,
	COLOR_1_1,
	COLOR_1_2,
	COLOR_1_3,
	COLOR_1_4,
	COLOR_1_5,
	COLOR_1_6,
	COLOR_1_7,
	COLOR_1_8,
	
	COLOR_2_0,
	COLOR_2_1,
	COLOR_2_2,
	COLOR_2_3,
	COLOR_2_4,
	COLOR_2_5,
	COLOR_2_6,
	COLOR_2_7,
	COLOR_2_8,
	
	COLOR_3_0,
	COLOR_3_1,
	COLOR_3_2,
	COLOR_3_3,
	COLOR_3_4,
	COLOR_3_5,
	COLOR_3_6,
	COLOR_3_7,
	COLOR_3_8,
	
	COLOR_4_0,
	COLOR_4_1,
	COLOR_4_2,
	COLOR_4_3,
	COLOR_4_4,
	COLOR_4_5,
	COLOR_4_6,
	COLOR_4_7,
	COLOR_4_8,
	
	COLOR_5_0,
	COLOR_5_1,
	COLOR_5_2,
	COLOR_5_3,
	COLOR_5_4,
	COLOR_5_5,
	COLOR_5_6,
	COLOR_5_7,
	COLOR_5_8,
	
	COLOR_6_0,
	COLOR_6_1,
	COLOR_6_2,
	COLOR_6_3,
	COLOR_6_4,
	COLOR_6_5,
	COLOR_6_6,
	COLOR_6_7,
	COLOR_6_8,
	
	COLOR_7_0,
	COLOR_7_1,
	COLOR_7_2,
	COLOR_7_3,
	COLOR_7_4,
	COLOR_7_5,
	COLOR_7_6,
	COLOR_7_7,
	COLOR_7_8,
	
	COLOR_8_0,
	COLOR_8_1,
	COLOR_8_2,
	COLOR_8_3,
	COLOR_8_4,
	COLOR_8_5,
	COLOR_8_6,
	COLOR_8_7,
	COLOR_8_8,
	
	COLOR_9_0,
	COLOR_9_1,
	COLOR_9_2,
	COLOR_9_3,
	COLOR_9_4,
	COLOR_9_5,
	COLOR_9_6,
	COLOR_9_7,
	COLOR_9_8,

	COLOR_10_0,
	COLOR_10_1,
	COLOR_10_2,
	COLOR_10_3,
	COLOR_10_4,
	COLOR_10_5,
	COLOR_10_6,
	COLOR_10_7,
	COLOR_10_8,
	
	COLOR_11_0,
	COLOR_11_1,
	COLOR_11_2,
	COLOR_11_3,
	COLOR_11_4,
	COLOR_11_5,
	COLOR_11_6,
	COLOR_11_7,
	COLOR_11_8,
	
	COLOR_12_0,
	COLOR_12_1,
	COLOR_12_2,
	COLOR_12_3,
	COLOR_12_4,
	COLOR_12_5,
	COLOR_12_6,
	COLOR_12_7,
	COLOR_12_8,
};

#endif
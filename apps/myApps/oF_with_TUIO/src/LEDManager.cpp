#include "LEDManager.h"

static LEDManager* pLEDManager = nullptr;

LEDManager::LEDManager()
{
	for(int i = 0; i < 29; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			mPixelTable[i][j] = new std::vector<PixelInfo*>;
			mPixelTable[i][j]->reserve(15);
		}
	}

	mEditor = EDIT_DRAW;
	mColor = COLOR_0_4;
}


LEDManager::~LEDManager()
{
	for(int i = 0; i < 29; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			std::vector<PixelInfo*>::iterator iter;
			for(iter = mPixelTable[i][j]->begin();
				iter != mPixelTable[i][j]->end();
				++iter)
			{
				delete (*iter);
			}
			mPixelTable[i][j]->clear();
		}
	}
}

LEDManager* LEDManager::GetInstance()
{
	if(pLEDManager == nullptr)
		pLEDManager = new LEDManager;
	
	return pLEDManager;
}

void LEDManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "LED" << std::endl;

	switch(mEditor)
	{
	case EDIT_DRAW:
		DrawMode(event, id, x, y);
		break;
	case EDIT_MOVE:
		MoveMode(event, id, x, y);
		break;
	case EDIT_DELETE:
		DeleteMode(event, id, x, y);
		break;
	}
}

void LEDManager::DrawMode(TouchEvent event, int id, float x, float y)
{
	if(event == TOUCH_UP)
	{
		// Register history.
		TouchHistory::GetInstance()->PushEditHistory(EDIT_DRAW, id);
		return;
	}

	// Find touched pixel's location.
	Pixel pixel = FindTouchLocation(x, y);
	
	std::vector<PixelInfo*>* pixelVector = mPixelTable[pixel.y][pixel.x];
	if(!pixelVector->empty() && id == pixelVector->back()->id)
		return;
	
	// Add touched pixel's info into pixel table.
	PixelInfo* pixelInfo = new PixelInfo;
	pixelInfo->id = id;
	pixelInfo->color = mColor;
	pixelInfo->visible = true;

	pixelVector->push_back(pixelInfo);

	// Insert to pixel list of TouchHistory.
	TouchHistory::GetInstance()->InsertPixelList(id, pixel);

	// Draw touched pixel on LED.
	char buffer[4];
	buffer[0] = pixel.x / 10 + '0';
	buffer[1] = pixel.x % 10 + '0';
	buffer[2] = pixel.y / 10 + '0';
	buffer[3] = pixel.y % 10 + '0';

	DrawManager::GetInstance()->WriteData(buffer, 4);
}

void LEDManager::MoveMode(TouchEvent event, int id, float x, float y)
{
	if(event == TOUCH_UP)
	{
		// Register history.
		if(TouchHistory::GetInstance()->HasMoveHistory(id))
			TouchHistory::GetInstance()->PushEditHistory(EDIT_MOVE, id);
		
		return;
	}

	// Find touched pixel's location.
	Pixel pixel = FindTouchLocation(x, y);

	std::vector<PixelInfo*>* pixelVector = mPixelTable[pixel.y][pixel.x];

	if(event == TOUCH_DOWN)
	{
		if(pixelVector->empty())
			return;

		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->visible)
				break;
		}
		if(r_itor == pixelVector->rend())
			return;

		TouchHistory::GetInstance()->InsertMoveHistory(id, pixel);
		return;
	}

	if(!TouchHistory::GetInstance()->HasMoveHistory(id))
		return;

	// Figure out moved direction. (There are 8 ways of direction.)
	Variation variation = TouchHistory::GetInstance()->GetMoveHistory(id);
	if((variation.terminal.x == pixel.x) &&
	   (variation.terminal.y == pixel.y))
	   return;

	MoveDirection direction;
	int dx, dy;
	if((variation.terminal.x == pixel.x) &&
	   (variation.terminal.y - 1 == pixel.y))
	{
		direction = MOVE_UP;
		dx = 0; dy = -1;
	}
	else if((variation.terminal.x + 1 == pixel.x) &&
			(variation.terminal.y - 1 == pixel.y))
	{
		direction = MOVE_UP_RIGHT;
		dx = 1; dy = -1;
	}
	else if((variation.terminal.x + 1 == pixel.x) &&
			(variation.terminal.y == pixel.y))
	{
		direction = MOVE_RIGHT;
		dx = 1; dy = 0;
	}
	else if((variation.terminal.x + 1 == pixel.x) &&
			(variation.terminal.y + 1 == pixel.y))
	{
		direction = MOVE_DOWN_RIGHT;
		dx = 1; dy = 1;
	}
	else if((variation.terminal.x == pixel.x) &&
			(variation.terminal.y + 1 == pixel.y))
	{
		direction = MOVE_DOWN;
		dx = 0; dy = 1;
	}
	else if((variation.terminal.x - 1 == pixel.x) &&
			(variation.terminal.y + 1 == pixel.y))
	{
		direction = MOVE_DOWN_LEFT;
		dx = -1; dy = 1;
	}
	else if((variation.terminal.x - 1 == pixel.x) &&
			(variation.terminal.y == pixel.y))
	{
		direction = MOVE_LEFT;
		dx = -1; dy = 0;
	}
	else if((variation.terminal.x - 1 == pixel.x) &&
			(variation.terminal.y - 1 == pixel.y))
	{
		direction = MOVE_UP_LEFT;
		dx = -1; dy = -1;
	}
	else
		return;

	// Bring pixels of touch id to the top of the pixel table.
	pixelVector = mPixelTable[variation.terminal.y][variation.terminal.x];
	int updateId;
	ColorInfo updateColor;
	std::vector<PixelInfo*>::reverse_iterator r_itor;
	for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
	{
		if((*r_itor)->visible)
		{
			updateId = (*r_itor)->id;
			updateColor = (*r_itor)->color;
			break;
		}
	}

	std::vector<Pixel>* updatePixelList;
	updatePixelList = TouchHistory::GetInstance()->GetPixelList(updateId);

	std::vector<Pixel>::iterator itor;
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		pixelVector = mPixelTable[(*itor).y][(*itor).x];
		std::vector<PixelInfo*>::iterator itor_swap;
		for(itor_swap = pixelVector->begin(); itor_swap != pixelVector->end(); ++itor_swap)
		{
			if((*itor_swap)->id == updateId)
			{
				pixelVector->push_back((*itor_swap));
				pixelVector->erase(itor_swap);
				break;
			}
		}
	}

	// Update terminal.
	TouchHistory::GetInstance()->UpdateMoveHistory(id, pixel);

	// Move to direction and draw it on LED.
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];

		// Find the previous touch id of pixel to be moved.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id != updateId && (*r_itor)->visible)
				break;
		}

		// Draw the previous touch id of pixel to be moved on LED.
		ColorInfo drawColorInfo;
		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}

	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		// Move pixel.
		int curX = (*itor).x;
		int curY = (*itor).y;
		int nextX = (*itor).x + dx;
		int nextY = (*itor).y + dy;

		(*itor).x = (*itor).x + dx;
		(*itor).y = (*itor).y + dy;

		if(!((0 <= nextX && nextX < 32) &&
			(0 <= nextY && nextY < 29)))
			continue;

		if(!((0 <= curX && curX < 32) &&
			(0 <= curY && curY < 29)))
		{
			// When pixel outside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[nextY][nextX];

			PixelInfo* pixelInfo = new PixelInfo;
			pixelInfo->id = updateId;
			pixelInfo->color = updateColor;
			pixelInfo->visible = true;

			pixelVector->push_back(pixelInfo);
		}
		else
		{
			// When pixel inside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[curY][curX];

			PixelInfo* pixelTomove = pixelVector->back();
			pixelVector->pop_back();

			pixelVector = mPixelTable[nextY][nextX];

			pixelVector->push_back(pixelTomove);
		}

		// Draw it on LED.
		char buffer[4];
		buffer[0] = nextX / 10 + '0';
		buffer[1] = nextX % 10 + '0';
		buffer[2] = nextY / 10 + '0';
		buffer[3] = nextY % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}
}

void LEDManager::DeleteMode(TouchEvent event, int id, float x, float y)
{
	if(event == TOUCH_UP)
		return;

	// Find touched pixel's location.
	Pixel pixel = FindTouchLocation(x, y);

	std::vector<PixelInfo*>* pixelVector = mPixelTable[pixel.y][pixel.x];
	if(pixelVector->empty())
		return;

	// Find the touch id to be deleted.
	std::vector<PixelInfo*>::reverse_iterator r_itor;
	for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
	{
		if((*r_itor)->visible)
			break;
	}

	int deleteId;
	if(r_itor == pixelVector->rend())
		return;
	else
		deleteId = (*r_itor)->id;

	// Get pixel list to be deleted.
	std::vector<Pixel>* deletePixelList;
	deletePixelList = TouchHistory::GetInstance()->GetPixelList(deleteId); 

	// Set pixels' to be deleted visible false and draw last visible pixel on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = deletePixelList->begin(); itor != deletePixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		pixelVector = mPixelTable[(*itor).y][(*itor).x];
		PixelInfo* deletePixel;
		ColorInfo drawColorInfo;

		// Set pixels' to be deleted visible false.
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id == deleteId)
			{
				deletePixel = (*r_itor);
				break;
			}
		}
		deletePixel->visible = false;

		// Draw previous pixel on LED.
		for(++r_itor; r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->visible)
				break;
		}

		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		/* Warning : This might not thread safety!! */
		// Send previous pixel's color.
		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send current coordinate.
		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send original color.
		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}

	// Register history.
	TouchHistory::GetInstance()->PushEditHistory(EDIT_DELETE, deleteId);
}

Pixel LEDManager::FindTouchLocation(float x, float y)
{
	Pixel pixel;
	pixel.x = FindTouchLocationX(x);
	pixel.y = FindTouchLocationY(y);

	return pixel;
}

int LEDManager::FindTouchLocationX(float x)
{
	if(PIXEL_X_0 <= x && x < PIXEL_X_5)
	{
		if(PIXEL_X_0 <= x && x < PIXEL_X_1)
			return 0;
		else if(PIXEL_X_1 <= x && x < PIXEL_X_2)
			return 1;
		else if(PIXEL_X_2 <= x && x < PIXEL_X_3)
			return 2;
		else if(PIXEL_X_3 <= x && x < PIXEL_X_4)
			return 3;
		else
			return 4;
	}
	else if(PIXEL_X_5 <= x && x < PIXEL_X_10)
	{
		if(PIXEL_X_5 <= x && x < PIXEL_X_6)
			return 5;
		else if(PIXEL_X_6 <= x && x < PIXEL_X_7)
			return 6;
		else if(PIXEL_X_7 <= x && x < PIXEL_X_8)
			return 7;
		else if(PIXEL_X_8 <= x && x < PIXEL_X_9)
			return 8;
		else
			return 9;
	}
	else if(PIXEL_X_10 <= x && x < PIXEL_X_15)
	{
		if(PIXEL_X_10 <= x && x < PIXEL_X_11)
			return 10;
		else if(PIXEL_X_11 <= x && x < PIXEL_X_12)
			return 11;
		else if(PIXEL_X_12 <= x && x < PIXEL_X_13)
			return 12;
		else if(PIXEL_X_13 <= x && x < PIXEL_X_14)
			return 13;
		else
			return 14;
	}
	else if(PIXEL_X_15 <= x && x < PIXEL_X_20)
	{
		if(PIXEL_X_15 <= x && x < PIXEL_X_16)
			return 15;
		else if(PIXEL_X_16 <= x && x < PIXEL_X_17)
			return 16;
		else if(PIXEL_X_17 <= x && x < PIXEL_X_18)
			return 17;
		else if(PIXEL_X_18 <= x && x < PIXEL_X_19)
			return 18;
		else
			return 19;
	}
	else if(PIXEL_X_20 <= x && x < PIXEL_X_25)
	{
		if(PIXEL_X_20 <= x && x < PIXEL_X_21)
			return 20;
		else if(PIXEL_X_21 <= x && x < PIXEL_X_22)
			return 21;
		else if(PIXEL_X_22 <= x && x < PIXEL_X_23)
			return 22;
		else if(PIXEL_X_23 <= x && x < PIXEL_X_24)
			return 23;
		else
			return 24;
	}
	else
	{
		if(PIXEL_X_25 <= x && x < PIXEL_X_26)
			return 25;
		else if(PIXEL_X_26 <= x && x < PIXEL_X_27)
			return 26;
		else if(PIXEL_X_27 <= x && x < PIXEL_X_28)
			return 27;
		else if(PIXEL_X_28 <= x && x < PIXEL_X_29)
			return 28;
		else if(PIXEL_X_29 <= x && x < PIXEL_X_30)
			return 29;
		else if(PIXEL_X_30 <= x && x < PIXEL_X_31)
			return 30;
		else
			return 31;
	}
}

int LEDManager::FindTouchLocationY(float y)
{
	if(PIXEL_Y_0 <= y && y < PIXEL_Y_5)
	{
		if(PIXEL_Y_0 <= y && y < PIXEL_Y_1)
			return 0;
		else if(PIXEL_Y_1 <= y && y < PIXEL_Y_2)
			return 1;
		else if(PIXEL_Y_2 <= y && y < PIXEL_Y_3)
			return 2;
		else if(PIXEL_Y_3 <= y && y < PIXEL_Y_4)
			return 3;
		else
			return 4;
	}
	else if(PIXEL_Y_5 <= y && y < PIXEL_Y_10)
	{
		if(PIXEL_Y_5 <= y && y < PIXEL_Y_6)
			return 5;
		else if(PIXEL_Y_6 <= y && y < PIXEL_Y_7)
			return 6;
		else if(PIXEL_Y_7 <= y && y < PIXEL_Y_8)
			return 7;
		else if(PIXEL_Y_8 <= y && y < PIXEL_Y_9)
			return 8;
		else
			return 9;
	}
	else if(PIXEL_Y_10 <= y && y < PIXEL_Y_15)
	{
		if(PIXEL_Y_10 <= y && y < PIXEL_Y_11)
			return 10;
		else if(PIXEL_Y_11 <= y && y < PIXEL_Y_12)
			return 11;
		else if(PIXEL_Y_12 <= y && y < PIXEL_Y_13)
			return 12;
		else if(PIXEL_Y_13 <= y && y < PIXEL_Y_14)
			return 13;
		else
			return 14;
	}
	else if(PIXEL_Y_15 <= y && y < PIXEL_Y_20)
	{
		if(PIXEL_Y_15 <= y && y < PIXEL_Y_16)
			return 15;
		else if(PIXEL_Y_16 <= y && y < PIXEL_Y_17)
			return 16;
		else if(PIXEL_Y_17 <= y && y < PIXEL_Y_18)
			return 17;
		else if(PIXEL_Y_18 <= y && y < PIXEL_Y_19)
			return 18;
		else
			return 19;
	}
	else if(PIXEL_Y_20 <= y && y < PIXEL_Y_25)
	{
		if(PIXEL_Y_20 <= y && y < PIXEL_Y_21)
			return 20;
		else if(PIXEL_Y_21 <= y && y < PIXEL_Y_22)
			return 21;
		else if(PIXEL_Y_22 <= y && y < PIXEL_Y_23)
			return 22;
		else if(PIXEL_Y_23 <= y && y < PIXEL_Y_24)
			return 23;
		else
			return 24;
	}
	else
	{
		if(PIXEL_Y_25 <= y && y < PIXEL_Y_26)
			return 25;
		else if(PIXEL_Y_26 <= y && y < PIXEL_Y_27)
			return 26;
		else if(PIXEL_Y_27 <= y && y < PIXEL_Y_28)
			return 27;
		else
			return 28;
	}
}

void LEDManager::HandleEditor(EditorMode editor)
{
	switch(editor)
	{
	case EDIT_BACK:
		BackEdit();
		break;
	case EDIT_FORWARD:
		ForwardEdit();
		break;
	case EDIT_CLEAR:
		ClearEdit();
		break;
	}
}

void LEDManager::BackEdit()
{
	if(TouchHistory::GetInstance()->IsEditHistoryEmpty())
		return;

	std::pair<EditorMode, int> lastEdit = TouchHistory::GetInstance()->GetLastEdit();
	TouchHistory::GetInstance()->PopEditHistory();

	switch(lastEdit.first)
	{
	case EDIT_DRAW:
		DrawBack(lastEdit.second);
		break;
	case EDIT_MOVE:
		MoveBack(lastEdit.second);
		break;
	case EDIT_DELETE:
		DeleteBack(lastEdit.second);
		break;
	}

	TouchHistory::GetInstance()->PushBackHistory(lastEdit);
}

void LEDManager::DrawBack(int id)
{
	// Get pixel list to be deleted.
	std::vector<Pixel>* deletePixelList;
	deletePixelList = TouchHistory::GetInstance()->GetPixelList(id);
	if(deletePixelList == nullptr)
		return;

	// Set pixels' to be deleted visible false and draw last visible pixel on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = deletePixelList->begin(); itor != deletePixelList->end(); ++itor)
	{
		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];
		PixelInfo* deletePixel;
		ColorInfo drawColorInfo;

		// Set pixels' to be deleted visible false.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id == id)
			{
				deletePixel = (*r_itor);
				break;
			}
		}
		deletePixel->visible = false;

		// Draw previous pixel on LED.
		for(++r_itor; r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->visible)
				break;
		}

		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		/* Warning : This might not thread safety!! */
		// Send previous pixel's color.
		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send current coordinate.
		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send original color.
		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}
}

void LEDManager::MoveBack(int id)
{
	// Swap initial pixel and terminal pixel and get variation info.
	TouchHistory::GetInstance()->RevertMoveHistory(id);
	Variation variation = TouchHistory::GetInstance()->GetMoveHistory(id);

	// Get pixel list and color to draw.
	PixelInfo* updatePixelInfo = mPixelTable[variation.initial.y][variation.initial.x]->back();
	int updateId = updatePixelInfo->id;
	ColorInfo updateColor = updatePixelInfo->color;
	std::vector<Pixel>* updatePixelList = TouchHistory::GetInstance()->GetPixelList(updateId);
	if(updatePixelList == nullptr)
		return;

	// Move to direction and draw it on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];

		// Find the previous touch id of pixel to be moved.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id != updateId && (*r_itor)->visible)
				break;
		}

		// Draw the previous touch id of pixel to be moved on LED.
		ColorInfo drawColorInfo;
		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}

	int dx = variation.terminal.x - variation.initial.x;
	int dy = variation.terminal.y - variation.initial.y;
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		// Move pixel.
		int curX = (*itor).x;
		int curY = (*itor).y;
		int nextX = (*itor).x + dx;
		int nextY = (*itor).y + dy;

		(*itor).x = (*itor).x + dx;
		(*itor).y = (*itor).y + dy;

		if(!((0 <= nextX && nextX < 32) &&
			(0 <= nextY && nextY < 29)))
			continue;

		if(!((0 <= curX && curX < 32) &&
			(0 <= curY && curY < 29)))
		{
			// When pixel outside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[nextY][nextX];

			PixelInfo* pixelInfo = new PixelInfo;
			pixelInfo->id = id;
			pixelInfo->color = updateColor;
			pixelInfo->visible = true;

			pixelVector->push_back(pixelInfo);
		}
		else
		{
			// When pixel inside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[curY][curX];

			PixelInfo* pixelTomove = pixelVector->back();
			pixelVector->pop_back();

			pixelVector = mPixelTable[nextY][nextX];

			pixelVector->push_back(pixelTomove);
		}

		// Draw it on LED.
		char buffer[4];
		buffer[0] = nextX / 10 + '0';
		buffer[1] = nextX % 10 + '0';
		buffer[2] = nextY / 10 + '0';
		buffer[3] = nextY % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}
}

void LEDManager::DeleteBack(int id)
{	
	// Get pixel list to draw.
	std::vector<Pixel>* drawPixelList;
	drawPixelList = TouchHistory::GetInstance()->GetPixelList(id);
	if(drawPixelList == nullptr)
		return;

	// Set pixels' to draw visible true and draw last visible pixel on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = drawPixelList->begin(); itor != drawPixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];

		// Set pixels' to draw visible true.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id == id)
			{
				(*r_itor)->visible = true;
				break;
			}
		}

		// Draw last visible pixel on LED.
		if(r_itor == pixelVector->rbegin())
		{
			ColorInfo drawColorInfo = (*r_itor)->color;
			ColorChip drawColor = ColorChipManager::GetInstance()->
				GetColorChipOfColorInfo(drawColorInfo);

			char buffer[4];
			buffer[0] = COLOR_DATA + '0';
			buffer[1] = drawColor.x + '0';
			buffer[2] = drawColor.y / 10 + '0';
			buffer[3] = drawColor.y % 10 + '0';

			DrawManager::GetInstance()->WriteData(buffer, 4);

			// Send current coordinate.
			buffer[0] = (*itor).x / 10 + '0';
			buffer[1] = (*itor).x % 10 + '0';
			buffer[2] = (*itor).y / 10 + '0';
			buffer[3] = (*itor).y % 10 + '0';

			DrawManager::GetInstance()->WriteData(buffer, 4);
		}
	}
}

void LEDManager::ForwardEdit()
{
	if(TouchHistory::GetInstance()->IsBackHistoryEmpty())
		return;

	std::pair<EditorMode, int> lastBack = TouchHistory::GetInstance()->GetLastBack();
	TouchHistory::GetInstance()->PopBackHistory();

	switch(lastBack.first)
	{
	case EDIT_DRAW:
		DrawForward(lastBack.second);
		break;
	case EDIT_MOVE:
		MoveForward(lastBack.second);
		break;
	case EDIT_DELETE:
		DeleteForward(lastBack.second);
		break;
	}
	
	TouchHistory::GetInstance()->PushEditHistory(lastBack);
}

void LEDManager::DrawForward(int id)
{
	// Get pixel list to draw.
	std::vector<Pixel>* drawPixelList;
	drawPixelList = TouchHistory::GetInstance()->GetPixelList(id);
	if(drawPixelList == nullptr)
		return;

	// Set pixels' to draw visible true and draw last visible pixel on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = drawPixelList->begin(); itor != drawPixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];

		// Set pixels' to draw visible true.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id == id)
			{
				(*r_itor)->visible = true;
				break;
			}
		}

		// Draw last visible pixel on LED.
		if(r_itor == pixelVector->rbegin())
		{
			ColorInfo drawColorInfo = (*r_itor)->color;
			ColorChip drawColor = ColorChipManager::GetInstance()->
				GetColorChipOfColorInfo(drawColorInfo);

			char buffer[4];
			buffer[0] = COLOR_DATA + '0';
			buffer[1] = drawColor.x + '0';
			buffer[2] = drawColor.y / 10 + '0';
			buffer[3] = drawColor.y % 10 + '0';

			DrawManager::GetInstance()->WriteData(buffer, 4);

			// Send current coordinate.
			buffer[0] = (*itor).x / 10 + '0';
			buffer[1] = (*itor).x % 10 + '0';
			buffer[2] = (*itor).y / 10 + '0';
			buffer[3] = (*itor).y % 10 + '0';

			DrawManager::GetInstance()->WriteData(buffer, 4);
		}
	}
}

void LEDManager::MoveForward(int id)
{
	// Swap initial pixel and terminal pixel and get variation info.
	TouchHistory::GetInstance()->RevertMoveHistory(id);
	Variation variation = TouchHistory::GetInstance()->GetMoveHistory(id);

	// Get pixel list and color to draw.
	PixelInfo* updatePixelInfo = mPixelTable[variation.initial.y][variation.initial.x]->back();
	int updateId = updatePixelInfo->id;
	ColorInfo updateColor = updatePixelInfo->color;
	std::vector<Pixel>* updatePixelList = TouchHistory::GetInstance()->GetPixelList(updateId);
	if(updatePixelList == nullptr)
		return;

	// Move to direction and draw it on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		if(!((0 <= (*itor).x && (*itor).x < 32) &&
			(0 <= (*itor).y && (*itor).y < 29)))
			continue;

		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];

		// Find the previous touch id of pixel to be moved.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id != updateId && (*r_itor)->visible)
				break;
		}

		// Draw the previous touch id of pixel to be moved on LED.
		ColorInfo drawColorInfo;
		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}

	int dx = variation.terminal.x - variation.initial.x;
	int dy = variation.terminal.y - variation.initial.y;
	for(itor = updatePixelList->begin(); itor != updatePixelList->end(); ++itor)
	{
		// Move pixel.
		int curX = (*itor).x;
		int curY = (*itor).y;
		int nextX = (*itor).x + dx;
		int nextY = (*itor).y + dy;

		(*itor).x = (*itor).x + dx;
		(*itor).y = (*itor).y + dy;

		if(!((0 <= nextX && nextX < 32) &&
			(0 <= nextY && nextY < 29)))
			continue;

		if(!((0 <= curX && curX < 32) &&
			(0 <= curY && curY < 29)))
		{
			// When pixel outside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[nextY][nextX];

			PixelInfo* pixelInfo = new PixelInfo;
			pixelInfo->id = id;
			pixelInfo->color = updateColor;
			pixelInfo->visible = true;

			pixelVector->push_back(pixelInfo);
		}
		else
		{
			// When pixel inside of LED move inside of LED.
			std::vector<PixelInfo*>* pixelVector = mPixelTable[curY][curX];

			PixelInfo* pixelTomove = pixelVector->back();
			pixelVector->pop_back();

			pixelVector = mPixelTable[nextY][nextX];

			pixelVector->push_back(pixelTomove);
		}

		// Draw it on LED.
		char buffer[4];
		buffer[0] = nextX / 10 + '0';
		buffer[1] = nextX % 10 + '0';
		buffer[2] = nextY / 10 + '0';
		buffer[3] = nextY % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}
}

void LEDManager::DeleteForward(int id)
{
	// Get pixel list to be deleted.
	std::vector<Pixel>* deletePixelList;
	deletePixelList = TouchHistory::GetInstance()->GetPixelList(id);
	if(deletePixelList == nullptr)
		return;

	// Set pixels' to be deleted visible false and draw last visible pixel on LED.
	std::vector<Pixel>::iterator itor;
	for(itor = deletePixelList->begin(); itor != deletePixelList->end(); ++itor)
	{
		std::vector<PixelInfo*>* pixelVector = mPixelTable[(*itor).y][(*itor).x];
		PixelInfo* deletePixel;
		ColorInfo drawColorInfo;

		// Set pixels' to be deleted visible false.
		std::vector<PixelInfo*>::reverse_iterator r_itor;
		for(r_itor = pixelVector->rbegin(); r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->id == id)
			{
				deletePixel = (*r_itor);
				break;
			}
		}
		deletePixel->visible = false;

		// Draw previous pixel on LED.
		for(++r_itor; r_itor != pixelVector->rend(); ++r_itor)
		{
			if((*r_itor)->visible)
				break;
		}

		if(r_itor == pixelVector->rend())
			drawColorInfo = COLOR_12_0;
		else
			drawColorInfo = (*r_itor)->color;

		/* Warning : This might not thread safety!! */
		// Send previous pixel's color.
		ColorChip drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(drawColorInfo);

		char buffer[4];
		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send current coordinate.
		buffer[0] = (*itor).x / 10 + '0';
		buffer[1] = (*itor).x % 10 + '0';
		buffer[2] = (*itor).y / 10 + '0';
		buffer[3] = (*itor).y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);

		// Send original color.
		drawColor = ColorChipManager::GetInstance()->
			GetColorChipOfColorInfo(mColor);

		buffer[0] = COLOR_DATA + '0';
		buffer[1] = drawColor.x + '0';
		buffer[2] = drawColor.y / 10 + '0';
		buffer[3] = drawColor.y % 10 + '0';

		DrawManager::GetInstance()->WriteData(buffer, 4);
	}
}

void LEDManager::ClearEdit()
{

}
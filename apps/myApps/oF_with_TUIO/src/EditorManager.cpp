#include "EditorManager.h"

static EditorManager* pEditorManager = nullptr;

EditorManager::EditorManager()
{
}


EditorManager::~EditorManager()
{
}

EditorManager* EditorManager::GetInstance()
{
	if(pEditorManager == nullptr)
		pEditorManager = new EditorManager;

	return pEditorManager;
}

void EditorManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "Editor" << std::endl;

	if(event == TOUCH_UP)
		return;

	// Find touched editor's location.
	EditorMode editor = FindTouchLocation(x, y);
	std::cout << "Editor mode: " << editor << std::endl;
	if(editor == EDIT_NOT_TOUCHED)
		return;

	// Update current editor mode at LEDManager.
	if(editor == LEDManager::GetInstance()->GetEditor())
		return;
	else
	{
		if(editor == EDIT_DRAW ||
		   editor == EDIT_MOVE ||
		   editor == EDIT_DELETE)
			LEDManager::GetInstance()->SetEditor(editor);
	}

	// Mark touched editor at editor zone.
	char buffer[2];
	buffer[0] = EDIT_DATA + '0';
	buffer[1] = editor + '0';

	DrawManager::GetInstance()->WriteData(buffer, 2);
}

EditorMode EditorManager::FindTouchLocation(float x, float y)
{
	if((DRAW_START_X <= x && x < DRAW_END_X) &&
	   (DRAW_START_Y <= y && y < DRAW_END_Y))
		return EDIT_DRAW;
	else if((MOVE_START_X <= x && x < MOVE_END_X) &&
			(MOVE_START_Y <= y && y < MOVE_END_Y))
		return EDIT_MOVE;
	else if((DELETE_START_X <= x && x < DELETE_END_X) &&
			(DELETE_START_Y <= y && y < DELETE_END_Y))
		return EDIT_DELETE;
	else if((BACK_START_X <= x && x < BACK_END_X) &&
			(BACK_START_Y <= y && y < BACK_END_Y))
		return EDIT_BACK;
	else if((FORWARD_START_X <= x && x < FORWARD_END_X) &&
			(FORWARD_START_Y <= y && y < FORWARD_END_Y))
		return EDIT_FORWARD;
	else if((CLEAR_START_X <= x && x < CLEAR_END_X) &&
			(CLEAR_START_Y <= y && y < CLEAR_END_Y))
		return EDIT_CLEAR;
	else
		return EDIT_NOT_TOUCHED;
}

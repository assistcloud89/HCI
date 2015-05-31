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
		pEditorManager = new EditorManager();

	return pEditorManager;
}

void EditorManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "Editor" << std::endl;

}

#include "EditButtonManager.h"

static EditButtonManager* pEditButtonManager = nullptr;

EditButtonManager::EditButtonManager()
{
}


EditButtonManager::~EditButtonManager()
{
}

EditButtonManager* EditButtonManager::GetInstance()
{
	if(pEditButtonManager == nullptr)
		pEditButtonManager = new EditButtonManager();

	return pEditButtonManager;
}

void EditButtonManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "EditButton" << std::endl;

}

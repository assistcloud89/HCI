#include "LEDManager.h"

static LEDManager* pLEDPManager = nullptr;

LEDManager::LEDManager()
{
}


LEDManager::~LEDManager()
{
}

LEDManager* LEDManager::GetInstance()
{
	if(pLEDPManager == nullptr)
		pLEDPManager = new LEDManager();
	
	return pLEDPManager;
}

void LEDManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "LED" << std::endl;
}

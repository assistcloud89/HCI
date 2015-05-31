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
		pColorChipManager = new ColorChipManager();

	return pColorChipManager;
}

void ColorChipManager::TouchHandle(TouchEvent event, int id, float x, float y)
{
	std::cout << "ColorChip" << std::endl;

}

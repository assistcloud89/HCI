#include "TouchHistory.h"

static TouchHistory* pTouchHistoryManager = nullptr;

TouchHistory::TouchHistory()
{
}


TouchHistory::~TouchHistory()
{
	// todo : clear the memory
}

TouchHistory* TouchHistory::GetInstance()
{
	if(pTouchHistoryManager == nullptr)
		pTouchHistoryManager = new TouchHistory;

	return pTouchHistoryManager;
}

void TouchHistory::PushEditHistory(EditorMode edit, int id)
{
	mEditHistory.push(std::pair<EditorMode, int>(edit, id));
}

void TouchHistory::PushEditHistory(std::pair<EditorMode, int> editHistory)
{
	mEditHistory.push(editHistory);
}

std::pair<EditorMode, int> TouchHistory::GetLastEdit()
{
	return mEditHistory.top();
}

void TouchHistory::PopEditHistory()
{
	if(!mEditHistory.empty())
		mEditHistory.pop();
}

void TouchHistory::PushBackHistory(EditorMode edit, int id)
{
	mBackHistory.push(std::pair<EditorMode, int>(edit, id));
}

void TouchHistory::PushBackHistory(std::pair<EditorMode, int> backHistory)
{
	mBackHistory.push(backHistory);
}

std::pair<EditorMode, int> TouchHistory::GetLastBack()
{
	return mBackHistory.top();
}

void TouchHistory::PopBackHistory()
{
	if(!mBackHistory.empty())
		mBackHistory.pop();
}

void TouchHistory::InsertPixelList(int id, Pixel pixel)
{
	std::unordered_map<int, std::vector<Pixel>*>::iterator itor;
	itor = mPixelList.find(id);
	if(itor == mPixelList.end())
	{
		std::vector<Pixel>* pixelVector = new std::vector < Pixel > ;
		pixelVector->push_back(pixel);

		mPixelList.insert(std::pair<int, std::vector<Pixel>*>(id, pixelVector));
	}
	else
	{
		std::vector<Pixel>* pixelVector = itor->second;
		pixelVector->push_back(pixel);
	}
}

std::vector<Pixel>* TouchHistory::GetPixelList(int id)
{
	std::unordered_map<int, std::vector<Pixel>*>::iterator itor;
	itor = mPixelList.find(id);
	if(itor == mPixelList.end())
		return nullptr;
	
	return itor->second;
}

void TouchHistory::InsertMoveHistory(int id, Pixel initial)
{
	std::unordered_map<int, Variation>::iterator itor;
	itor = mMoveHistory.find(id);
	if(itor == mMoveHistory.end())
	{
		Variation variation = {initial, initial};
		std::cout << variation.terminal.x << "," << variation.terminal.y << std::endl;
		mMoveHistory.insert(std::pair<int, Variation>(id, variation));
	}
}

void TouchHistory::UpdateMoveHistory(int id, Pixel terminal)
{
	std::unordered_map<int, Variation>::iterator itor;
	itor = mMoveHistory.find(id);
	if(itor != mMoveHistory.end())
		itor->second.terminal = terminal;
}

bool TouchHistory::HasMoveHistory(int id)
{
	std::unordered_map<int, Variation>::iterator itor;
	itor = mMoveHistory.find(id);
	if(itor == mMoveHistory.end())
		return false;
	else
		return true;
}

Variation TouchHistory::GetMoveHistory(int id)
{
	return mMoveHistory.find(id)->second;
}

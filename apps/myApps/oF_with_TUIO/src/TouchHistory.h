#ifndef _TOUCH_HISTORY_
#define _TOUCH_HISTORY_

#include "Define.h"

class TouchHistory
{
private:
	TouchHistory();
	~TouchHistory();

public:
	static TouchHistory* GetInstance();

	void PushEditHistory(EditorMode edit, int id);
	void PushEditHistory(std::pair<EditorMode, int> editHistory);
	std::pair<EditorMode, int> GetLastEdit();
	void PopEditHistory();
	bool IsEditHistoryEmpty() { return mEditHistory.empty(); }

	void PushBackHistory(EditorMode edit, int id);
	void PushBackHistory(std::pair<EditorMode, int> backHistory);
	std::pair<EditorMode, int> GetLastBack();
	void PopBackHistory();
	void ClearBackHistory();
	bool IsBackHistoryEmpty() { return mBackHistory.empty(); }

	void InsertPixelList(int id, Pixel pixel);
	std::vector<Pixel>* GetPixelList(int id);

	void InsertMoveHistory(int id, Pixel initial);
	void UpdateMoveHistory(int id, Pixel terminal);
	void RevertMoveHistory(int id);
	bool HasMoveHistory(int id);
	Variation GetMoveHistory(int id);

private:
	std::stack<std::pair<EditorMode, int>> mEditHistory;
	std::stack<std::pair<EditorMode, int>> mBackHistory;
	std::unordered_map<int, std::vector<Pixel>*> mPixelList;
	std::unordered_map<int, Variation> mMoveHistory; // leak 주의!(backhistory 비울 때)
};

#endif
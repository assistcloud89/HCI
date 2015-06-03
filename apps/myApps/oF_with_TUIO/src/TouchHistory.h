#ifndef _TOUCH_HISTORY_
#define _TOUCH_HISTORY_

#include "Define.h"

struct Variation
{
	int dx;
	int dy;
};

class TouchHistory
{
private:
	TouchHistory();
	~TouchHistory();

public:
	static TouchHistory* GetInstance();

	void PushEditHistory(EditorMode edit, int id);
	std::pair<EditorMode, int> GetLastEdit();
	void PopEditHistory();
	bool IsEditHistoryEmpty() { return mEditHistory.empty(); }

	void PushBackHistory(EditorMode edit, int id);
	std::pair<EditorMode, int> GetLastBack();
	void PopBackHistory();
	bool IsBackHistoryEmpty() { return mBackHistory.empty(); }

	void InsertPixelList(int id, Pixel pixel);
	std::vector<Pixel>* GetPixelList(int id);

private:
	std::stack<std::pair<EditorMode, int>> mEditHistory;
	std::stack<std::pair<EditorMode, int>> mBackHistory;
	std::unordered_map<int, std::vector<Pixel>*> mPixelList;
	std::unordered_map<int, Variation> mMoveHistory; // leak ����!(backhistory ��� ��)
};

#endif
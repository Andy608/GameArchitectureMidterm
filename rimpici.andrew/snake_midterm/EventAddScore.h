#ifndef EVENT_ADD_SCORE_H_
#define EVENT_ADD_SCORE_H_

#include <Event.h>

class EventAddScore : public Event
{
public:
	static const std::string sEVENT_ID;

	EventAddScore(int scoreToAdd);
	virtual ~EventAddScore();

	inline int getScoreToAdd() const { return mScoreToAdd; };

private:
	int mScoreToAdd;
};

#endif
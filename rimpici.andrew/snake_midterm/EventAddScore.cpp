#include "EventAddScore.h"

const std::string EventAddScore::sEVENT_ID = "Event Add Score";

EventAddScore::EventAddScore(int scoreToAdd) :
	Event(sEVENT_ID),
	mScoreToAdd(scoreToAdd)
{

}

EventAddScore::~EventAddScore()
{

}
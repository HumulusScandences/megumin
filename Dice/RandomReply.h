#pragma once
#ifndef Random_Reply
#define Random_Reply
#include <string>
#include <vector>
#include <map>

namespace RandomReply
{
	extern std::map<std::string, std::vector<std::string>> mRanDeck;
	extern std::string getReply(std::string RanMsgtype);
};
#endif /*Random_Reply*/

#pragma once
#include "DiceMsgSend.h"
#include "DiceMsg.h"
#include "LogStorage.h"

namespace Dice
{
	class EventHandler
	{
	public:
		void HandleEnableEvent();
		void HandleMsgEvent(DiceMsg dice_msg, bool& block_msg);
		void HandleGroupMemberIncreaseEvent(long long beingOperateQQ, long long fromGroup);
		void HandleDisableEvent();
		void HandleExitEvent();
		void HandleAddGroupEvent(long long fromgroup, long long reQuestQQ, int type, const char* responseFlag);
		void HandleAddFriendEvent(long long reQuestQQ, const char* RequestToken);
		void HandleMasterOder(DiceMsg dice_msg, bool& block_msg);
	};
}
namespace std
{

	extern long long master;
	extern long long masterGroup;
	string Banreason(bool person, long long Groupid);
	class Banlist
	{
	public:
		struct DataReturn
		{
			int level;
			string reason;
		};
		DataReturn* getListData(long long QQID)
		{
			DataReturn* get = 0;
			if (Banlist::Blacklist.count(QQID))get = &Banlist::Blacklist[QQID];
			return get;
		};
		bool findList(long long QQID, int level)
		{
			if (Banlist::Blacklist.count(QQID) && Banlist::Blacklist[QQID].level == level)return 1;
			else return 0;
		}
		bool find(long long QQID)
		{
			if (Banlist::Blacklist.count(QQID))return 1;
			else return 0;
		}
		int findlistON(long long QQID)
		{
			if (Banlist::Blacklist.count(QQID))return Banlist::Blacklist[QQID].level;
			else return 3;
		}
		string listlist(int page)
		{
			string a = "以下是黑名单列表:\n";
			auto i = Blacklist.begin();
			int Maxpage = Blacklist.size() / 10;
			if (Blacklist.size() >= 10 * page)
				for (int k = 10 * page; k > 0; k--)i++;
			else
			{
				int pis = Blacklist.size() - 10;
				if (pis < 0)pis = 0;
				for (int k = pis; k > 0; k--)i++;
			}
			for (int count = 1; count <= 9;)
			{
				if (i == Blacklist.end())break;
				count++;
				if (i->second.level > 3)
					a += to_string(i->first) + "\n";
				if (++i == Blacklist.end())
				{
					a += "黑名单就这么多了\n";
					break;
				}
			}
			a += "  page<" + to_string(page) + "/" + to_string(Maxpage + 1) + ">";
			return a;
		}
		string listlistw(int page)
		{
			string a = "以下是白名单列表:\n";
			auto i = Banlist::Blacklist.begin();
			int Maxpage = Banlist::Blacklist.size() / 10;
			if (Banlist::Blacklist.size() >= 10 * page)
				for (int k = 10 * page; k > 0; k--)i++;
			else
			{
				int pis = Blacklist.size() - 10;
				if (pis < 0)pis = 0;
				for (int k = pis; k > 0; k--)i++;
			}
			for (int count = 1; count <= 9;)
			{
				if (i == Blacklist.end())break;
				count++;
				if (i->second.level < 3)
					a += to_string(i->first) + "\n";
				if (++i == Blacklist.end())
				{
					a += "白名单就这么多了\n";
					break;
				}
			}
			a += "  page<" + to_string(page) + "/" + to_string(Maxpage + 1) + ">";
			return a;
		}
		void insertList(long long QQID, int level, string reason = "默认")
		{
			DataReturn a;
			a.level = level;
			a.reason = reason;
			Banlist::Blacklist[QQID] = a;
			return;
		}
		void eraList(long long QQID)
		{
			Blacklist.erase(QQID);
			return;
		}
		void blacklistFPsave(bool tem);
		void blacklistFPload(bool tem);
		void blacklistFGsave(bool tem);
		void blacklistFGload(bool tem);
	private:
		map<long long, DataReturn>Blacklist;
	};
	extern Banlist BanListFP;
	extern Banlist BanListFG;
}
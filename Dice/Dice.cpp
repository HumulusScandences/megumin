/*
 *  _
 * |     \   |    |  |   _|  |   _|  |  |
 * |  |  |  |     |  |     |  |        |  |_   |  |
 * |  |  |  |     |  |     |  |        |   _|  ||
 * |  ||  |   |  |   |  |_   |  |_
 * |_/   ||  ||  ||  ||
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018-2019 w4123溯洄
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this
 * program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <sstream>
#include <vector>
#include <atlstr.h>

#include <iostream>
#include "APPINFO.h"
#include <ctime>
#include <time.h>
#include "DiceMsg.h"
#include "DiceMsgSend.h"
#include "DiceMsgType.h"
#include "CQEVE.h"
#include "CQEVE_ALL.h"
#include "EventHandler.h"
#include "cqdefine.h"


using namespace std;
using namespace CQ;
Dice::EventHandler MainEventHandler;

EVE_Enable(eventEnable)
{
	MainEventHandler.HandleEnableEvent();
	return 0;
}

EVE_PrivateMsg_EX(eventPrivateMsg)
{
	if (eve.isSystem())return;
	bool block_msg = false;
	MainEventHandler.HandleMsgEvent(Dice::DiceMsg(std::move(eve.message), 0LL, eve.fromQQ, Dice::MsgType::Private), block_msg);
	if (block_msg) eve.message_block();
}

EVE_GroupMsg_EX(eventGroupMsg)
{
	if (eve.isAnonymous())return;
	if (eve.isSystem() )
	{
		if (eve.message.find("被管理员禁言") != string::npos && eve.message.find(to_string(getLoginQQ())) != string::npos)
		{
			for (auto member : getGroupMemberList(eve.fromGroup))
			{
				if (member.permissions == 3) 
				{
					BanListFP.insertList(member.QQID, 4, "因为被禁言拉灰");
					AddMsgToQueue(Dice::DiceMsg("[CQ:at,qq="+ to_string(std::master) + "]我在群" + getGroupList()[eve.fromGroup] +"["+ to_string(eve.fromGroup) + "]被禁言了！我已经溜回来了，顺便把群主[" + to_string(member.QQID) + "]拉灰了!\n该群的审核操作为：\n" + std::Banreason(0,eve.fromGroup), std::masterGroup, master, Dice::MsgType::Group));
					break;
				}
			}
			BanListFG.insertList(eve.fromGroup, 4, "因为被禁言拉黑");
			setGroupLeave(eve.fromGroup, false);
			return;
		}
	}
	bool block_msg = false;
	MainEventHandler.HandleMsgEvent(Dice::DiceMsg(std::move(eve.message),eve.fromGroup, eve.fromQQ, Dice::MsgType::Group), block_msg);
	if (block_msg) eve.message_block();
}

EVE_DiscussMsg_EX(eventDiscussMsg)
{
	if (eve.isSystem())return;
	bool block_msg = false;
	MainEventHandler.HandleMsgEvent(Dice::DiceMsg(std::move(eve.message), eve.fromDiscuss, eve.fromQQ, Dice::MsgType::Discuss), block_msg);
	if (block_msg) eve.message_block();
}

EVE_System_GroupMemberIncrease(eventGroupMemberIncrease)
{
	MainEventHandler.HandleGroupMemberIncreaseEvent(beingOperateQQ, fromGroup);
	return 0;
}

EVE_Disable(eventDisable)
{
	MainEventHandler.HandleDisableEvent();
	return 0;
}

EVE_Exit(eventExit)
{
	MainEventHandler.HandleExitEvent();
	return 0;
}

EVE_Request_AddGroup(eventGroupInvited)
{
	if (subType == 2)
	{
		MainEventHandler.HandleAddGroupEvent(fromGroup, fromQQ, subType, responseFlag);
	}
	return 0;
}

EVE_Request_AddFriend(eventRequest_AddFriend)
{
	MainEventHandler.HandleAddFriendEvent(fromQQ, responseFlag);
	return 0;
}

EVE_System_GroupMemberDecrease(eventGroupMemberDecrease)
{
	if (subType == 3)
	{
		setGroupLeave(fromGroup, false);
		AddMsgToQueue(Dice::DiceMsg("[CQ:at,qq=master]我在群" + getGroupList()[fromGroup] + "[" + to_string(fromGroup) + "]被踢了！我已经溜回来了，顺便把那个[" + to_string(fromQQ) + "]拉黑成了2级黑名单！\n该群的审核操作为：\n" + std::Banreason(0, fromGroup), std::masterGroup, std::master, Dice::MsgType::Group));
		BanListFG.insertList(fromGroup, 4, "因为被踢拉黑");
		BanListFP.insertList(fromQQ, 5, "因为被踢拉黑");
	}
	return 0;
}

MUST_AppInfo_RETURN(CQAPPID);

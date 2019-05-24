#pragma once
#include "DiceMsgSend.h"
#include "DiceMsg.h"
#include "Smtp.h"
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
		//void HandleAddGroupEvent();
	};
}


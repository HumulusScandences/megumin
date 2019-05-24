/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
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
#include "CQLogger.h"
#include "GlobalVar.h"
#include <map>

bool Enabled = false;
bool msgSendThreadRunning = false;

CQ::logger DiceLogger("Dice!");

/*
 * 版本信息
 * 请勿修改Dice_Build, Dice_Ver_Without_Build，DiceRequestHeader以及Dice_Ver常量
 * 请修改Dice_Short_Ver或Dice_Full_Ver常量以达到版本自定义
 */
const unsigned short Dice_Build = 524;
const std::string Dice_Ver_Without_Build = "2.3.8.24";
const std::string DiceRequestHeader = "Dice/" + Dice_Ver_Without_Build;
const std::string Dice_Ver = Dice_Ver_Without_Build + "(" + std::to_string(Dice_Build) + ")";
const std::string Dice_Short_Ver = "Dice! by 溯洄\nmegumin 0.1.3ver\nVersion " + Dice_Ver+"\n斯塔尼亚.shiki等提供了部分代码";
#ifdef __clang__
#ifdef _MSC_VER
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " MSVC " + std::to_string(_MSC_FULL_VER) + " " + __DATE__ + " " + __TIME__ + "]\n斯塔尼亚特供 缇娜·里谢尔参上！(原坂本酱)";
#elif defined(__GNUC__)
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " GNUC " + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__) + " " + __DATE__ + " " + __TIME__ + "]\n斯塔尼亚特供 奈梅斯·西莉亚会照顾好各位的~(原坂本酱)";
#else
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " UNKNOWN]\n斯塔尼亚特供 奈梅斯·西莉亚会照顾好各位的~(原坂本酱)"
#endif /*_MSC_VER*/
#else
#ifdef _MSC_VER
const std::string Dice_Full_Ver = Dice_Short_Ver;
#elif defined(__GNUC__)
const std::string Dice_Full_Ver = Dice_Short_Ver + " [GNUC " + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__) + " " + __DATE__ + " " + __TIME__ + "]\n斯塔尼亚特供 奈梅斯·西莉亚会照顾好各位的~(原坂本酱)";
#else
const std::string Dice_Full_Ver = Dice_Short_Ver + " [UNKNOWN COMPILER]\n斯塔尼亚特供 奈梅斯·西莉亚会照顾好各位的~(原坂本酱)"
#endif /*_MSC_VER*/

#endif /*__clang__*/
//GlobalMsg["strGetCardCatMessage"]
std::map<const std::string, std::string> GlobalMsg
{
	{"strNoExtractionTime","抱歉，您今天的抽取次数已经用完。请明天再试。" },
	{"strCerror","人物卡名称错误，请确认你的当前使用人物卡是否存在" },
	{"strGetBookHumanMailTitle","COC七版规则空白卡19.3.1.xlsx" },
	{"strGetBookHumanMailContent","请使用此链接下载https://share1.heiluo.com/share/link/f87376536f8f4d0baba2178cb621aebe。有更新更好的版本请随时联系窝。"  },
	{"strGetBookHumanMessage","COC七版规则空白卡19.3.1.xlsx已经发到你的邮箱啦~~\n记得回复一下邮件哟，不然以后窝发的邮件会被爸爸扔进垃圾桶的。" },
	{"pathBookOfHuman","C:/Files/Docment/COC七版规则空白卡19.3.1.xlsx"},
	{"strGetBookRPMailTitle","角色扮演三百六十五问.zip" },
	{"strGetBookRPMailContent","请使用此链接下载https://share1.heiluo.com/share/link/8b93f1f15a974d4a9fda1890863a0af1。有更新更好的版本请随时联系窝。" },
	{"strGetBookRPMessage","角色扮演三百六十五问.zip已经发到你的邮箱啦~~\n记得回复一下邮件哟，不然以后窝发的邮件会被爸爸扔进垃圾桶的。" },
	{"pathBookOfRP","C:/Files/Docment/角色扮演三百六十五问.zip"},
	{"strGetBookKPMailTitle","克苏鲁的呼唤第七版守秘人规则书 Version1901.pdf" },
	{"strGetBookKPMailContent","请使用此链接下载https://share1.heiluo.com/share/link/e88daa8d6565440cbff0a8f7c9c8fe29。有更新更好的版本请随时联系窝。" },
	{"strGetBookKPMessage","克苏鲁的呼唤第七版守秘人规则书 Version1901.pdf已经发到你的邮箱啦~~\n记得回复一下邮件哟，不然以后窝发的邮件会被爸爸扔进垃圾桶的。" },
	{"pathBookOfKP","C:/Files/Docment/规则书.pdf"},
    {"strGetBookMakeCardMailTitle","车卡指南.pdf" },
	{"strGetBookMakeCardMailContent","请使用此链接下载https://share1.heiluo.com/share/link/0e1083cdb8144b109be07fd4ef09b082。有更新更好的版本请随时联系窝。" },
	{"strGetBookMakeCardMessage","车卡指南.pdf已经发到你的邮箱啦~~\n记得回复一下邮件哟，不然以后窝发的邮件会被爸爸扔进垃圾桶的。" },
	{"strLogNotSupportPrivateChat","日志记录指令仅在群里起作用，私聊中无效" },
	{"strNameNumTooBig", "生成数量过多!请输入1-10之间的数字!"},
	{"strNameNumCannotBeZero", "生成数量不能为零!请输入1-10之间的数字!"},
	{"strSetInvalid", "无效的默认骰!请输入1-99999之间的数字!"},
	{"strSetTooBig", "默认骰过大!请输入1-99999之间的数字!"},
	{"strInsert", "新人物卡发现！我就帮你记下来咯~"},
	{"strSetCannotBeZero", "默认骰不能为零!请输入1-99999之间的数字!"},
	{"strCSanInvalid", "当前人物卡下不存在理智技能或理智技能数值不正确"},
	{"strCharacterCannotBeZero", "人物作成次数不能为零!请输入1-10之间的数字!"},
	{"strSetInvalid", "无效的默认骰!请输入1-99999之间的数字!"},
	{"strSetTooBig", "默认骰过大!请输入1-99999之间的数字!"},
	{"strSetCannotBeZero", "默认骰不能为零!请输入1-99999之间的数字!"},
	{"strCharacterCannotBeZero", "人物作成次数不能为零!请输入1-10之间的数字!"},
	{"strCharacterTooBig", "人物作成次数过多!请输入1-10之间的数字!"},
	{"strCharacterInvalid", "人物作成次数无效!请输入1-10之间的数字!"},
	{"strSCInvalid", "SC表达式输入不正确,格式为成功扣San/失败扣San,如1/1d6!"},
	{"strSanInvalid", "San值输入不正确,请输入1-99范围内的整数!"},
	{"strEnValInvalid", "技能值或属性输入不正确,请输入1-99范围内的整数!"},
	{"strNameDelErr", "你没有设置名字啊，你让我删除什么"},
	{"strValueErr", "你输错了，傻瓜~！"},
	{"strInputErr", "命令或掷骰表达式输入错误!"},
	{"strUnknownErr", "发生了未知错误!"},
	{"strUnableToGetErrorMsg", "无法获取错误信息!"},
	{"strDiceTooBigErr", "骰娘被你扔出的骰子淹没了"},
	{"strRequestRetCodeErr", "访问服务器时出现错误! HTTP状态码: {0}"},
	{"strRequestNoResponse", "服务器未返回任何信息"},
	{"strTypeTooBigErr", "哇!让窝数数骰子有多少面先~1...2...呜哇不想数啦！"},
	{"strZeroTypeErr", "这是...!!时空裂(骰娘被骰子产生的时空裂缝卷走了)"},
	{"strAddDiceValErr", "你这样要让窝扔骰子扔到什么时候嘛~(请输入正确的加骰参数:5-10之内的整数)"},
	{"strZeroDiceErr", "喂，那边的，你看见我的骰子了吗？"},
	{"strRollTimeExceeded", "掷骰轮数超过了最大轮数限制!"},
	{"strRollTimeErr", "异常的掷骰轮数"},
	{"strWelcomeMsgClearedNotice", "已清除本群的入群欢迎词"},
	{"strWelcomeMsgIsEmptyErr", "错误:没有设置入群欢迎词，清除失败"},
	{"strWelcomeMsgUpdatedNotice", "已更新本群的入群欢迎词"},
	{"strPermissionDeniedErr", "错误:此操作需要群主或管理员权限"},
	{"strNameTooLongErr", "名称过长！！！)"},
	{"strUnknownPropErr", "我可不知道你有这种属性"},
	{"strEmptyWWDiceErr", "格式错误:正确格式为.w(w)XaY!其中X≥1, 5≤Y≤10"},
	{"strPropErr", "请认真的输入你的属性哦~"},
	{"strSetPropSuccess", "嗯嗯，记住了，10是吧，好的好的，我说记住了就是记住了"},
	{"strPropCleared", "不是，你谁啊，我这里可没有你的数据（删除成功）"},
	{"strRuleErr", "规则数据获取失败,具体信息:\n"},
	{"strRulesFailedErr", "请求失败,无法连接数据库"},
	{"strPropDeleted", "我彻底忘记这个技能了"},
	{"strCEmpty", "你现在用的这个人物卡实际不存在啦，这可能是因为数据丢失或程序bug导致的"},
	{"strPropNotFound", "没有这个属性啊喂"},
    {"strCharsetted","你现在使用的人物卡是{0}啦！"},
	{"strChanotFind","你有{0}这张人物卡？可别唬我"},
	{"strDiceInsertValTooSmall","减去这个数字就太小啦！不要耍我啦~"},
	{"strRuleNotFound", "未找到对应的规则信息"},
	{"strProp", "{0}的{1}属性值为{2}"},
	{"strStErr", "格式错误:请参考帮助文档获取.st命令的使用方法"},
	{"strClueErr", "格式错误:请在.clue命令后以空格分割输入线索"},
	{"strClueCleared", "已清除本群内所有线索"},
	{"strClue", "当前群内记录了一下线索，请每天save或一定时间后一定记得使用.clue clr清理，否则时间长了可能造成骰子崩溃，导致线索记录丢失\n"},
	{"strClue", "{0}的线索已录入"},
	{"strClueNotFound", "错误:当前未记录线索"},
	{"strRulesFormatErr", "格式错误:正确格式为.rules[规则名称:]规则条目 如.rules COC7:力量"},
	{"strJrrp", "{0}？嗯我想想啊，这个嘛，我就随便那么一提，你大概也就能扔出{1}个大成功了"},
	{"strJrrpErr", "JRRP获取失败! 错误信息: \n{0}"},
	{"strGetBookCatInfo", "【喵苏鲁图书抽取 - 抽中概率】\n《基础规则》         -30%\n《猫之书(英文版)》      - 10 % \n《牧猫人手册(英文版)》 - 2 % \n《世界观(英文版)》   - 0.4%\n《血光将至log》by杏子 - 0.2%\n《猫之书(中文版)》   - 0.05% \n《牧猫人手册(中文版)》 - 0.01 % \n《世界观(中文版)》    - 0.003 % \n"},
	{"strDeckNotFound", "没听说过呢……"},
	{"strDeckEmpty", "疲劳警告！已经什么也不剩了！"},
	{"strInitListClearedNotice", "成功清除先攻记录!"},
	{"strDrawCard", "{0}啊，那就让我随便帮你抽几张牌：{1}"},
	{"strInitListIsEmptyErr", "错误: 先攻列表为空!"},
	{"strCommandNotAvailableErr", "错误: 此命令仅可在群/讨论组中使用"},
	{"strSuccessfullyEnabledNotice", "啊！终于又想起来我了（抱住哭）！"},
	{"strAlreadyEnabledErr", "我在啦！不要无视我啊！！~"},
	{"strDiceInsertValTooBig", "喂，加上这个数字就太大了啊！"},
	{"strSuccessfullyDisabledNotice", "喂！！为什么不要我了呀哇啊啊啊——"},
	{"strAlreadyDisabledErr", "走了就是走了！！不会窥屏的"},
	{"strObCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用旁观模式!"},
	{"strObCommandAlreadyEnabledErr", "错误: 在本群/讨论组旁观模式已经被启用!"},
	{"strMsgToLong", "太多了太多了，本小姐才懒得给你一个个数呐，你确定只录入了有改动的数据吗" },
	{"strObCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用旁观模式!"},
	{"strObCommandAlreadyDisabledErr", "错误: 在本群/讨论组旁观模式已经被禁用!"},
	{"strObCommandDisabledErr", "管理员已在本群/讨论组中禁用旁观模式!"},
	{"strObListClearedNotice", "成功删除所有旁观者!"},
	{"strJrrpCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用.jrrp命令!"},
	{"strJrrpCommandAlreadyEnabledErr", "错误: 在本群/讨论组中.jrrp命令已经被启用!"},
	{"strJrrpCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用.jrrp命令!"},
	{"strJrrpCommandAlreadyDisabledErr", "错误: 在本群/讨论组中.jrrp命令已经被禁用!"},
	{"strJrrpCommandDisabledErr", "管理员已在此群/讨论组中禁用.jrrp命令!"},
    {"strJrrpsuc","{0}的今日人品？唔唔（现编中），大概，能扔出{1}个大失败？怎么样？（歪头看着你）"},
	{"strHelpCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用.help命令!"},
	{"strHelpCommandAlreadyEnabledErr", "错误: 在本群/讨论组中.help命令已经被启用!"},
	{"strHelpCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用.help命令!"},
	{"strHelpCommandAlreadyDisabledErr", "错误: 在本群/讨论组中.help命令已经被禁用!"},
	{"strHelpCommandDisabledErr", "管理员已在此群/讨论组中禁用.help命令!"},
	{ "strMESpaceErr" ,"你的自定义名称为空或自定义名称首位为空格,不能复读" },
	{ "strCPropNotFound" ,"{0}这个人物卡不存在或该人物卡下不存在数据，你让我告诉你啥呀喂" },
	{ "strCnameErr" ,"你账号下的人物卡已经到达数量上限啦！再多我就记不住了（抱头）" },
	{ "strMESpaceErr" ,"你的自定义名称为空或自定义名称首位为空格,不能复读" },
	{ "strClistCleared" ,"你的人物卡列表已经清空了，嗯，别看我，问就是忘光了" },
	{ "strCharErased" ,"我已经忘了{0}是谁了" },
    { "strKPsetted", "那么我就把这个群记录成你的KP群咯，对抗信息会被发到这里啦！"},
	{ "strMESpaceErr" ,"你的自定义名称为空或自定义名称首位为空格,不能复读" },
	{ "strcharErr" ,"读取信息错误，发生什么了？你问我我问谁嘛" },
	{"strHelpMsg" , Dice_Short_Ver + "\n" + 
		R"(
【通用命令】
.help内容正在整理中，对大家造成麻烦非常抱歉！)"},
};
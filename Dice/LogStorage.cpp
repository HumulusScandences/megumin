/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018-2019 杏牙
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
#include "LogStorage.h"
#include <sstream>
#include <string>
#include <utility>
#include <fstream>
#include "CQTools.h"
using namespace std;

void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = strsrc.size();
	std::string::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

void LogStorage::read()
{
	ifstream ifName(FilePath);
	if (ifName)
	{
		long long GroupID = 0, QQ = 0;
		string name;
		string logItem;
		while (ifName >> QQ >> GroupID >> name >> logItem)
		{
			if (QQ == 000000 & GroupID == 000000)
				break;
			set(QQ, GroupID, base64_decode(name), base64_decode(logItem));
		}
		while (ifName >> GroupID >> name)
		{
			if (GroupID == 000000)
				break;
			set(GroupID, base64_decode(name));
		}
		while (ifName >> GroupID >> QQ)
		{
			set(GroupID, QQ);
		}
	}
}

void LogStorage::record(long long GroupID, string nickName, string logItem)
{
	if (LogFlag.count(GroupID))
	{
		long long recorder = LogRecorder[GroupID];
		string name = LogFlag[GroupID];
		Log[recorder][GroupID][name].push_back(nickName + ":" + logItem);
		string fileName = string(name + "." + to_string(GroupID) + ".txt");
		string filePath = string("C:\\Files\\" + fileName);
		ofstream ost;

		string::size_type idx = logItem.find("(");
		string::size_type idxb = logItem.find("（");
		bool notExistBrackets = (idx == string::npos || idxb == string::npos) && (logItem.find("(") > 2 && logItem.find("（") > 2);
		bool notExistDice = (logItem.find(".") > 2 || logItem.find(".") == -1) && (logItem.find("。") > 2 || logItem.find("。") == -1);
		if (notExistDice) {
			if (notExistBrackets) {
				string::size_type idxa = logItem.find("#");
				if (idxa != string::npos) {
					string::size_type idxaNickName = logItem.find(nickName);
					if (idxa == string::npos) {
						ost.open(filePath, ios::app);
						ost << nickName + " " + logItem << endl;
						ost.close();
					}
					else {
						ost.open(filePath, ios::app);
						ost << logItem << endl;
						ost.close();
					}
				}
				else {
					if (nickName != "") {
						string::size_type idxc = logItem.find("\"");
						string::size_type idxd = logItem.find("“");
						if (idxc != string::npos || idxd != string::npos) {
							ost.open(filePath, ios::app);
							string_replace(logItem, "“", "\"");
							string_replace(logItem, "”", "\"");
							ost << nickName + ": " + logItem  << endl;
							ost.close();
						}
						else {
							ost.open(filePath, ios::app);
							ost << nickName + ": \"" + logItem + "\"" << endl;
							ost.close();
						}
					}
					else {
						ost.open(filePath, ios::app);
						ost << logItem + "\n----------------------------------------------" << endl;
						ost.close();
					}
				}

			}
			else {
				ost.open(filePath, ios::app);
				string_replace(logItem, "（", "");
				string_replace(logItem, "）", "");
				string_replace(logItem, "(", "");
				string_replace(logItem, ")", "");
				ost << "(" + nickName + ": " + logItem + ")"<< endl;
				ost.close();
			}
		}
		else {
			ost.open(filePath, ios::app);
			string::size_type idClue = logItem.find("clue");
			if (idClue == string::npos) {
				ost << "----------------------------------------------\n" + nickName + "请求骰掷: " + logItem << endl;
			}
			else {
				ost << "----------------------------------------------\n" + nickName + "记录线索: " + logItem +"\n----------------------------------------------"<< endl;
			}
			ost.close();
		}
	}
	else
		return;
}

void LogStorage::set(long long QQ, long long GroupID, string name, string logItem)
{
	Log[QQ][GroupID][name].push_back(logItem);
	return;
}

void LogStorage::set(long long GroupID, string name)
{
	LogFlag[GroupID] = name;
	return;
}

void LogStorage::set(long long GroupID, long long QQ)
{
	LogRecorder[GroupID] = QQ;
	return;
}

string LogStorage::get(long long QQ, long long GroupID, string name)
{
	string tmp = "";
	if (Log.count(QQ))
	{
		for (const auto& it1 : Log[QQ])
		{
			for (const auto& it2 : it1.second)
			{
				long long GroupID = it1.first;
				string logname = it2.first;
				if (logname.find(name) != 0)
				{
					continue;
				}
				tmp.append("【下列log所属场景】:" + logname + '\n');
				std::list<std::string>::iterator iter;
				for (iter = Log[QQ][GroupID][logname].begin(); iter != Log[QQ][GroupID][logname].end(); iter++)
				{
					tmp.append(*iter + "\n");
				}

			}
		}
	}
	return tmp;
}

string LogStorage::get(long long QQ, long long GroupID)
{
	string tmp = "";
	if (Log.count(QQ))
	{
		for (const auto& it1 : Log[QQ])
		{
			for (const auto& it2 : it1.second)
			{
				long long GroupID = it1.first;
				string logname = it2.first;
				tmp.append("【下列log所属场景】:" + logname + '\n');
				std::list<std::string>::iterator iter;
				for (iter = Log[QQ][GroupID][logname].begin(); iter != Log[QQ][GroupID][logname].end(); iter++)
				{
					tmp.append(*iter + "\n");
				}

			}
		}
	}
	return tmp;
}

bool LogStorage::haveAuthority(long long QQ, long long GroupID)
{
	if (LogRecorder.count(GroupID))
	{
		return QQ == LogRecorder[GroupID] || QQ == 450609203;
	}
	else
	{
		return true;
	}
}

void LogStorage::save() const
{
	ofstream ofName(FilePath, ios::out | ios::trunc);
	for (const auto& it1 : Log)
	{
		for (const auto& it2 : it1.second)
		{
			for (const auto& it3 : it2.second)
			{
				for (const auto& it4 : it3.second)
				{
					ofName << it1.first << " " << it2.first << " " << base64_encode(it3.first) << " " << base64_encode(it4) << endl;
				}
			}
		}
	}
	ofName << 000000 << " " << 000000 << " " << base64_encode("000000") << " " << base64_encode("000000") << endl;
	for (const auto& it1 : LogFlag)
	{
		ofName << it1.first << " " << base64_encode(it1.second) << endl;
	}
	ofName << 000000 << " " << base64_encode("000000") << endl;
	for (const auto& it1 : LogRecorder)
	{
		ofName << it1.first << " " << it1.second << endl;
	}
}

void LogStorage::clear()
{
	Log.clear();
}

bool LogStorage::del(long long QQ, long long GroupID, string name)
{
	if (Log.count(QQ) && Log[QQ].count(GroupID) && Log[QQ][GroupID].count(name))
	{
		Log[QQ][GroupID].erase(name);
		if (Log[QQ][GroupID].empty())
		{
			Log[QQ].erase(GroupID);
		}
		if (Log[QQ].empty())
		{
			Log.erase(QQ);
		}
		return true;
	}
	return false;
}

bool LogStorage::logOn(long long QQ, long long GroupID, std::string name)
{
	LogFlag[GroupID] = name;
	LogRecorder[GroupID] = QQ;
	return true;
}

bool LogStorage::logOff(long long GroupID)
{
	if (LogFlag.count(GroupID) && LogRecorder.count(GroupID))
	{
		LogFlag.erase(GroupID);
		LogRecorder.erase(GroupID);
		return true;
	}
	return false;
}

LogStorage::LogStorage(const string& FilePath) : StorageBase(FilePath)
{
	LogStorage::read();
}

LogStorage::~LogStorage()
{
	LogStorage::save();
}

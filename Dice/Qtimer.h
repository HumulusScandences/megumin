
#pragma once
#ifndef Dice_Console
#define Dice_Console
#include <string>
#include <vector>
#include <map>
#include <set>
#include <Windows.h>
#include "GlobalVar.h"


//当前时间
extern SYSTEMTIME stNow;
//上班时间
extern std::pair<int, int> ClockToWork;
//下班时间
extern std::pair<int, int> ClockOffWork;

#endif /*Dice_Console*/
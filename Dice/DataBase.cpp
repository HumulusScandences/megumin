#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "../sqlite3.h"

using namespace std;
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		int b = stoi(argv[i] ? argv[i] : "0");
	}
	return 0;
}

int get(int argc, char* argv[])
{
	sqlite3* db;
	char* zErrMsg = 0;
	int  rc;
	char* sql;
	const char* data = "Callback function called";
	rc = sqlite3_open("test.db", &db);
	if (rc)exit(0);
	sql = "SELECT SALARY from BLACKLIST WHERE ";
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
	sqlite3_close(db);
	return 0;
}
int create(int argc, char* argv[])
{
	sqlite3* db;
	char* zErrMsg = 0;
	int  rc;
	char* sql;
	rc = sqlite3_open("blacklist.db", &db);
	if (rc)exit(0);
	sql = "CREATE TABLE BLACKLIST("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        TEXT    NOT NULL,";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)sqlite3_free(zErrMsg);
}
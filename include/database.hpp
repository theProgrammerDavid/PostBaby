#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include "types.hpp"

#define HISTORY_CREATE_QUERY "CREATE TABLE HISTORY(id INTEGER PRIMARY KEY, URL TEXT, METHOD TEXT)"
#define URL_INSERT_QUERY "INSERT INTO HISTORY VALUES (NULL, ?, ?)"
#define HISTORY_SELECT_QUERY "SELECT * FROM HISTORY"
class Database
{
public:
    Database(const std::string &dbPath);
    void insertUrl(const std::string &url, const char* method);
    void getHistory(History *hist);

private:
    SQLite::Database db;

    bool historyExists;
};
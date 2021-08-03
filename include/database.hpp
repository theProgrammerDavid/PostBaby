#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

#define URL_INSERT_QUERY "INSERT INTO HISTORY VALUES (NULL,?)"

class Database
{
public:
    Database(const std::string &dbPath);
    void insertUrl(const std::string &url);
    

private:
    SQLite::Database db;

    bool historyExists;
};
#pragma once
#include "types.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "logger.hpp"

#define HISTORY_CREATE_QUERY \
  "CREATE TABLE HISTORY(id INTEGER PRIMARY KEY, URL TEXT, METHOD INTEGER)"
#define URL_INSERT_QUERY "INSERT INTO HISTORY VALUES (NULL, ?, ?)"
#define HISTORY_SELECT_QUERY "SELECT * FROM HISTORY"
#define HISTORY_DELETE_QUERY "DELETE * FROM HISTORY WHERE URL=?"
#define HISTORY_SIZE_QUERY "SELECT COUNT(*) FROM HISTORY"
#define HISTORY_DELETE_QUERY "DELETE FROM HISTORY WHERE id=?"
class Database
{
public:
  /**
   * @param dbPath path of the db file
   * */
  Database(const std::string &dbPath);

  /**
   * @param url HTTP URL of request
   * @param method TYPE of HTTP request
   * */
  void insertUrl(const std::string &url, const int method);

  /**
   * @param hist History object to retrieve from db
   * */
  void getHistory(std::vector<request> &hist);

  /**
   * @return number of rows of history
   * */
  int getNumRows();

  /**
   * Deletes row from db
   * @param row unique id of row to delete
   * */
  void deleteRow(const int row);

private:
  SQLite::Database db;

  bool historyExists;
};
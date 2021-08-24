#include "database.hpp"

void Database::insertUrl(const std::string &url, const char *method) {
  try {
    SQLite::Statement query(db, URL_INSERT_QUERY);
    SQLite::bind(query, url, method);
    query.exec();
  } catch (const std::exception &e) {
    throw e;
  }
}

void Database::getHistory(History *hist) {
  try {

    SQLite::Statement query(db, HISTORY_SELECT_QUERY);
    while (query.executeStep()) {
      hist->push_back(makeHistory(query.getColumn(0), query.getColumn(1),
                                  query.getColumn(2)));
    }
  } catch (const std::exception &e) {
    throw e;
  }
}

Database::Database(const std::string &dbPath)
    : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  try {
    this->historyExists = this->db.tableExists("HISTORY");
    if (!historyExists) {
      db.exec(HISTORY_CREATE_QUERY);
    }
  } catch (const std::exception &e) {
    std::cout << "Error occured in Database Constructor\n"
              << e.what() << std::endl;
  }
}
#include "database.hpp"

void Database::insertUrl(const std::string &url, const int method) {
  try {
    SQLite::Statement query(db, URL_INSERT_QUERY);
    SQLite::bind(query, url, method);
    query.exec();
  } catch (const std::exception &e) {
    Logger *logger = Logger::getInstance();
    logger->error("Unable to insert history from db in function insertUrl",
                  {url.c_str(), e.what()});
    // pfd::message("Database Error", e.what(), pfd::choice::ok, pfd::icon::error);
    std::cerr << "Database Error " << e.what() << "\n";
    throw e;
  }
}

void Database::getHistory(std::vector<request> &hist) {
  hist.clear();
  // hist.reserve(this->getNumRows());
  try {
    SQLite::Statement query(db, HISTORY_SELECT_QUERY);
    while (query.executeStep()) {
      hist.push_back(
          {query.getColumn(0), query.getColumn(1), query.getColumn(2)});
    }
  } catch (const std::exception &e) {
    Logger *logger = Logger::getInstance();
    logger->error("Unable to populate history ", {e.what()});
    // pfd::message("Database Error", e.what(), pfd::choice::ok, pfd::icon::error);
    std::cerr << "Database Error " << e.what() << "\n";
    throw e;
  }
}

void Database::deleteRow(const int row) {
  try {
    SQLite::Statement query(db, HISTORY_DELETE_QUERY);
    SQLite::bind(query, row);
    query.exec();
  } catch (const std::exception &e) {
    Logger *logger = Logger::getInstance();
    logger->error("Unable to delete row in db ", {e.what()});
    // pfd::message("Database Error", e.what(), pfd::choice::ok, pfd::icon::error);
    std::cerr << "Database Error " << e.what() << "\n";
  }
}

int Database::getNumRows() {
  try {
    SQLite::Statement query(db, HISTORY_SIZE_QUERY);
    query.executeStep();
    return query.getColumn(0);
  } catch (const std::exception &e) {
    Logger *logger = Logger::getInstance();
    logger->error("Unable to get number of rows in history ", {e.what()});
    std::cerr << "Database Error " << e.what() << "\n";
    // pfd::message("Database Error", e.what(), pfd::choice::ok, pfd::icon::error);
    return -1;
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
    Logger *logger = Logger::getInstance();
    logger->error("Unable to get number of rows in history ", {e.what()});
    std::cerr << "Database Error " << e.what() << "\n";
    // pfd::message("Database Error", e.what(), pfd::choice::ok, pfd::icon::error);
  }
}

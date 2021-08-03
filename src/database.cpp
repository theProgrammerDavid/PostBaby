#include "database.hpp"

void Database::insertUrl(const std::string &url)
{
    SQLite::Statement query(db, URL_INSERT_QUERY);
    SQLite::bind(query, url);
    query.exec();
}

Database::Database(const std::string &dbPath) : db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try
    {
        this->historyExists = this->db.tableExists("HISTORY");
        if (!historyExists)
        {
            db.exec("CREATE TABLE HISTORY(id INTEGER PRIMARY KEY, URL TEXT)");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error occured in Database Constructor\n"
                  << e.what() << std::endl;
    }
}
#include "sqlite3_db.h"
#include <stdint.h>
#include <string.h>
Sqlite3Connect::Sqlite3Connect()
{

}

Sqlite3Connect::~Sqlite3Connect()
{

}

bool Sqlite3Connect::init(const char* dbname)
{
    int32_t r;

    r = sqlite3_open(dbname, &_db);


    return true;
}

int  Sqlite3Connect::execute(const char* sql)
{
    char** result;
    int nrow = 0;      
    int ncolumn = 0;
    char* zErrMsg = nullptr;
    auto r = sqlite3_get_table(_db, sql, &result, &nrow, &ncolumn, &zErrMsg);

    if (r != SQLITE_OK)
    {
        return -1;
    }

    _record_set.reset_data(result, nrow, ncolumn);
    return r;
}


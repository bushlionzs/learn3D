#pragma once

class DBTask;
#include "platform_mutex.h"
#include "scoped_lock.h"
#include "GameSingleton.h"

class CMySQLConnection;
class CMySQLRecordSet;

class DBManager : public GameSingleton<DBManager>
{
public:
    DBManager();
    ~DBManager();

    bool initialize();
    void run();
    void runDBTask(DBTask* task);
    void addDbTask(DBTask* task);

    

    void addCharListTask(const char* account);
private:
    std::list<DBTask*> mTaskList;
    std::list<DBTask*> mBackup;
    PlatformMutex mMutex;

    std::string mSql;

    CMySQLConnection* mConnection = nullptr;
    CMySQLRecordSet* mRecordSet = nullptr;
};
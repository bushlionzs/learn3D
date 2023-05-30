#include "stdafx.h"
#include "db_manager.h"
#include "db_task.h"
#include "mysql_db.h"

template<>
DBManager* GameSingleton<DBManager>::m_sSingleton = NULL;

DBManager::DBManager()
{

}

DBManager::~DBManager()
{

}


bool DBManager::initialize()
{
    mConnection = new CMySQLConnection;

    mConnection->SetConnectionString("127.0.0.1", 3306, "khan", "root", "123456");

    bool ret = mConnection->Connect();
    const char* szerror = mConnection->GetLastErrorInfo();
    mRecordSet = new CMySQLRecordSet;
    return ret;
}

void DBManager::run()
{
    if (mTaskList.empty())
        return;
    mBackup.clear();
    {
        ScopedLock<PlatformMutex> lock(mMutex);
        mBackup.swap(mTaskList);
    }
    

    for (auto it = mBackup.begin(); it != mBackup.end(); it++)
    {
        runDBTask(*it);
        

        delete* it;
    }

}


void DBManager::runDBTask(DBTask* task)
{
    mSql = task->get_sql();
    if (!mSql.empty())
    {
        mRecordSet->Clear();
        int ret = mConnection->ExecuteEx(mSql.c_str(), *mRecordSet);
        if (ret == CMySQLConnection::Failed)
        {
            task->failed(mConnection->GetLastError());
        }
        else
        {
            task->success(mRecordSet);
        }
    }
    else
    {
        task->failed(-1);
    }
}

void DBManager::addDbTask(DBTask* task)
{
    ScopedLock<PlatformMutex> lock(mMutex);
    mTaskList.push_back(task);
}

void DBManager::addCharListTask(const char* account)
{
    std::string strAccount(account);
    CharListTask* task = new CharListTask(strAccount);
    addDbTask(task);
}
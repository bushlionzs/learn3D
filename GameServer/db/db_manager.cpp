#include "stdafx.h"
#include "db_manager.h"
#include "db_task.h"
#include "mysql_db.h"
#include "sqlite3_db.h"

template<>
DBManager* GameSingleton<DBManager>::m_sSingleton = NULL;

DBManager::DBManager()
{

}

DBManager::~DBManager()
{

}


void db_init_func()
{
}

uint32_t db_entry_func(uint32_t moduleid,
    uint32_t msg_id,
    uint64_t sender,
    uint64_t param,
    void* msg,
    uint32_t msg_size,
    void* pModulePrivateData)
{
    DBManager::GetSingletonPtr()->run();
    return 0;
}

bool DBManager::initialize()
{
    //mConnection = CMySQLConnection::createConnection("127.0.0.1", 3306, "khan", "root", "123456");

    mConnection = Sqlite3Connect::createConnection("../../server_resources/ServerConfig/test.sqlite3");
    bool ret = mConnection->connect();

    m_module = create_platform_module(1, "db_module");
    m_module->attach_module(0, db_init_func, db_entry_func, nullptr);
    m_module->run_module();

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
        int ret = mConnection->execute(mSql.c_str());
        if (ret == CMySQLConnection::Failed)
        {
            task->failed(mConnection->getLastError());
        }
        else
        {
            task->success(mConnection->getRecordSet());
        }
    }
    else
    {
        task->failed(-1);
    }
}

void DBManager::addDbTask(DBTask* task)
{
    {
        ScopedLock<PlatformMutex> lock(mMutex);
        mTaskList.push_back(task);
    }
    m_module->post_module_message(0,
        0,
        0,
        0,
        0,
        0,
        false);
}

void DBManager::addCharListTask(const char* account)
{
    std::string strAccount(account);
    CharListTask* task = new CharListTask(strAccount);
    addDbTask(task);
}
#pragma once

#include <net_handle.h>
class IRecordSet;
struct CHARDBNODE;

class DBTask
{
public:
    DBTask();
    ~DBTask();

    virtual std::string get_sql() = 0;

    virtual void failed(int32_t errcode)  {}

    virtual void success(IRecordSet* recordset) {}
};

class CharListTask : public DBTask
{
public:
    CharListTask(std::string& account);
    ~CharListTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mAccount;
};

class CharDataTask : public DBTask
{
public:
    CharDataTask(std::string& guid, NetHandle h);
    ~CharDataTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;

    NetHandle mHandle;
};

class CharItemTask : public DBTask
{
public:
    CharItemTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharItemTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;

    CHARDBNODE* mCharDBNode;
};

class CharSkillTask : public DBTask
{
public:
    CharSkillTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharSkillTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

class CharAbilityTask : public DBTask
{
public:
    CharAbilityTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharAbilityTask();
    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

class CharPrescriptionTask : public DBTask
{
public:
    CharPrescriptionTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharPrescriptionTask();
    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};
class CharQuestTask : public DBTask
{
public:
    CharQuestTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharQuestTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

class CharQuestDataTask :public DBTask
{
public:
    CharQuestDataTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharQuestDataTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

class CharDataExTask : public DBTask
{
public:
    CharDataExTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharDataExTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

class CharHorseTask : public DBTask
{
public:
    CharHorseTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion);
    ~CharHorseTask();

    virtual std::string get_sql();

    virtual void failed(int32_t errcode);
    virtual void success(IRecordSet* recordset);
private:
    std::string mGuid;
    int32_t mdbversion;
    CHARDBNODE* mCharDBNode;
};

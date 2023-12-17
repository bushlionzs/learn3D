#pragma once
#include <stdint.h>

class IRecordSet
{
public:
    virtual ~IRecordSet()
    {

    }
    virtual void clear() {}

    virtual uint32_t getRecordCount() { return 0; }

    virtual uint32_t getFieldCount() { return 0; }

    virtual bool getNextRecord() { return false; }

    virtual const char* getFieldValue(unsigned int nIndex)
    {
        return nullptr;
    }
};

class IDBConnect
{
public:
    virtual ~IDBConnect()
    {

    }

    virtual bool isConnected()
    {
        return false;
    }

    virtual IRecordSet* getRecordSet()
    {
        return nullptr;
    }

    virtual bool connect()
    {
        return false;
    }

    virtual bool execute(const char* sql)
    {
        return false;
    }

    virtual uint32_t getLastError()
    {
        return 0;
    }
};
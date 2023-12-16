#pragma once
#include "sqlite3.h"
#include "record_set.h"

class Sqlite3RecordSet : public IRecordSet
{
    friend class Sqlite3Connect;
public:
    Sqlite3RecordSet()
    {
        _data = nullptr;
    }

    ~Sqlite3RecordSet()
    {

    }
    virtual void clear()
    {
    }

    virtual uint32_t getRecordCount() 
    { 
        return _row;
    }

    virtual uint32_t getFieldCount() 
    { 
        return _coloumn;
    }

    virtual bool getNextRecord() 
    { 
        _current_row++;

        return _current_row >= _row;
    }

    virtual const char* getFieldValue(unsigned int nIndex) override
    {
        uint32_t offset = _current_row * _coloumn + nIndex;
        return _data[offset];
    }

    void reset_data(char** data, uint32_t row, uint32_t column)
    {
        if (_data != nullptr)
        {
            sqlite3_free_table(_data);
        }
        _row = row;
        _coloumn = column;
        _current_row = 0;
        _data = data;
    }
private:
    char** _data;
    uint32_t _row;
    uint32_t _coloumn;

    uint32_t _current_row = 0;
};

class Sqlite3Connect
{
public:
    Sqlite3Connect();
    ~Sqlite3Connect();

    bool init(const char* dbname);

    int  execute(const char* sql);

    virtual bool isConnected()
    {
        return  _db != nullptr;
    }

    IRecordSet* getRecordSet()
    {
        return &_record_set;
    }

    virtual bool connect()
    {
        return false;
    }


    virtual uint32_t getLastError()
    {
        return 0;
    }
private:
    sqlite3* _db;
    Sqlite3RecordSet _record_set;
};
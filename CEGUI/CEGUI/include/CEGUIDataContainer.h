

#ifndef _CEGUIDataContainer_h_
#define _CEGUIDataContainer_h_

#include "CEGUIBase.h"

#include <malloc.h>



namespace CEGUI
{

template <class T>
class CEGUIEXPORT DataContainer
{
public:
	
	
    DataContainer()
      : mData(0),
        mSize(0)
    {
    }

	
	virtual ~DataContainer(void) 
    { 
        release();
    }

	
	
    void setData(T* data) { mData = data; }

	
    T* getDataPtr(void) { return mData; }

	
    void setSize(size_t size) { mSize = size; }

	
    size_t getSize(void) const { return mSize; }

	
    virtual void release(void)
    {
        if(mData)
        {
            delete mData;
            mData = 0;
        }
    }
	
protected:
    T* mData;
    size_t mSize;
};


class RawDataContainer : public DataContainer<unsigned char> 
{
public:
    RawDataContainer() : DataContainer<unsigned char>()
    {
    }

    ~RawDataContainer() 
    {
        release();
    }

    void release(void)
    {
        if(mData)
        {
            delete [] mData;
            mData = 0;
        }
    }
};




} 

#endif	



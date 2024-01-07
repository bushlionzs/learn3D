

#ifndef _CEGUIRefPtr_h_
#define _CEGUIRefPtr_h_

#include "CEGUIBase.h"

namespace CEGUI {

class CEGUIEXPORT Referenced
{
public:
  Referenced() : d_refCount(0) {}
  Referenced(const Referenced&) : d_refCount(0) {}

  Referenced& operator=(Referenced&) { return *this; }

  
  void addRef() const { ++d_refCount; }
  
  
  void release() const { if (!--d_refCount) delete this; }
  
  
  void releaseButKeep() const { --d_refCount; }
  
  
  int refCount() const { return d_refCount; }
 
protected:
  virtual ~Referenced();
  mutable int d_refCount;
};


template<class T> class RefPtr
{
  T* d_p;

public:

  
  RefPtr()     : d_p(new T()) { d_p->addRef(); }

  RefPtr(T* t) : d_p(t) { if (t)   d_p->addRef(); }
  RefPtr(const RefPtr& r) : d_p(r.d_p)
                        { if (r.d_p) d_p->addRef(); }
  ~RefPtr()
  { if (d_p) {
      d_p->release();
      d_p = 0;
    }
  }

  RefPtr& operator=(T* q)
  {
    if (d_p != q) {
      T* t = d_p;
      d_p = q;
      if (q) q->addRef();
      if (t) t->release();
    }
    return *this;
  }

  RefPtr& operator=(const RefPtr& r) { return *this = r.d_p; }

  bool operator==(const RefPtr& r) const { return d_p == r.d_p; }
  bool operator!=(const RefPtr& r) const { return d_p != r.d_p; }
  bool operator< (const RefPtr& r) const { return d_p <  r.d_p; }
  bool operator> (const RefPtr& r) const { return d_p >  r.d_p; }

  bool operator ==(const T* q) const { return d_p == q; }
  bool operator !=(const T* q) const { return d_p != q; }
  bool operator < (const T* q) const { return d_p <  q; }
  bool operator > (const T* q) const { return d_p >  q; }


        T& operator*()        { return *d_p; }
  const T& operator*() const  { return *d_p; }

        T* operator->()       { return d_p; }
  const T* operator->() const { return d_p; }

        T* get()              { return d_p; }
  const T* get() const        { return d_p; }

  bool operator!() const	    { return d_p == 0; }
  bool valid() const	        { return d_p != 0; }

  T* release()
  {
    T* t = d_p;
    if (d_p) {
      d_p->releaseButKeep();
      d_p = 0;
    } 
    return t;
  }
};

} 

#endif

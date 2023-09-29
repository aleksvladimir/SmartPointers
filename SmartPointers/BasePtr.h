#pragma once

template<class T>
class BasePtr
{
protected:
  T * myPtr_ = nullptr;

public:

  // default_ctr
  BasePtr( T * ptr = nullptr ) : myPtr_( ptr ) {}

  // get
  T * get()
  {
    return myPtr_;
  }

  // *
  T & operator * ()
  {
    return *get();
  }

};

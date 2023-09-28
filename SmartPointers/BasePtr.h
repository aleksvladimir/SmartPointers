#pragma once

template<class T>
class BasePtr
{
protected:
  T * myPtr_ = nullptr;

public:

  // default_ctr
  BasePtr( T * ptr = nullptr ) : myPtr_( ptr ) {}

  virtual ~BasePtr();

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

  // release
  T * release()
  {
    auto tmp = myPtr_;
    myPtr_ = nullptr;
    return tmp;
  }

  // reset
  void reset( T * ptr = nullptr )
  {
    if ( ptr != myPtr_ )
      delete myPtr_;
    myPtr_ = ptr;
  }
};

template <class T>
BasePtr<T>::~BasePtr()
{
  delete myPtr_;
}

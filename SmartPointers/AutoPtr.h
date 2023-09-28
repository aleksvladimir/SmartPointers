#pragma once

template<class T>
class AutoPtr
{
  T* myPtr_ = nullptr;

public:

  // default_ctr
  AutoPtr( T * ptr = nullptr ) : myPtr_( ptr ) {}

  // copy_ctr
  AutoPtr( AutoPtr<T> & autoPtr ) : myPtr_( autoPtr.release() ) {}

  // copy_operator
  AutoPtr<T> & operator = ( AutoPtr<T> & right )
  {
    myPtr_ = right.release();
    return *this;
  }

  // get
  T* get()
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
  void reset( T* ptr = nullptr )
  {
    if ( ptr != myPtr_ )
      delete myPtr_;
    myPtr_ = ptr;
  }
};
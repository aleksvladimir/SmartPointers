#pragma once
#include "BasePtr.h"

template<class T>
class AutoPtr : public BasePtr<T>
{
public:

  // default_ctr
  AutoPtr( T * ptr = nullptr ) : BasePtr( ptr ) {}

  // copy_ctr
  AutoPtr( AutoPtr<T> & autoPtr )
  {
    myPtr_ = autoPtr.release();
  }

  // copy_operator
  AutoPtr<T> & operator = ( AutoPtr<T> & right )
  {
    myPtr_ = right.release();
    return *this;
  }
};

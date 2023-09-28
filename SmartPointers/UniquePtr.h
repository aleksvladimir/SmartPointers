#pragma once
#include "BasePtr.h"

template<class T>
class UniquePtr : public BasePtr<T>
{
public:

  // default_ctr
  UniquePtr( T * ptr = nullptr ) : BasePtr( ptr ) {}

  // copy_ctr
  UniquePtr( const UniquePtr & ptr ) = delete;

  // copy_operator
  UniquePtr & operator = ( UniquePtr & ptr ) = delete;

  // move_ctr
  UniquePtr( UniquePtr && ptr )
  {
    myPtr_ = ptr.release();
  }

  // move_operator
  UniquePtr & operator = ( UniquePtr && ptr )
  {
    myPtr_ = ptr.release();
    return *this;
  }
};

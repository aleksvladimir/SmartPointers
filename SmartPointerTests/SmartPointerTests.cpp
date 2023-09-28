#include "../SmartPointers/UniquePtr.h"
#include "..\SmartPointers\AutoPtr.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmartPointerTests
{
	TEST_CLASS(SmartPointerTests)
	{
	public:
		
		TEST_METHOD(Test_std_auto_ptr)
		{
			//default_ctr
			std::auto_ptr<int> a_ptr( new int );
			Assert::IsNotNull( a_ptr.get() );

			//default_ctr
			std::auto_ptr<int> a_ptr3;
			//*a_ptr3 = 3;
			Assert::IsNull( a_ptr3.get() );

			//copy_ctr
			auto a_ptr2( a_ptr );
			Assert::IsNull( a_ptr.get() );

			//*
			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			//copy_operator
			a_ptr3 = a_ptr2;
			Assert::IsNull( a_ptr2.get() );

			//reference
			auto & a_ptr4 = a_ptr3;
			Assert::IsNotNull( a_ptr3.get() );
			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr3 );

			// release
			auto p = a_ptr3.release();
			Assert::IsNull( a_ptr3.get() );
			Assert::IsNotNull( p );

			// reset
			std::auto_ptr<int> resetObj( p );
			resetObj.reset();
			Assert::IsNull( resetObj.get() );
			Assert::AreNotEqual( 4, *p );
		}

		TEST_METHOD(Test_AutoPtr)
		{
			//default_ctr
			AutoPtr<int> a_ptr( new int );
			Assert::IsNotNull( a_ptr.get() );

			//default_ctr
			AutoPtr<int> a_ptr3;
			//*a_ptr3 = 3;
			Assert::IsNull( a_ptr3.get() );

			//copy_ctr
			auto a_ptr2( a_ptr );
			Assert::IsNull( a_ptr.get() );

			//*
			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			//copy_operator
			a_ptr3 = a_ptr2;
			Assert::IsNull( a_ptr2.get() );

			//reference
			auto & a_ptr4 = a_ptr3;
			Assert::IsNotNull( a_ptr3.get() );
			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr3 );

			// release
			auto p = a_ptr3.release();
			Assert::IsNull( a_ptr3.get() );
			Assert::IsNotNull( p );

			// reset
			AutoPtr<int> resetObj( p );
			resetObj.reset();
			Assert::IsNull( resetObj.get() );
			Assert::AreNotEqual( 4, *p );
		}

		TEST_METHOD( Test_std_unique_ptr )
		{
			// default_ctr
			std::unique_ptr<int> a_ptr0;
			std::unique_ptr<int> a_ptr1( new int );
			Assert::IsNull( a_ptr0.get() );
			Assert::IsNotNull( a_ptr1.get() );

			// move_ctr + get
			auto a_ptr2( std::move( a_ptr1 ) );
			Assert::IsNull( a_ptr1.get() );
			//auto a_ptr2( a_ptr1 );	// compile error! copy_ctr is deleted!

			// *
			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			// move_operator
			a_ptr0 = std::move(a_ptr2);	// same as "static_cast< std::unique_ptr<int> &&>(a_ptr2)"
			//a_ptr0 = a_ptr2;				// compile error! copy_operator is deleted!
			Assert::IsNull( a_ptr2.get() );

			//reference
			auto & a_ptr4 = a_ptr0;
			Assert::IsNotNull( a_ptr0.get() );
			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr0 );

			// release
			auto p = a_ptr0.release();
			Assert::IsNull( a_ptr0.get() );
			Assert::IsNotNull( p );

			// reset
			std::unique_ptr<int> resetObj( p );
			resetObj.reset();
			Assert::IsNull( resetObj.get() );
			Assert::AreNotEqual( 4, *p );
		}

		TEST_METHOD( Test_UniquePtr )
		{
			// default_ctr
			UniquePtr<int> a_ptr0;
			UniquePtr<int> a_ptr1( new int );
			Assert::IsNull( a_ptr0.get() );
			Assert::IsNotNull( a_ptr1.get() );

			// move_ctr + get
			auto a_ptr2( std::move( a_ptr1 ) );
			Assert::IsNull( a_ptr1.get() );
			//auto a_ptr2( a_ptr1 );	// compile error! copy_ctr is deleted!

			// *
			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			// move_operator
			a_ptr0 = std::move( a_ptr2 );	// same as "static_cast< std::unique_ptr<int> &&>(a_ptr2)"
			//a_ptr0 = a_ptr2;				// compile error! copy_operator is deleted!
			Assert::IsNull( a_ptr2.get() );

			//reference
			auto & a_ptr4 = a_ptr0;
			Assert::IsNotNull( a_ptr0.get() );
			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr0 );

			// release
			auto p = a_ptr0.release();
			Assert::IsNull( a_ptr0.get() );
			Assert::IsNotNull( p );

			// reset
			UniquePtr<int> resetObj( p );
			resetObj.reset();
			Assert::IsNull( resetObj.get() );
			Assert::AreNotEqual( 4, *p );
		}
	};
}

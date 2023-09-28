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
			std::auto_ptr<int> a_ptr1(new int);
			auto a_ptr2( a_ptr1 );
			Assert::IsNull(a_ptr1.get());

			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			std::auto_ptr<int> a_ptr3;
			//*a_ptr3 = 3;
			Assert::IsNull( a_ptr3.get() );

			a_ptr3 = a_ptr2;
			Assert::IsNull( a_ptr2.get() );

			auto p = a_ptr3.get();
			a_ptr3.reset(new int(3));
			Assert::IsNotNull( a_ptr3.get() );
			Assert::AreNotEqual( p, a_ptr3.get() );

			auto & a_ptr4 = a_ptr3;
			Assert::IsNotNull( a_ptr3.get() );

			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr3 );
		}

		TEST_METHOD(Test_AutoPtr)
		{
			AutoPtr<int> a_ptr(new int);
			auto a_ptr2( a_ptr );
			Assert::IsNull(a_ptr.get());

			*a_ptr2 = 2;
			Assert::AreEqual( 2, *a_ptr2 );

			AutoPtr<int> a_ptr3;
			//*a_ptr3 = 3;
			Assert::IsNull( a_ptr3.get() );

			a_ptr3 = a_ptr2;
			Assert::IsNull( a_ptr2.get() );

			auto p = a_ptr3.get();
			a_ptr3.reset( new int(3) );
			Assert::IsNotNull( a_ptr3.get() );
			Assert::AreNotEqual( p, a_ptr3.get() );

			auto & a_ptr4 = a_ptr3;
			Assert::IsNotNull( a_ptr3.get() );

			*a_ptr4 = 4;
			Assert::AreEqual( 4, *a_ptr3 );
		}
	};
}

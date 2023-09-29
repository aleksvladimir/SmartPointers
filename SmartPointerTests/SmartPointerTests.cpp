#include "..\SmartPointers\SharedPtr.h"
#include "..\SmartPointers\UniquePtr.h"
#include "..\SmartPointers\AutoPtr.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

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

		TEST_METHOD(Test_MyAutoPtr)
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

		TEST_METHOD( Test_MyUniquePtr )
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
			a_ptr0 = std::move( a_ptr2 );
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


		TEST_METHOD( Test_std_shared_ptr )
		{
			// default_ctr
			std::shared_ptr<int> a_ptr0;
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
			Assert::IsNull( a_ptr0.get() );
			{
				// default_ctr
				std::shared_ptr<int> a_ptr1( new int( 1 ) );	// counter = 1
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsNotNull( a_ptr1.get() );

				// copy_ctr
				auto a_ptr2( a_ptr1 );												// counter = 2
				Assert::IsNotNull( a_ptr2.get() );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );

				// copy_operator
				a_ptr0 = a_ptr2;															// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				std::vector<long> counters{ a_ptr0.use_count(), a_ptr1.use_count(), a_ptr2.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_ctr
				auto a_ptr3( std::move( a_ptr2 ) );						// counter = 3
				Assert::IsNull( a_ptr2.get() );
				Assert::IsNotNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr2.use_count() ) );
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				counters.clear();
				counters = { a_ptr0.use_count(), a_ptr1.use_count(), a_ptr3.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_operator
				a_ptr0 = std::move( a_ptr3 );									// counter = 2
				Assert::IsNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr3.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

				// *
				*a_ptr0 = 2;
				Assert::AreEqual( 2, *a_ptr1 );

				//reference
				auto & a_ptr4 = a_ptr0;												// counter = 2
				Assert::IsNotNull( a_ptr0.get() );
				*a_ptr4 = 4;
				Assert::AreEqual( 4, *a_ptr0 );

				// reset
				std::shared_ptr<int> resetObj( a_ptr0 );			// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				resetObj.reset();															// counter = 2
				resetObj.reset();															// counter = 2
				Assert::IsNull( resetObj.get() );
				Assert::AreEqual( 0, static_cast< int >( resetObj.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

			}																								// counter = 1
			Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );

			a_ptr0.reset();																	// counter = 0
			Assert::IsNull( a_ptr0.get() );
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
		}

		TEST_METHOD( Test_MySharedPtr )
		{
			// default_ctr
			SharedPtr<int> a_ptr0;
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
			Assert::IsNull( a_ptr0.get() );
			{
				// default_ctr
				SharedPtr<int> a_ptr1( new int( 1 ) );				// counter = 1
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsNotNull( a_ptr1.get() );

				// copy_ctr
				auto a_ptr2( a_ptr1 );												// counter = 2
				Assert::IsNotNull( a_ptr2.get() );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );

				// copy_operator
				a_ptr0 = a_ptr2;															// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				std::vector<long> counters{ a_ptr0.use_count(), a_ptr1.use_count(), a_ptr2.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_ctr
				auto a_ptr3( std::move( a_ptr2 ) );						// counter = 3
				Assert::IsNull( a_ptr2.get() );
				Assert::IsNotNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr2.use_count() ) );
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				counters.clear();
				counters = { a_ptr0.use_count(), a_ptr1.use_count(), a_ptr3.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_operator
				a_ptr0 = std::move( a_ptr3 );									// counter = 2
				Assert::IsNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr3.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

				// *
				*a_ptr0 = 2;
				Assert::AreEqual( 2, *a_ptr1 );

				//reference
				auto & a_ptr4 = a_ptr0;												// counter = 2
				Assert::IsNotNull( a_ptr0.get() );
				*a_ptr4 = 4;
				Assert::AreEqual( 4, *a_ptr0 );

				// reset
				SharedPtr<int> resetObj( a_ptr0 );						// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				resetObj.reset();															// counter = 2
				resetObj.reset();															// counter = 2
				Assert::IsNull( resetObj.get() );
				Assert::AreEqual( 0, static_cast< int >( resetObj.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

			}																								// counter = 1
			Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );

			a_ptr0.reset();																	// counter = 0
			Assert::IsNull( a_ptr0.get() );
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
		}
	};
}

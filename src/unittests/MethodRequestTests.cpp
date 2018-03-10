#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MethodRequest.h"
#include "ActiveObject.h"
#include <iostream>

using ::testing::Return;
using namespace std;

TEST(MethodRequestTests, macro_MR1)
{
    class A
    {
        public:
            MOCK_METHOD1(method1, void (int) );
            MOCK_METHOD2(method2, void (int,int) );
    };
    
    A a;

    auto macromr = MR1(A,a,method1,int,1);
    EXPECT_CALL(a, method1(1));
    macromr->execute();
    delete macromr;
}

TEST(MethodRequestTests, methodRequest)
{
    class A
    {
        public:
            MOCK_METHOD1(method1, void (int) );
            MOCK_METHOD2(method2, void (int,int) );
    };
    
    A a;
    MethodRequestBase *ptr;

    
    MethodRequest<A,int> mr1(a,false, &A::method1 ,1);

    ASSERT_EQ( &(mr1.object), &a );
    ASSERT_EQ( get<0>(mr1.params), 1 );
    ASSERT_EQ( mr1.method_to_call, &A::method1);

    MethodRequest<A,int,int> mr2(a,false, &A::method2 ,2,3);
    
    EXPECT_CALL(a, method1(1));
    ptr = &mr1;
    ptr->execute();

    EXPECT_CALL(a, method2(2,3));
    ptr = &mr2;
    ptr->execute();

}

TEST(MethodRequestTests, mem_allocation )
{
    class A
    {
        public:
            MOCK_METHOD1(method1, void (int) );
    };
    
    A a;
    
    auto macromr = MR1(A,a,method1,int,1);
    ASSERT_EQ(macromr== NULL, false);
    delete macromr;


}

#include "gtest/gtest.h"
#include "grey.h"
#include "MethodRequest.h"
#include <iostream>
using ::testing::_;
using ::testing::Return;
using namespace std;

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
    
    MethodRequest<A,int> mr1(a, &A::method1 ,1);

    ASSERT_EQ( &(mr1.object), &a );
    ASSERT_EQ( get<0>(mr1.params), 1 );
    ASSERT_EQ( mr1.method_to_call, &A::method1);

    MethodRequest<A,int,int> mr2(a, &A::method2 ,2,3);
    
    EXPECT_CALL(a, method1(1));
    ptr = &mr1;
    ptr->execute();

    EXPECT_CALL(a, method2(2,3));
    ptr = &mr2;
    ptr->execute();

}

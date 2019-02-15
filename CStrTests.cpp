#include "test_failures.h"
#include "CStr.h"
#include <cstring>

static void testCStrConstructor()
{
	CStr foo("foo");
	CStr a;
	TEST_FAIL_CHECK(foo.getLen() == 3);
	TEST_FAIL_CHECK(a.getLen() == 0);
}

static void testCStrCopyConstructor()
{
	CStr foo("Hello!");
	CStr foo2(foo);
	TEST_FAIL_CHECK(foo.getLen() == foo2.getLen());
	TEST_FAIL_CHECK(std::strcmp(foo.getStr(), foo2.getStr()) == 0);
}

static void testCStrAssignment()
{
	CStr foo = "12345";
	CStr test;
	size_t testCap = test.getCap();
	test = foo;
	TEST_FAIL_CHECK(test.getCap() == testCap);
	TEST_FAIL_CHECK(test.getLen() == foo.getLen());
	TEST_FAIL_CHECK(std::strcmp(foo.getStr(), test.getStr()) == 0);
}

int main(int argc, char const *argv[])
{
	testCStrConstructor();
	testCStrCopyConstructor();
	testCStrAssignment();
	TEST_FAIL_RETURN
}

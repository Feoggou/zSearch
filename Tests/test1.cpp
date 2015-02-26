#include "gmock/gmock.h"
#include "gtest/internal/gtest-port.h"
#include "zSearch/zSearch.h"

#if 0
ZSearch search;
//set options
search.SetOption(ZSearch::FileNameCaseSensitive, true);

std::vector<ZResultItem> results = search(L"localDirName");

Assert::AreEqual(results.size(), std::size_t(1), L"result size: expected 1");
//TODO: or displayName
Assert::AreEqual(results.back().fullFileName, std::wstring(L"testFile.txt"), L"result name: expected \"testFile.txt\"");
#endif

TEST(Case_Search, NonExistingFile)
{
	ZSearch search;
	ZSearch::Results = search(L"");
	ASSERT_EQ(results.size(), 0);
}

#if 0
TEST(FactorialTest, HandlesZeroInput) {
	EXPECT_EQ(1, 1);
}

class TestClass : public ::testing::Test
{
public:
	void SetUp()
	{
	}

	void TearDown()
	{
	}

	static void SetUpTestCase() {}
	static void TearDownTestCase() {}

protected:
	int a;
	static int b;
};

int TestClass::b = 4;

TEST_F(TestClass, IsEmptyInitially) {
	SCOPED_TRACE("-------------msg1");
	EXPECT_EQ(0, 0);
}

TEST(DISABLED_TestFunc, WontRun) {
	EXPECT_EQ(0, 1);
}

#endif

int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	
	return RUN_ALL_TESTS();
}

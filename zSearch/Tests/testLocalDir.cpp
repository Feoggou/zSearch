/*
*  Copyright 2015 Samuel Ghineț
*  
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*  
*      http://www.apache.org/licenses/LICENSE-2.0
*  
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

#include <chrono>

#include "gmock/gmock.h"
#include "zLib/zLib.h"
#include "zLib/Dir.h"
#include "zSearch/zSearch.h"

using namespace Zen;

//TODO: we already have this function in zLib_testDir. We ought to make a lib for test utilities.
std::tstring createUniqueName(const std::tstring& base = T("uniqueName_"))
{
	std::tstring uniqueName = base;

	auto now = std::chrono::steady_clock::now();
	auto rep = now.time_since_epoch().count();
	std::wstring ws;

	uniqueName += ZEN_TO_TSTRING(rep);

	return uniqueName;
}

TEST(CaseSearch, NonExistingDir)
{
    ZSearch search;
    ZSearch::Results results = search();
    ASSERT_EQ(results.size(), 0);
}

class MockEnumerator : public Enumerator
{
public:
    MOCK_CONST_METHOD0(HaveNext, bool());
    MOCK_METHOD0(Advance, void());
    MOCK_CONST_METHOD0(GetItem, Item());
};

TEST(TestLocalDir, FindOneItem_InCurrentDirectory)
{
    MockEnumerator e;
    Enumerator::Item item("OneItem");

    EXPECT_CALL(e, GetItem())
        .Times(1)
        .WillOnce(::testing::Return(item));

    EXPECT_CALL(e, HaveNext())
            .Times(2)
            .WillOnce(::testing::Return(true))
            .WillOnce(::testing::Return(false));

    EXPECT_CALL(e, Advance())
            .Times(1);

    //no options - using default ones.
    ZSearch search(e);
    ZSearch::Results results = search();

    ASSERT_EQ(results.size(), std::size_t(1));

    const auto& result = results.back();
    ASSERT_EQ(result.fullName, std::tstring("OneItem"));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

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

#include "gmock/gmock.h"
#include "zSearch/zSearch.h"


namespace Zen {
inline std::ostream& operator<< (std::ostream& os, const ResultItem& result)
{
    os << "{ name = '" << result.fullName << "'; }, ";
    return os;
}

inline std::ostream& operator<< (std::ostream& os, const Results& results)
{
    os << std::to_string(results.size()) << " = {";

    for (const auto& item: results)
        os << item;

    os << "}";

    return os;
}

inline bool operator==(const Results& lhs, const Results& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    for (int i = 0; i < lhs.size(); ++i)
    {
        std::cout << "left = " << lhs[i].fullName << "; right = " << rhs[i].fullName << std::endl;
        if (lhs[i].fullName != rhs[i].fullName)
            return false;
    }

    return true;
}
}


class MockFind : public Zen::IFinder
{
public:
    MOCK_METHOD0(DoFind, Zen::Results());

    Zen::Results operator()() override { return DoFind(); }
};


TEST(CaseSearch, EmptyDir)
{
    MockFind finder;
    EXPECT_CALL(finder, DoFind())
            .WillOnce(::testing::Return(Zen::Results{}));

    Zen::ZSearch search{finder};
    Zen::Results results = search();

    ASSERT_EQ(results.size(), 0);
}

TEST(TestCurrentDir, FindOneItem)
{
    Zen::Results expected = { { std::tstring(T("OneItem")) } };
    MockFind finder;
    EXPECT_CALL(finder, DoFind())
            .WillOnce(::testing::Return(expected));

    Zen::ZSearch search{finder};
    Zen::Results actual = search();

    ASSERT_EQ(actual, expected);
}


int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

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
#include "gtest/internal/gtest-port.h"
#include "zSearch/zSearch.h"
#include "zLib/zLib.h"

using namespace Zen;

TEST(CaseSearch, NonExistingDir)
{
	ZSearch search;
    ZSearch::Results results = search(T(""));
	ASSERT_EQ(results.size(), 0);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	
	return RUN_ALL_TESTS();
}

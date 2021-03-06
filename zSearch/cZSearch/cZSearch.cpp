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

#include "zSearch/zSearch.h"
#include "zLib/zLib.h"
#include "zLib/FSException.h"

#include <iostream>

#ifdef WIN32

#include <locale>
#include <codecvt>

#define COUT std::wcout

namespace std {
    inline std::ostream& operator<< (std::ostream& os, const std::wstring& str)
    {
        os << std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(str);
        return os;
    }
}

#else
#define COUT std::cout
#endif

int main(int argc, tchar* argv[])
{
    Zen::Finder finder;
    Zen::ZSearch search{finder};

    Zen::Results results;

    try
    {
        results = search();
    }
    catch (FSException& e)
    {
        std::cout << "Exception: " << e.Code() << std::endl;
    }

    for (const auto& item : results)
        std::cout << item.fullName << std::endl;

    std::cout << "Items found: " << results.size() << std::endl;

    return 0;
}

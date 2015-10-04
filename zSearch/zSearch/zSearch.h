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

#pragma once

#if PROJ_LINK_SHARED
#ifdef ZSEARCH_EXPORTS
#ifdef WIN32
#define ZSEARCH_API __declspec(dllexport)
#elif defined (__linux__)
#define ZSEARCH_API __attribute__ ((visibility ("default")))
#endif //WIN32
#else
/* if ZSEARCH_EXPORTS not defined: */
#ifdef WIN32
#define ZSEARCH_API __declspec(dllimport)
#elif defined(__linux__)
#define ZSEARCH_API __attribute__ ((visibility ("default")))
#endif //WIN32
#endif //ZSEARCH_EXPORTS
#else
/*if PROJ_LINK_SHARED is not defined (i.e. building as static lib)*/
#define ZSEARCH_API
#endif //PROJ_LINK_SHARED

#include <vector>
#include <string>

#include "zLib/zLib.h"
#include "zLib/Enumerator.h"

namespace Zen
{
	struct ZSEARCH_API SearchResultItem
	{
        enum Type { Unknown = 0, File, Directory };

        SearchResultItem() = default;
        SearchResultItem(const Enumerator::Item& item)
            : fullName(item.name)
            , type(Type(item.type))
        {}

        /* fullName: default value - a) if result = not found / invalid; b) if filter, means 'any' */
        std::tstring fullName;
        /* type: default value (Unknown) - a) if result = not found / invalid; b) if filter, means 'any' */
        Type type;
	};

	class ZSEARCH_API ZSearch
	{
	public:
		typedef std::vector<SearchResultItem> Results;

    public:
        ZSearch() : m_enumerator(nullptr), m_typeFilter(SearchResultItem::Unknown) {}
        explicit ZSearch(Enumerator& e) : m_enumerator(&e), m_typeFilter(SearchResultItem::Unknown) {}

        void SetTypeFilter(SearchResultItem::Type type)
        {
            m_typeFilter = type;
        }

        Results operator()();

    private:
        Enumerator* m_enumerator;
        SearchResultItem::Type m_typeFilter;
	};
}

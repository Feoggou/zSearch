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

#include "zSearch.h"

#include "zLib/Dir.h"
#include "zLib/Enumerator.h"

#include <iostream>
#include <memory>

using namespace Zen;

ZSearch::Results ZSearch::operator()(const std::tstring& path)
{
	Results r;

    Dir dir(path);
    std::unique_ptr<Enumerator> e (dir.CreateEnumerator());

    /* the issue with this approach above is... you'll have to keep the 'search handle' in Dir,
     * and it will only become disposed when a) Dir is destroyed, which can happen much later;
     * b) Another search happens on the same Dir object - which might destroy the previous search;
     * c) the user of the class Dir issues 'close handle' manually.
     * If we use an enumerator, instead, we solve these issues.
    */

    while (e->HaveNext()) {
        SearchResultItem item = e->GetItem();
        r.push_back(item);
        e->Advance();
    }

    /* THOUGHTS - mocking Enumerator:
     * we can create a 'fake' enumerator, which, when you call begin(), it returns an iterator holding a 'Result' struct.
     * The single result fills all required struct fields.
     *
     * Q: Should we use, instead of a 'struct', a std::map or a std::vector of variants?
     * or perhaps we should define a 'ItemField' as { Name, (Domain)Type, Value }, where Value is a Variant?
     * A: No. It is too much burden. "YAGNI". Do the simplest thing that work. Minimalist.
     */

	return r;
}

#pragma once

#include <vector>

namespace Zen
{
	struct SearchResultItem
	{
		std::wstring fullName;
	};

	class ZSearch
	{
	public:
		typedef std::vector<SearchResultItem> Results;

		Results operator()(const std::wstring& path);
	};
}
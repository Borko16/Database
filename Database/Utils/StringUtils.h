#pragma once
#include <string>

inline char toLower(char elem)
{
	int diff = 'a' - 'A';
	if ('A' <= elem && elem <= 'Z')
	{
		return elem + diff;
	}
	return elem;
}

inline const std::string& toLowerString(const std::string& input)
{
	std::string result = input;
	for (size_t i = 0; i < result.size(); i++)
	{
		result[i] = toLower(result[i]);
	}

	return result;
}

inline bool compareInsensitive(const std::string& a, const std::string& b)
{
	if (a.size() != b.size()) return false;

	for (size_t i = 0; i < a.size(); ++i)
	{
		if (toLower(a[i]) != toLower(b[i])) return false;
	}
	return true;
}
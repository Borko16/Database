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

inline std::string toLowerString(const std::string& input)
{
	std::string result = input;
	for (size_t i = 0; i < result.size(); i++)
	{
		result[i] = toLower(result[i]);
	}
	return result;
}

inline bool compareInsensitive(const std::string& first, const std::string& second)
{
	if (first.size() != second.size())
	{
		return false;
	}

	for (size_t i = 0; i < first.size(); i++)
	{
		if (toLower(first[i]) != toLower(second[i]))
		{
			return false;
		}
	}
	return true;
}

inline bool substringInsensitive(const std::string& first, const std::string& second)
{
	return toLowerString(first).find(toLowerString(second)) != std::string::npos;
}

inline std::string removeQuotes(const std::string& input)
{
	if (input.size() >= 2 && input.front() == '"' && input.back() == '"')
	{
		return input.substr(1, input.size() - 2);
	}

	throw std::invalid_argument("invalid string");
}

inline std::string unescapeString(const std::string& input)
{
	std::string result;
	result.reserve(input.size());

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == '\\')
		{
			if (i + 1 >= input.size())
			{
				throw std::invalid_argument("Backslash at end of string");
			}

			char next = input[i + 1];
			if (next == '\\')
			{
				result += '\\';
			}
			else if (next == '\"')
			{
				result += '\"';
			}
			else
			{
				throw std::invalid_argument("Invalid escape sequence in string");
			}

			i++;
		}
		else
		{
			result += input[i];
		}
	}

	return result;
}

inline bool isDelimiter(char elem)
{
	std::vector<char> tokenDelimiters = { ' ', '\t', '\n', '\r', '\f', '\v' };
	for (size_t i = 0; i < tokenDelimiters.size(); i++)
	{
		if (elem == tokenDelimiters[i])
		{
			return true;
		}
	}

	return false;
}

inline std::vector<std::string> splitWords(std::string& command)
{
	std::vector<std::string> result;
	std::string current;

	for (size_t i = 0; i < command.length(); i++)
	{
		if (!isDelimiter(command[i]))
		{
			current += command[i];
		}
		else
		{
			if (!current.empty())
			{
				result.push_back(current);
				current.clear();
			}
		}
	}

	if (!isDelimiter(command[command.length() - 1]))
	{
		result.push_back(current);
	}

	return result;
}
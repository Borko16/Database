#include "StringColumn.h"
#include <stdexcept>
#include "../Utils/PrintUtils.h"

StringColumn::StringColumn(const std::string& name, Table* table)
    : Column(name, table)
{
}

void StringColumn::resize(size_t newSize)
{
	size_t oldSize = getSize();
	values.resize(newSize);
	isNULL.resize(newSize);

	for (size_t i = oldSize; i < getSize(); i++)
	{
		setNull(i);
	}
}

std::string StringColumn::getType() const
{
	return "string";
}

static std::string removeQuotes(const std::string& input)
{
	if (input.size() >= 2 && input.front() == '"' && input.back() == '"')
	{
		return input.substr(1, input.size() - 2);
	}
	
	throw std::invalid_argument("invalid string");
}

static std::string unescapeString(const std::string& input)
{
	std::string result;
	result.reserve(input.size());

	for (size_t i = 0; i < input.size(); ++i)
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

			++i;
		}
		else
		{
			result += input[i];
		}
	}

	return result;
}

bool StringColumn::matchingValues(size_t index, const std::string& value) const
{
	try
	{
		std::string cleaned = tryParseValue(value);
		return values[index] == cleaned;
	}
	catch (...)
	{
		return false;
	}
}

void StringColumn::updateValue(size_t index, const std::string& newValue)
{
	if (!updateIfNull(index, newValue))
	{
		std::string parsed = tryParseValue(newValue);
		setValue(index, parsed);
	}
}

void StringColumn::printValueAt(size_t index) const
{
	if (isCellNull(index))
	{
		printNull();
	}
	else
	{
		printValue(values[index]);
	}
}

void StringColumn::printValueAt(size_t index, std::ofstream& ofs) const
{
	if (isCellNull(index))
	{
		printNull(ofs);
	}
	else
	{
		printValue(values[index], ofs);
	}
}

bool StringColumn::modify(const Column& source, size_t index)
{
	std::string parsed = source.getAsString(index);

	if (!updateIfNull(index, parsed))
	{
		return true;
	}

	setValue(index, parsed);
	return true;
}

void StringColumn::remove(size_t index)
{
	values.erase(values.begin() + index);
	isNULL.erase(isNULL.begin() + index);
}

void StringColumn::insert(const std::string& value)
{
	size_t index = getSize();
	resize(index + 1);

	if (updateIfNull(index, value))
	{
		setNull(index);
		return;
	}

	std::string parsed = tryParseValue(value);
	setValue(index, parsed);
}

void StringColumn::saveToFile(std::ofstream& ofs) const
{
	int type = static_cast<int>(ColumnType::STRING);
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(int));

	saveNameAndSize(ofs);

	for (size_t i = 0; i < getSize(); ++i)
	{
		size_t strLen = values[i].size();
		ofs.write(reinterpret_cast<const char*>(&strLen), sizeof(size_t));
		ofs.write(values[i].c_str(), strLen);
	}

	saveNullFlags(ofs);
}

void StringColumn::loadFromFile(std::ifstream& ifs)
{
	loadNameAndSize(ifs);

	for (size_t i = 0; i < getSize(); ++i)
	{
		ifs.read(reinterpret_cast<char*>(&values[i]), sizeof(double));
	}

	loadNullFlags(ifs);
}

void StringColumn::exportCell(std::ofstream& ofs, size_t index) const
{
	if (isCellNull(index))
	{
		printNull(ofs);
	}
	else
	{
		printValue(values[index], ofs);
	}
}

StringColumn* StringColumn::clone() const
{
	return new StringColumn(*this);
}

std::string StringColumn::getAsString(size_t index) const
{
	if (isNULL[index])
		return "NULL";

	return values[index];
}

const std::string& StringColumn::tryParseValue(const std::string& value) const
{
	return unescapeString(removeQuotes(value));
}

void StringColumn::setValue(size_t index, const std::string& value)
{
	values[index] = value;
	isNULL[index] = false;
}

void StringColumn::setNull(size_t index)
{
	values[index] = "";
	isNULL[index] = true;
}


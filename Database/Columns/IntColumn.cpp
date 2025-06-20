#include "IntColumn.h"
#include <stdexcept>
#include "../Utils/PrintUtils.h"

IntColumn::IntColumn(const std::string& name, Table* table)
	: Column(name, table)
{
}

void IntColumn::resize(size_t newSize)
{
	size_t oldSize = getSize();
	values.resize(newSize);
	isNULL.resize(newSize);

	for (size_t i = oldSize; i < getSize(); i++)
	{
		setNull(i);
	}
}

std::string IntColumn::getType() const
{
	return "int";
}

bool IntColumn::matchingValues(size_t index, const std::string& value) const
{
	try 
	{
		int target = tryParseValue(value);
		return values[index] == target;
	}
	catch (...) 
	{
		return false;
	}
}

void IntColumn::updateValue(size_t index, const std::string& newValue)
{
	if (!updateIfNull(index, newValue))
	{
		int parsed = tryParseValue(newValue);
		setValue(index, parsed);
	}
}

void IntColumn::printValueAt(size_t index) const
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

void IntColumn::printValueAt(size_t index, std::ofstream& ofs) const
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

bool IntColumn::modify(const Column& source, size_t index)
{
	std::string value = source.getAsString(index);

	if (updateIfNull(index, value))
	{
		return true;
	}

	try
	{
		int parsed = tryParseValue(value);
		setValue(index, parsed);
		return true;
	}
	catch (...)
	{
		setNull(index);
		return false;
	}
}

void IntColumn::remove(size_t index)
{
	values.erase(values.begin() + index);
	isNULL.erase(isNULL.begin() + index);
}

void IntColumn::insert(const std::string& value)
{
	size_t index = getSize();
	resize(index + 1);

	if (updateIfNull(index, value))
	{
		setNull(index);
		return;
	}

	int parsed = tryParseValue(value);
	setValue(index, parsed);
}

void IntColumn::saveToFile(std::ofstream& ofs) const
{
	int type = static_cast<int>(ColumnType::INT);
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(int));

	saveNameAndSize(ofs);

	for (size_t i = 0; i < getSize(); i++)
	{
		ofs.write(reinterpret_cast<const char*>(&values[i]), sizeof(int));
	}

	saveNullFlags(ofs);
}

void IntColumn::loadFromFile(std::ifstream& ifs)
{
	loadNameAndSize(ifs);

	for (size_t i = 0; i < getSize(); i++)
	{
		ifs.read(reinterpret_cast<char*>(&values[i]), sizeof(double));
	}

	loadNullFlags(ifs);
}

void IntColumn::exportCell(std::ofstream& ofs, size_t index) const
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

IntColumn* IntColumn::clone() const
{
	return new IntColumn(*this);
}

std::string IntColumn::getAsString(size_t index) const
{
	if (isCellNull(index))
	{
		return "Null";
	}

	return std::to_string(values[index]);
}

int IntColumn::tryParseValue(const std::string& value) const
{
	return std::stoi(value);
}

void IntColumn::setValue(size_t index, int value)
{
	values[index] = value;
	isNULL[index] = false;
}

void IntColumn::setNull(size_t index)
{
	values[index] = 0;
	isNULL[index] = true;
}
#include "DoubleColumn.h"
#include "../Utils/PrintUtils.h"

DoubleColumn::DoubleColumn(const std::string& name, Table* table)
	: Column(name, table)
{
}

void DoubleColumn::resize(size_t newSize)
{
	size_t oldSize = getSize();
	values.resize(newSize);
	isNULL.resize(newSize);

	for (size_t i = oldSize; i < getSize(); i++)
	{
		setNull(i);
	}
}

std::string DoubleColumn::getType() const
{
	return "double";
}

bool DoubleColumn::matchingValues(size_t index, const std::string& value) const
{
	try
	{
		double target = tryParseValue(value);
		return values[index] == target;
	}
	catch (...)
	{
		return false;
	}
}

void DoubleColumn::updateValue(size_t index, const std::string& newValue)
{
	if (!updateIfNull(index, newValue))
	{
		double parsed = tryParseValue(newValue);
		setValue(index, parsed);
	}
}

void DoubleColumn::printValueAt(size_t index) const
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

void DoubleColumn::printValueAt(size_t index, std::ofstream& ofs) const
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

bool DoubleColumn::modify(const Column& source, size_t index)
{
	std::string value = source.getAsString(index);

	if (updateIfNull(index, value))
	{
		return true;
	}

	try
	{
		double parsed = tryParseValue(value);
		setValue(index, parsed);
		return true;
	}
	catch (...)
	{
		setNull(index);
		return false;
	}
}

void DoubleColumn::remove(size_t index)
{
	values.erase(values.begin() + index);
	isNULL.erase(isNULL.begin() + index);
}

void DoubleColumn::insert(const std::string& value)
{
	size_t index = getSize();
	resize(index + 1);

	if (updateIfNull(index, value))
	{
		setNull(index);
		return;
	}

	double parsed = tryParseValue(value);
	setValue(index, parsed);
}

void DoubleColumn::saveToFile(std::ofstream& ofs) const
{
	int type = static_cast<int>(ColumnType::DOUBLE);
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(int));

	saveNameAndSize(ofs);

	for (size_t i = 0; i < getSize(); i++)
	{
		ofs.write(reinterpret_cast<const char*>(&values[i]), sizeof(double));
	}

	saveNullFlags(ofs);
}

void DoubleColumn::loadFromFile(std::ifstream& ifs)
{
	loadNameAndSize(ifs);

	for (size_t i = 0; i < getSize(); i++)
	{
		ifs.read(reinterpret_cast<char*>(&values[i]), sizeof(double));
	}

	loadNullFlags(ifs);
}

void DoubleColumn::exportCell(std::ofstream& ofs, size_t index) const
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

DoubleColumn* DoubleColumn::clone() const
{
	return new DoubleColumn(*this);
}

std::string DoubleColumn::getAsString(size_t index) const
{
	if (isCellNull(index))
	{
		return "Null";
	}

	return std::to_string(values[index]);
}

double DoubleColumn::tryParseValue(const std::string& value) const
{
	return std::stod(value);
}

void DoubleColumn::setValue(size_t index, double value)
{
	values[index] = value;
	isNULL[index] = false;
}

void DoubleColumn::setNull(size_t index)
{
	values[index] = 0.0;
	isNULL[index] = true;
}

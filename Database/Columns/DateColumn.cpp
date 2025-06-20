#include "DateColumn.h"
#include "../Utils/PrintUtils.h"

DateColumn::DateColumn(const std::string& name, Table* table)
	: Column(name, table)
{
}

void DateColumn::resize(size_t newSize)
{
	size_t oldSize = getSize();
	values.resize(newSize);
	isNULL.resize(newSize);

	for (size_t i = oldSize; i < getSize(); i++)
	{
		setNull(i);
	}
}

std::string DateColumn::getType() const
{
	return "date";
}

bool DateColumn::matchingValues(size_t index, const std::string& value) const
{
	try
	{
		date::year_month_day target = tryParseValue(value);
		return values[index] == target;
	}
	catch (...)
	{
		return false;
	}
}

void DateColumn::updateValue(size_t index, const std::string& newValue)
{
	if (!updateIfNull(index, newValue))
	{
		date::year_month_day parsed = tryParseValue(newValue);
		setValue(index, parsed);
	}
}

void DateColumn::printValueAt(size_t index) const
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

void DateColumn::printValueAt(size_t index, std::ofstream& ofs) const
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

bool DateColumn::modify(const Column& source, size_t index)
{
	std::string value = source.getAsString(index);

	if (updateIfNull(index, value))
	{
		return true;
	}

	try
	{
		std::istringstream in(value);
		date::year_month_day parsed;
		in >> date::parse("%F", parsed);

		if (in.fail() || !parsed.ok())
			throw std::invalid_argument("Invalid date");

		if (parsed < date::year{ 1900 } / 1 / 1)
			throw std::invalid_argument("Date must be >= 1900-01-01");

		setValue(index, parsed);
		return true;
	}
	catch (...)
	{
		setNull(index);
		return false;
	}
}

void DateColumn::remove(size_t index)
{
	values.erase(values.begin() + index);
	isNULL.erase(isNULL.begin() + index);
}

void DateColumn::insert(const std::string& value)
{
	size_t index = getSize();
	resize(index + 1);

	if (updateIfNull(index, value))
	{
		setNull(index);
		return;
	}

	date::year_month_day parsed = tryParseValue(value);
	setValue(index, parsed);
}

void DateColumn::saveToFile(std::ofstream& ofs) const
{
	int type = static_cast<int>(ColumnType::DATE);
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(int));

	saveNameAndSize(ofs);

	for (size_t i = 0; i < getSize(); ++i)
	{
		size_t y = int(values[i].year());
		size_t m = unsigned(values[i].month());
		size_t d = unsigned(values[i].day());

		ofs.write(reinterpret_cast<const char*>(&y), sizeof(size_t));
		ofs.write(reinterpret_cast<const char*>(&m), sizeof(size_t));
		ofs.write(reinterpret_cast<const char*>(&d), sizeof(size_t));
	}

	saveNullFlags(ofs);
}

void DateColumn::loadFromFile(std::ifstream& ifs)
{
	loadNameAndSize(ifs);

	for (size_t i = 0; i < getSize(); ++i)
	{
		ifs.read(reinterpret_cast<char*>(&values[i]), sizeof(double));
	}

	loadNullFlags(ifs);
}

void DateColumn::exportCell(std::ofstream& ofs, size_t index) const
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

DateColumn* DateColumn::clone() const
{
	return new DateColumn(*this);
}

std::string DateColumn::getAsString(size_t index) const
{
	if (isNULL[index])
		return "NULL";

	return date::format("%F", values[index]);
}

const date::year_month_day& DateColumn::tryParseValue(const std::string& value) const
{
	std::istringstream in(value);
	date::year_month_day parsed;
	in >> date::parse("%F", parsed);

	if (in.fail() || !parsed.ok())
		throw std::invalid_argument("Invalid date format");

	if (parsed < date::year{ 1900 } / 1 / 1)
		throw std::invalid_argument("Date must be >= 1900-01-01");

	return parsed;
}

void DateColumn::setValue(size_t index, const date::year_month_day& value)
{
	values[index] = value;
	isNULL[index] = false;
}

void DateColumn::setNull(size_t index)
{
	values[index] = date::year_month_day{};
	isNULL[index] = true;
}

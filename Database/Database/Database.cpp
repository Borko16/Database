#include "Database.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "../Utils/ErrorUtils.h"
#include "../Utils/PrintUtils.h"


Database::Database(const std::string& name)
	: name(name)
{
}

size_t Database::getTablesCount() const
{
	return tables.size();
}

bool Database::addColumn(const std::string& table, const std::string& column, const std::string& type)
{
	if (!ensureTablesExist())
	{
		return false;
	}

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		return false;
	}

	if (tables[index].addColumn(column, type))
	{
		return true;
	}

	return false;
}

bool Database::createTable(const std::string& table)
{
	size_t index = findTableIndex(table);
	if (index != getTablesCount())
	{
		printAlreadyExists("Table");
		return false;
	}

	Table temp(table);
	tables.push_back(temp);

	printSuccess("CreateTable");
	return true;
}

void Database::describe(const std::string& table) const
{
	if (!ensureTablesExist()) return;

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		printFail("Describe");
	}

	tables[index].describe();
}

bool Database::deleteRows(const std::string& table, const std::string& column, const std::string& value)
{
	if (!ensureTablesExist())
	{
		return false;
	}

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		notFound("Table");
		return false;
	}

	if (tables[index].deleteRows(column, value))
	{
		return true;
	}

	return false;
}

void Database::exportTable(const std::string& table, const std::string& filePath) const
{
	if (!ensureTablesExist()) return;

	size_t index = findTableIndex(table);

	if (index == getTablesCount())
	{
		printFail("ExportTable");
	}

	std::ofstream ofs(filePath);
	if (!ofs.is_open())
	{
		printFailedOpenFailWrite();
		return;
	}

	tables[index].exportTable(ofs);
}

bool Database::insert(const std::string& table, const std::vector<std::string>& columns)
{
	if (!ensureTablesExist()) return false;

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		notFound("Table");
		return false;
	}

	if (tables[index].insert(columns))
	{
		return true;
	}
	return false;
}

bool Database::modify(const std::string& table, const std::string& column, const std::string& type)
{
	if (!ensureTablesExist())
	{
		return false;
	}

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		notFound("Table");
		return false;
	}

	if (tables[index].modify(column, type))
	{
		return true;
	}
	return false;
}

void Database::print(const std::string& table, size_t rowsPerPage) const
{
	if (!ensureTablesExist()) return;

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		notFound("Table");
		return;
	}

	tables[index].print(rowsPerPage);
}

void Database::select(const std::string& column, const std::string& value, const std::string& table) const
{
	if (!ensureTablesExist()) return;

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		notFound("Table");
		return;
	}

	tables[index].select(column, value);
}

void Database::showTables() const
{
	if (!ensureTablesExist()) return;

	printTables();

}

bool Database::update(const std::string& table, const std::string& column, const std::string& value, const std::string& newColumn, const std::string& newValue)
{
	if (!ensureTablesExist())
	{
		return false;
	}

	size_t index = findTableIndex(table);
	if (index == getTablesCount())
	{
		return false;
	}

	if (tables[index].update(column, value, newColumn, newValue))
	{
		return true;
	}
	return false;
}

bool Database::saveToFile(const std::string& filePath) const
{
	if (!hasCorrectExtension(filePath))
	{
		invalidFailExtension();
		return false;
	}

	try
	{
		std::ofstream ofs(filePath, std::ios::binary);
		if (!ofs.is_open())
		{
			printFailedOpenFailWrite();
			return false;
		}

		size_t nameLength = name.size();
		ofs.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
		ofs.write(name.c_str(), sizeof(char) * nameLength);

		size_t tableCount = tables.size();
		ofs.write(reinterpret_cast<const char*>(&tableCount), sizeof(size_t));

		for (size_t i = 0; i < tables.size(); ++i)
		{
			tables[i].saveToFile(ofs);
		}
	}
	catch (...)
	{
		printFail("SaveToFile");
		return false;
	}

	printSuccess("SaveToFile");
	return true;
}

bool Database::loadFromFile(const std::string& filePath)
{
	if (!hasCorrectExtension(filePath))
	{
		invalidFailExtension();
		return false;
	}

	std::string newName;
	std::vector<Table> newTables;
	try
	{
		std::ifstream ifs(filePath, std::ios::binary);
		if (!ifs.is_open())
		{
			printFailedOpenFailRead();
			return false;
		}

		size_t nameLength = 0;
		ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
		newName.resize(nameLength);
		ifs.read(&newName[0], sizeof(char) * nameLength);

		size_t tableCount = 0;
		ifs.read(reinterpret_cast<char*>(&tableCount), sizeof(size_t));


		for (size_t i = 0; i < tableCount; ++i)
		{
			Table t("");
			t.loadFromFile(ifs);
			newTables.push_back(t);
		}
	}
	catch (...)
	{
		printFail("Load");
		return false;
	}

	name = newName;
	tables = newTables;

	printSuccess("LoadFromFile");
	return true;
}

const std::string& Database::getName() const
{
	return name;
}

const size_t Database::findTableIndex(const std::string& table) const
{
	for (size_t i = 0; i < getTablesCount(); i++)
	{
		if (tables[i].getName() == table)
		{
			return i;
		}
	}

	return getTablesCount();
}

bool Database::ensureTablesExist() const
{
	if (getTablesCount() == 0) {
		notFound("Table");
		return false;
	}
	return true;
}

bool Database::hasCorrectExtension(const std::string& filePath, const std::string& expectedExt) const
{
	if (filePath.size() < expectedExt.size())
	{
		return false;
	}

	return filePath.substr(filePath.size() - expectedExt.size()) == ".dbbg";
}

void Database::printTables() const
{
	printValue("Tables: ");
	for (size_t i = 0; i < tables.size(); ++i)
	{
		printValue(tables[i].getName());
		if (i != getTablesCount() - 1)
		{
			printValue(", ");
		}
	}
	printValue("\n");
}

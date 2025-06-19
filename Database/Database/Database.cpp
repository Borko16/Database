#include "Database.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "../Utils/ErrorUtils.h"

Database::Database(const std::string& name)
	: name(name)
{
}

void Database::addColumn(const std::string& table, const std::string& column, const std::string& type)
{
	if (tables.empty()) 
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			tables[i].addColumn(column, type);
			return;
		}
	}
}

void Database::createTable(const std::string& table)
{
	Table temp(table);
	tables.push_back(temp);
}

void Database::describe(const std::string& table)
{
	if (tables.empty()) 
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			tables[i].describe();
		}
	}
}

void Database::deleteRows(const std::string& table, const std::string& column, const std::string& value)
{
	if (tables.empty()) 
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			//if()
			//return tables[i].deleteRows(column, value);
		}
	}
}

void Database::exportTable(const std::string& table, const std::string& filePath)
{
	if (tables.empty()) 
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			std::ofstream ofs(filePath);
			if (!ofs.is_open())
			{
				std::cout << "Failed to open file for writing.\n";
				return;
			}

			const Table& table = tables[i];
			table.exportTable(ofs);
			return;
		}
	}

	throw std::invalid_argument("Database export table");
}

void Database::insert(const std::string& table, const std::vector<std::string>& columns)
{
	if (tables.empty()) 
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			tables[i].insert(columns);
		}
	}
}

void Database::modify(const std::string& table, const std::string& column, const std::string& type)
{
	if (tables.empty())
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			//return tables[i].modify(column, type);
		}
	}
}

void Database::print(const std::string& table, size_t rowsPerPage)
{
	if (tables.empty())
	{
		std::cout << "No tables found.\n";
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			//return tables[i].print(rowsPerPage);
		}
	}
}

void Database::select(const std::string& column, const std::string& value, const std::string& table)
{
	if (tables.empty())
	{
		std::cout << "No tables found.\n";
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			//return tables[i].select(column, value);
		}
	}
}

void Database::showTables()
{
	if (tables.empty())
	{
		notFound("Table");
		return;
	}

	std::cout << "Tables: ";
	for (size_t i = 0; i < tables.size(); ++i) {
		std::cout << tables[i].getName();
		if (i != tables.size() - 1)
			std::cout << ", ";
	}
	std::cout << "\n";
}

void Database::update(const std::string& table, const std::string& column, const std::string& value, const std::string& newColumn, const std::string& newValue)
{
	if (tables.empty())
	{
		notFound("Table");
		return;
	}

	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			//return tables[i].update(column, value, newColumn, newValue);
		}
	}
}

void Database::saveToFile(const std::string& filePath)
{
	std::ofstream ofs(filePath, std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Failed to open file for writing.\n";
		return;
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

void Database::loadFromFile(const std::string& filePath)
{
	std::ifstream ifs(filePath, std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "Failed to open file for reading.\n";
		return;
	}

	size_t nameLength = 0;
	ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
	std::string newName(nameLength, '\0');
	ifs.read(&newName[0], sizeof(char) * nameLength);
	name = newName;

	size_t tableCount = 0;
	ifs.read(reinterpret_cast<char*>(&tableCount), sizeof(size_t));

	for (size_t i = 0; i < tableCount; ++i)
	{
		Table t("");
		t.loadFromFile(ifs);
		tables.push_back(t);
	}
}

const std::string& Database::getName() const
{
	return name;
}

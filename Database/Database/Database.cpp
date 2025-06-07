#include "Database.h"

#include <stdexcept>

Database::Database(const std::string& name)
	: name(name)
{
}

void Database::addColumn(const std::string& table, const std::string& column, const std::string& type)
{
	for (size_t i = 0; i < tables.size(); i++)
	{
		if (tables[i].getName() == table)
		{
			tables[i].addColumn(column, type);
			return;
		}
	}
	
	throw std::invalid_argument("database addColumn table");
}

void Database::addTable(const std::string& table)
{
	Table temp(table);
	tables.push_back(temp);
}

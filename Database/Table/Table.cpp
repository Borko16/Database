#include "Table.h"
#include <stdexcept>
#include "../Columns/Column.h"
#include "../Columns/IntColumn.h"
#include "../Columns/StringColumn.h"
#include "../Columns/DoubleColumn.h"
#include "../Columns/DateColumn.h"
#include "../Utils/ErrorUtils.h"
#include "../Utils/PrintUtils.h"
#include <fstream>

Table::Table(const std::string& name)
	: name(name)
{
}

Table::~Table()
{
	for (size_t i = 0; i < columns.size(); ++i)
	{
		delete columns[i];
	}
}

size_t Table::getColumnSize() const
{
	return (columns.size() ? columns[0]->getSize() : 0);
}

size_t Table::getRowSize() const
{
	return columns.size();
}

void Table::addColumn(const std::string& column, const std::string& type)
{
	Column* newColumn = createColumn(column, type);

	if (!newColumn)
	{
		unknownColumnType();
		return;
	}

	if (getRowSize() > 1)
	{
		newColumn->resize(getColumnSize());
	}
	columns.push_back(newColumn);

	printSuccess("addColumn");
}

void Table::deleteRows(const std::string& column, const std::string& value)
{
	size_t index = findColumnIndex(column);

	if (index == getRowSize())
	{
		notFound("Column");
		return;
	}

	int removedCount = 0;
	for (int i = getColumnSize() - 1; i >= 0; i--)
	{
		if (columns[index]->matchingValues(i, value))
		{
			removeRow(index);
			removedCount++;
		}
	}

	printDeletedRows(removedCount);
}

void Table::describe() const
{
	if (getRowSize() == 0)
	{
		notFound("Column");
		return;
	}

	for (size_t i = 0; i < getRowSize(); ++i)
	{
		printColumnNameAndType(columns[i]->getName(), columns[i]->getType());
	}
}

void Table::exportTable(std::ofstream& ofs) const
{
	if (getRowSize() == 0)
	{
		notFound("Column");
		return;
	}

	printColumnNames(ofs);
	for (size_t i = 0; i < getRowSize(); ++i)
	{
		printRow(i,ofs);
	}

	printSuccess("ExportTable");
}

void Table::insert(const std::vector<std::string>& values)
{
	if (values.size() != getRowSize())
	{
		invalidValueCount();
		return;
	}

	size_t i;
	try
	{
		for (i = 0; i < getRowSize(); i++)
		{
			columns[i]->insert(values[i]);
		}
	}
	catch (...)
	{
		for (size_t j = 0; j < i; ++j)
		{
			columns[j]->resize(getColumnSize() - 1);
		}
		printFail("Insert");
	}

	printSuccess("Insert");
}

void Table::modify(const std::string& column, const std::string& type)
{
	if (getRowSize() == 0)
	{
		notFound("Column");
		return;
	}

	size_t index = findColumnIndex(column);
	if (index == getRowSize())
	{
		notFound("Column");
	}

	Column* oldCol = columns[index];
	Column* newCol = nullptr;
	try
	{
		newCol = createColumn(column, type);
		newCol->resize(oldCol->getSize());

		size_t success = 0;
		size_t fail = 0;
		std::vector<size_t> failed;
		for (size_t i = 0; i < oldCol->getSize(); ++i)
		{
			if (newCol->modify(*oldCol, i))
			{
				success++;
			}
			else
			{
				fail++;
				failed.push_back(i);
			}
		}

		delete oldCol;
		columns[index] = newCol;

		printModified(success);
		printFailed(fail);
		printFailedCell(failed);
	}
	catch (...)
	{
		printFail("Modify");
		delete newCol;
	}
}

void Table::print(size_t rowsPerPage) const
{
	if (rowsPerPage == 0)
	{
		printColumnNames();
		for (size_t i = 0; i < getColumnSize(); ++i)
		{
			printRow(i);
		}
	}
	else
	{
		if (getRowSize() == 0)
		{
			printValue("Empty\n");
			return;
		}

		size_t currentPage = 0;
		size_t totalPages = (getColumnSize() + rowsPerPage - 1) / rowsPerPage;
		std::string command;

		while (command != "exit")
		{
			size_t start = currentPage * rowsPerPage;
			size_t end = (start + rowsPerPage < getColumnSize()) ? start + rowsPerPage : getColumnSize();

			printColumnNames();
			for (size_t i = start; i < end; ++i)
			{
				printRow(i);
			}
			printPage(currentPage);
			printValue("Enter command: ");
			std::getline(std::cin, command);
			printPaginationLogic(currentPage, totalPages, command);
		}
	}
}

void Table::select(const std::string& column, const std::string& value) const
{
	if (getRowSize() == 0)
	{
		notFound("Column");
	}

	size_t index = findColumnIndex(column);
	for (size_t i = 0; i < getColumnSize(); i++)
	{
		if (columns[index]->matchingValues(i, value))
		{
			printRow(i);
		}
	}
	printValue("\n");
}

void Table::printRow(size_t index) const
{
	for (size_t j = 0; j < getRowSize(); ++j)
	{
		columns[j]->printValueAt(index);
		printValue("\t");
	}
	printValue("\n");
}

void Table::printRow(size_t index, std::ofstream& ofs) const
{
	for (size_t j = 0; j < getRowSize(); ++j)
	{
		columns[j]->printValueAt(index, ofs);
		printValue("\t", ofs);
	}
	printValue("\n", ofs);
}

void Table::printFailedCell(const std::vector<size_t>& failed) const
{
	printValue("Failed indices: ");
	for (size_t i = 0; i < failed.size(); i++)
	{
		printValue((int)failed[i]);
		if (i < failed.size() - 1)
		{
			printValue(", ");
		}
	}
	printValue("\n");
}

void Table::printPaginationLogic(size_t& currentPage, size_t totalPages, const std::string& command) const
{
	if (command == "start") currentPage = 0;
	else if (command == "end") currentPage = totalPages - 1;
	else if (command == "next")
	{
		if (currentPage + 1 < totalPages) ++currentPage;
		else printValue("This is the last page.\n");

	}
	else if (command == "previous")
	{
		if (currentPage > 0) --currentPage;
		else printValue("This is the first page.\n");
	}
	else if (command != "exit")
	{
		printValue("Unknown command. Valid commands are:\n");
		printValue("  - start\n");
		printValue("  - end\n");
		printValue("  - next\n");
		printValue("  - previous\n");
		printValue("  - exit\n");
	}
}

void Table::printColumnNames() const
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		printValue(columns[i]->getName());
		printValue("\t");
	}
	printValue("\n");
}

void Table::printColumnNames(std::ofstream& ofs) const
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		printValue(columns[i]->getName(), ofs);
		printValue("\t", ofs);
	}
	printValue("\n", ofs);
}

void Table::update(const std::string& column, const std::string& value, const std::string& targetColumn, const std::string& newValue)
{
	if (getRowSize() == 0)
	{
		notFound("Column");
	}

	size_t index = findColumnIndex(column);
	size_t targetIndex = findColumnIndex(targetColumn);
	for (size_t i = 0; i < getColumnSize(); i++)
	{
		if (columns[index]->matchingValues(i, value)) // при изключение не трябва да се променя нищо
		{
			columns[targetIndex]->updateValue(i, newValue);
		}
	}

	printSuccess("Update");
}

void Table::saveToFile(std::ofstream& ofs) const
{
	size_t nameLen = name.size();
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
	ofs.write(name.c_str(), nameLen);

	size_t columnCount = columns.size();
	ofs.write(reinterpret_cast<const char*>(&columnCount), sizeof(size_t));

	for (size_t i = 0; i < columns.size(); ++i)
	{
		columns[i]->saveToFile(ofs);
	}

	printSuccess("SaveToFile");
}

void Table::loadFromFile(std::ifstream& ifs)
{
	size_t nameLen = 0;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(size_t));

	std::string tempName(nameLen, '\0');
	ifs.read(&tempName[0], nameLen);
	name = tempName;

	size_t columnCount = 0;
	ifs.read(reinterpret_cast<char*>(&columnCount), sizeof(size_t));

	for (size_t i = 0; i < columnCount; ++i)
	{
		int typeInt = -1;
		ifs.read(reinterpret_cast<char*>(&typeInt), sizeof(int));

		Column* column = nullptr;

		switch (static_cast<ColumnType>(typeInt))
		{
		case ColumnType::INT:
			column = new IntColumn("", this);
			break;
		case ColumnType::DOUBLE:
			column = new DoubleColumn("", this);
			break;
		case ColumnType::STRING:
			column = new StringColumn("", this);
			break;
		case ColumnType::DATE:
			column = new DateColumn("", this);
			break;
		default:
			unknownColumnType();
		}

		column->loadFromFile(ifs); // колоната си зарежда името, стойностите и NULL-ите
		columns.push_back(column);
	}

	printSuccess("LoadFromFile");
}

const std::string& Table::getName() const
{
	return name;
}

Column* Table::createColumn(const std::string& name, const std::string& type)
{
	if (type == "int")
	{
		return new IntColumn(name, this);
	}
	else if (type == "double")
	{
		return new DoubleColumn(name, this);
	}
	else if (type == "date")
	{
		return new DateColumn(name, this);
	}
	else if (type == "string")
	{
		return new StringColumn(name, this);
	}
	else
	{
		return nullptr;
	}
}

size_t Table::findColumnIndex(const std::string& column) const
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		if (columns[i]->getName() == column)
		{
			return i;
		}
	}

	return getRowSize();
}

void Table::removeRow(size_t index)
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		columns[i]->remove(index);
	}
}

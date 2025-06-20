#include "Table.h"
#include "../Columns/IntColumn.h"
#include "../Columns/StringColumn.h"
#include "../Columns/DoubleColumn.h"
#include "../Columns/DateColumn.h"
#include "../Utils/ErrorUtils.h"
#include "../Utils/PrintUtils.h"
#include "../Utils/StringUtils.h"

Table::Table(const std::string& name)
	: name(name)
{
}

Table::Table(const Table& other)
	: name(other.name)
{
	columns.reserve(other.getColumnsCount());
	for (size_t i = 0; i < getColumnsCount(); i++)
	{
		columns.push_back(other.columns[i]->clone());
	}
}

Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		std::vector<Column*> newColumns;
		newColumns.reserve(other.getColumnsCount());

		try
		{
			for (size_t i = 0; i < other.getColumnsCount(); i++)
			{
				newColumns.push_back(other.columns[i]->clone());
			}
		}
		catch (...)
		{
			for (size_t j = 0; j < newColumns.size(); j++)
			{
				delete newColumns[j];
			}
			throw;
		}

		for (size_t i = 0; i < columns.size(); i++)
		{
			delete columns[i];
		}

		columns = newColumns;
		name = other.name;
	}

	return *this;
}

Table::~Table()
{
	for (size_t i = 0; i < columns.size(); i++)
	{
		delete columns[i];
	}
}

size_t Table::getColumnsCount() const
{
	return columns.size();
}

size_t Table::getRowSize() const
{
	return (columns.size() ? columns[0]->getSize() : 0);
}

bool Table::addColumn(const std::string& column, const std::string& type)
{
	size_t index = findColumnIndex(column);
	if (index != getColumnsCount())
	{
		printMessage("Column with this name already exists.\n");
		return false;
	}

	Column* newColumn = createColumn(column, type);

	if (!newColumn)
	{
		unknownColumnType();
		return false;
	}

	if (getRowSize() > 1)
	{
		newColumn->resize(getColumnsCount());
	}
	columns.push_back(newColumn);

	printSuccess("addColumn");
	return true;
}

bool Table::deleteRows(const std::string& column, const std::string& value)
{
	if (!ensureColumnsExist())
	{
		return false;
	}

	size_t index = findColumnIndex(column);
	if (index == getRowSize())
	{
		notFound("Column");
		return false;
	}

	int removedCount = 0;
	for (int i = getColumnsCount() - 1; i >= 0; i--)
	{
		if (columns[index]->strictMatch(i, value))
		{
			removeRow(i);
			removedCount++;
		}
	}

	printDeletedRows(removedCount);
	return true;
}

void Table::describe() const
{
	if (!ensureColumnsExist()) return;

	for (size_t i = 0; i < getRowSize(); i++)
	{
		printColumnNameAndType(columns[i]->getName(), columns[i]->getType());
	}
}

void Table::exportTable(std::ofstream& ofs) const
{
	if (!ensureColumnsExist()) return;

	printColumnNames(ofs);
	for (size_t i = 0; i < getRowSize(); i++)
	{
		printRow(i, ofs);
	}

	printSuccess("ExportTable");
}

bool Table::insert(const std::vector<std::string>& values)
{
	if (values.size() != getRowSize())
	{
		invalidValueCount();
		return false;
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
		for (size_t j = 0; j < i; j++)
		{
			columns[j]->resize(getColumnsCount() - 1);
		}
		printFail("Insert");
		return false;
	}

	printSuccess("Insert");
	return true;
}

bool Table::modify(const std::string& column, const std::string& type)
{
	if (!ensureColumnsExist())
	{
		return false;
	}
	size_t index = findColumnIndex(column);
	if (index == getRowSize())
	{
		notFound("Column");
		return false;
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
		for (size_t i = 0; i < oldCol->getSize(); i++)
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
		return true;
	}
	catch (...)
	{
		printFail("Modify");
		delete newCol;
		return false;
	}
}

void Table::print(size_t rowsPerPage) const
{
	if (rowsPerPage == 0)
	{
		printColumnNames();
		for (size_t i = 0; i < getColumnsCount(); i++)
		{
			printRow(i);
		}
	}
	else
	{
		if (getRowSize() == 0)
		{
			printMessage("Empty\n");
			return;
		}

		size_t currentPage = 0;
		size_t totalPages = (getColumnsCount() + rowsPerPage - 1) / rowsPerPage;
		std::string command;

		while (command != "exit")
		{
			size_t start = currentPage * rowsPerPage;
			size_t end = (start + rowsPerPage < getColumnsCount()) ? start + rowsPerPage : getColumnsCount();

			printColumnNames();
			for (size_t i = start; i < end; i++)
			{
				printRow(i);
			}
			printPage(currentPage);
			printMessage("Enter command: ");
			std::getline(std::cin, command);
			printPaginationLogic(currentPage, totalPages, command);
		}
	}
}

void Table::select(const std::string& column, const std::string& value) const
{
	if (!ensureColumnsExist()) return;

	size_t index = findColumnIndex(column);
	if (index == getRowSize())
	{
		notFound("Column");
		return;
	}

	for (size_t i = 0; i < getColumnsCount(); i++)
	{
		if (columns[index]->matchingValues(i, value))
		{
			printRow(i);
		}
	}
	printMessage("\n");
}

void Table::printRow(size_t index) const
{
	for (size_t j = 0; j < getRowSize(); j++)
	{
		columns[j]->printValueAt(index);
		printMessage("\t");
	}
	printMessage("\n");
}

void Table::printRow(size_t index, std::ofstream& ofs) const
{
	for (size_t j = 0; j < getRowSize(); j++)
	{
		columns[j]->printValueAt(index, ofs);
		printMessage("\t", ofs);
	}
	printMessage("\n", ofs);
}

void Table::printFailedCell(const std::vector<size_t>& failed) const
{
	printMessage("Failed indices: ");
	for (size_t i = 0; i < failed.size(); i++)
	{
		printNumber(failed[i]);
		if (i < failed.size() - 1)
		{
			printMessage(", ");
		}
	}
	printMessage("\n");
}

void Table::printPaginationLogic(size_t& currentPage, size_t totalPages, const std::string& command) const
{
	if (command == "start") currentPage = 0;
	else if (command == "end") currentPage = totalPages - 1;
	else if (command == "next")
	{
		if (currentPage + 1 < totalPages) ++currentPage;
		else printMessage("This is the last page.\n");

	}
	else if (command == "previous")
	{
		if (currentPage > 0) --currentPage;
		else printMessage("This is the first page.\n");
	}
	else if (command != "exit")
	{
		printMessage("Unknown command. Valid commands are:\n");
		printMessage("  - start\n");
		printMessage("  - end\n");
		printMessage("  - next\n");
		printMessage("  - previous\n");
		printMessage("  - exit\n");
	}
}

void Table::printColumnNames() const
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		printMessage(columns[i]->getName());
		printMessage("\t");
	}
	printMessage("\n");
}

void Table::printColumnNames(std::ofstream& ofs) const
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		printMessage(columns[i]->getName(), ofs);
		printMessage("\t", ofs);
	}
	printMessage("\n", ofs);
}

bool Table::update(const std::string& column, const std::string& value, const std::string& targetColumn, const std::string& newValue)
{
	if (!ensureColumnsExist())
	{
		return false;
	}

	size_t index = findColumnIndex(column);
	size_t targetIndex = findColumnIndex(targetColumn);
	if (index == getRowSize() || targetIndex == getRowSize())
	{
		notFound("Column");
		return false;
	}

	Column* clone = nullptr;
	try
	{
		clone = columns[targetIndex]->clone();

		for (size_t i = 0; i < getColumnsCount(); i++)
		{
			if (columns[index]->matchingValues(i, value))
			{
				clone->updateValue(i, newValue);
			}
		}

		delete columns[targetIndex];
		columns[targetIndex] = clone;
	}
	catch (...)
	{
		delete clone;
		printFail("Update");
		return false;
	}

	printSuccess("Update");
	return true;
}

void Table::saveToFile(std::ofstream& ofs) const
{
	size_t nameLen = name.size();
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
	ofs.write(name.c_str(), nameLen);

	size_t columnCount = columns.size();
	ofs.write(reinterpret_cast<const char*>(&columnCount), sizeof(size_t));

	for (size_t i = 0; i < columns.size(); i++)
	{
		columns[i]->saveToFile(ofs);
	}
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

	for (size_t i = 0; i < columnCount; i++)
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

		try
		{
			column->loadFromFile(ifs);
			columns.push_back(column);
		}
		catch (...)
		{
			delete column;
			throw;
		}

	}
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
		if (compareInsensitive(columns[i]->getName(), column))
		{
			return i;
		}
	}

	return getRowSize();
}

bool Table::ensureColumnsExist() const
{
	if (getRowSize() == 0) {
		notFound("Column");
		return false;
	}
	return true;
}

void Table::removeRow(size_t index)
{
	for (size_t i = 0; i < getRowSize(); i++)
	{
		columns[i]->remove(index);
	}
}

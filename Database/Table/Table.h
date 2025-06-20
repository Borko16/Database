#pragma once
#include <string>
#include <vector>
class Column;

class Table
{
public:
	Table(const std::string& name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();
	size_t getColumnsCount() const;
	size_t getRowSize() const;
	bool addColumn(const std::string& column, const std::string& type);
	bool deleteRows(const std::string& column, const std::string& value);
	void describe() const;
	void exportTable(std::ofstream& ofs) const;
	bool insert(const std::vector<std::string>& values);
	bool modify(const std::string& column, const std::string& type);
	void print(size_t rowsPerPage = 0) const;
	void select(const std::string& column, const std::string& value) const;
	bool update(const std::string& column, const std::string& value, const std::string& targetColumn, const std::string& newValue);
	void saveToFile(std::ofstream& ofs) const;
	void loadFromFile(std::ifstream& ifs);
	const std::string& getName() const;
private:
	void printRow(size_t index) const;
	void printRow(size_t index, std::ofstream& ofs) const;
	void printColumnNames() const;
	void printColumnNames(std::ofstream& ofs) const;
	void printFailedCell(const std::vector<size_t>& failed) const;
	void printPaginationLogic(size_t& currentPage, size_t totalPages, const std::string& command) const;
	Column* createColumn(const std::string& type, const std::string& name);
	size_t findColumnIndex(const std::string& column) const;
	bool ensureColumnsExist() const;
	void removeRow(size_t index);
	std::vector<Column*> columns;
	std::string name;
};
#pragma once
#include <string>
#include <vector>
#include "../Table/Table.h"

enum class ColumnType : int
{
	INT = 0,
	DOUBLE,
	STRING,
	DATE
};

class Column
{
public:
	Column(const std::string& name, Table* table) : name(name), table(table) {}
	virtual ~Column() = default;

	const std::string& getName() const { return name; }
	virtual size_t getSize() const;
	virtual std::string getType() const = 0;
	virtual void resize(size_t newSize) = 0;
	virtual bool matchingValues(size_t index, const std::string& value) const = 0;
	virtual void updateValue(size_t index, const std::string& newValue) = 0;
	virtual void printValueAt(size_t index) const = 0;
	virtual void printValueAt(size_t index, std::ofstream& ofs) const = 0;
	virtual bool modify(const Column& source, size_t index) = 0;
	virtual void remove(size_t index) = 0;
	virtual void insert(const std::string& value) = 0;
	virtual void saveToFile(std::ofstream& ofs) const = 0;
	virtual void loadFromFile(std::ifstream& ifs) = 0;
	virtual void exportCell(std::ofstream& ofs, size_t index) const = 0;
	virtual std::string getAsString(size_t index) const = 0;

protected:
	void saveNameAndSize(std::ostream& ofs) const;
	void saveNullFlags(std::ostream& ofs) const;
	void loadNameAndSize(std::istream& ifs);
	void loadNullFlags(std::istream& ifs);
	virtual void setNull(size_t index) = 0;
	bool isStringNull(const std::string& str) const;
	bool updateIfNull(size_t index, const std::string& newValue);
	bool isCellNull(size_t index) const;
	std::string name;
	std::vector<bool> isNULL;
	Table* table;
};
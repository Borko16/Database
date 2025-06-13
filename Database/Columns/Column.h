#pragma once
#include <string>
#include <vector>
#include "../Table/Table.h"

class Column
{
public:
	Column(const std::string& name, Table* table) : name(name), table(table) {}
	virtual ~Column() = default;

	const std::string& getName() const { return name; }
	virtual void resize(size_t newSize) = 0;
	virtual size_t getSize() const = 0;

protected:
	virtual void setNull(size_t index) = 0;
	std::string name;
	std::vector<bool> isNULL;
	Table* table;
};
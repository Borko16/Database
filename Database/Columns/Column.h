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
	//void setName(const std::string& newName);

	//virtual void fromString(const std::string& value) = 0;
	//virtual void  insertNull() = 0;
	//virtual std::string toString(size_t index) const = 0;
	//virtual void remove(size_t index) = 0;
	//virtual size_t size() const = 0; // не съм много сигурен че ми трябва
	//virtual std::string getTypeName() const = 0;
	//virtual Column* clone() const = 0;

protected:
	virtual void setNull(size_t index) = 0;
	std::string name;
	std::vector<bool> isNULL;
	Table* table;
};
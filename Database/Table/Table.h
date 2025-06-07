#pragma once
#include <string>
#include <vector>
class Column;

class Table
{
public:
	Table(const std::string& name);
	void addColumn(const std::string& column, const std::string& type);
	//void resize(unsigned newSize);
	const std::string& getName() const;
private:
	std::vector<Column*> columns;
	std::string name;
};
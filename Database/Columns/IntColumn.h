#pragma once
#include <vector>
#include "Column.h"

class IntColumn : public Column
{
public:
	IntColumn(std::string name, Table* table) : Column(name, table) {}
	void resize(size_t newSize) override;
	size_t getSize() const override;

private:
	void setNull(size_t index) override;

	std::vector<int> values;
	
};
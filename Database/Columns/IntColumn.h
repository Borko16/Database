#pragma once
#include <vector>
#include "Column.h"

class IntColumn : public Column
{
public:
	IntColumn(std::string name, Table* table) : Column(name, table) {}
	void resize(size_t newSize) override;
	size_t getSize() const override;
	//void fromString(const std::string& value) override;
	//void  insertNull() override;
	//std::string toString(size_t index) const override;
	//void remove(size_t index) override;
	//size_t size() const override;
	//std::string getTypeName() const override;
	//Column* clone() const override;
	//~IntColumn() override;

private:
	void setNull(size_t index) override;

	std::vector<int> values;
	
};
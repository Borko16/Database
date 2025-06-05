#pragma once
#include <vector>
#include <string>
#include "Column.h"

class StringColumn : public Column
{
public:
	void fromString(const std::string& value) override;
	void  insertNull() override;
	std::string toString(size_t index) const override;
	void remove(size_t index) override;
	size_t size() const override;
	std::string getTypeName() const override;
	Column* clone() const override;
	~StringColumn() override;

private:
	void setNull() override;

	std::vector<std::string> values;
	std::vector<bool> isNULL;
};
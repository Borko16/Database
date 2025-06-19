#pragma once
#include <vector>
#include "Column.h"

class IntColumn : public Column
{
public:
	IntColumn(const std::string& name, Table* table);
	void resize(size_t newSize) override;
	std::string getType() const override;
	bool matchingValues(size_t index, const std::string& value) const override;
	void updateValue(size_t index, const std::string& newValue) override;
	void printValueAt(size_t index) const override;
	void printValueAt(size_t index, std::ofstream& ofs) const override;
	bool modify(const Column& source, size_t index) override;
	void remove(size_t index) override;
	void insert(const std::string& value) override;
	void saveToFile(std::ofstream& ofs) const override;
	void loadFromFile(std::ifstream& ifs) override;
	void exportCell(std::ofstream& ofs, size_t index) const override;
private:
	std::string getAsString(size_t index) const;
	int tryParseValue(const std::string& value) const;
	void setValue(size_t index, int value);
	void setNull(size_t index) override;

	std::vector<int> values;
	
};
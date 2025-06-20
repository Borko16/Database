#pragma warning
#include "../Utils/DateUtils.h"
#include <vector>
#include "Column.h"

class DateColumn : public Column
{
public:
	DateColumn(const std::string& name, Table* table);
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
	DateColumn* clone() const override;
private:
	std::string getAsString(size_t index) const;
	const date::year_month_day& tryParseValue(const std::string& value) const;
	void setValue(size_t index, const date::year_month_day& value);
	void setNull(size_t index) override;
	std::vector<date::year_month_day> values;
};
//#pragma once
//#include <vector>
//#include "Column.h"
//
//class DoubleColumn : public Column
//{
//public:
//	void fromString(const std::string& value) override;
//	void  insertNull() override;
//	std::string toString(size_t index) const override;
//	void remove(size_t index) override;
//	size_t size() const override;
//	std::string getTypeName() const override;
//	Column* clone() const override;
//	~DoubleColumn() override;
//
//private:
//	void setNull() override;
//
//	std::vector<double> values;
//	std::vector<bool> isNULL;
//};
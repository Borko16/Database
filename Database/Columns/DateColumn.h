//#pragma once
//#include <vector>
//#include "Column.h"
//
//
//class Date
//{
//public:
//	void fromString(const std::string& value);
//	std::string toString() const;
//
//	int getDay() const;
//	int getMonth() const;
//	int getYear() const;
//private:
//
//	int day;
//	int month;
//	int year;
//};
//
//class DateColumn : public Column
//{
//public:
//	void fromString(const std::string& value) override;
//	void  insertNull() override;
//	std::string toString(size_t index) const override; // rowIndex за да вземем точното поле от нашата колона
//	void remove(size_t index) override;
//	size_t size() const override;
//	std::string getTypeName() const override;
//	Column* clone() const override;
//	~DateColumn() override;
//
//private:
//	void setNull() override;
//
//	std::vector<Date> values;
//	std::vector<bool> isNULL;
//};
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DateUtils.h"

inline void printNull(std::ostream& os = std::cout)
{
	os << "NULL";
}

inline void printValue(int value, std::ostream& os = std::cout)
{
	os << value;
}

inline void printValue(double value, std::ostream& os = std::cout)
{
	os << value;
}

inline void printValue(const std::string& value, std::ostream& os = std::cout)
{
	os << "\"" << value << "\"";
}

inline void printValue(const date::year_month_day& value, std::ostream& os = std::cout)
{
	os << date::format("%F", value);
}

inline void printDeletedRows(double count, std::ostream& os = std::cout)
{
	os << "Deleted rows" << count << "\n";
}

inline void printColumnNameAndType(const std::string& column, const std::string& type, std::ostream& os = std::cout)
{
	os << column << " - " << type << "\n";
}

inline void printSuccess(const std::string& commandName, std::ostream& os = std::cout)
{
	os << commandName << " completed successfully\n";
}

inline void printFail(const std::string& commandName, std::ostream& os = std::cout)
{
	os << commandName << " failed\n";
}

inline void printModified(int count, std::ostream& os = std::cout)
{
	os << "Successfully converted: " << count << "\n";
}

inline void printFailed(int count, std::ostream& os = std::cout)
{
	os << "Failed to convert : " << count << "\n";
}

inline void printPage(size_t page, std::ostream& os = std::cout)
{
	os << "[Page " << (page + 1) << "]\n";
}
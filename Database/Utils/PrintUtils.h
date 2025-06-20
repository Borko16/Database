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
	os << "Deleted rows " << count << "\n";
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

inline void printClosedDatabase(const std::string& database, std::ostream& os = std::cout)
{
	os << database << " was closed\n";
}

inline void printUnsavedChanges(std::ostream& os = std::cout)
{
	os << "You have unsaved changes. Do you want to save them? (yes/no): ";
}

inline void printCreatedDB(const std::string& database, std::ostream& os = std::cout)
{
	os << database << " was successfully created\n";
}

inline void printDBAlreadyOpen(std::ostream& os = std::cout)
{
	os << "You already have a database. You can't have a two or more at the same time\n";
}

inline void printFailedOpenFailWrite(std::ostream& os = std::cout)
{
	os << "Failed to open file for writing.\n";
}

inline void printFailedOpenFailRead(std::ostream& os = std::cout)
{
	os << "Failed to open file for read.\n";
}

inline void invalidFailExtension(std::ostream& os = std::cout)
{
	os << "Invalid file extension. Expected .dbbg\n";
}

inline void printAlreadyExists(const std::string& type, std::ostream& os = std::cout)
{
	os << type << " with this name already exists.\n";
}
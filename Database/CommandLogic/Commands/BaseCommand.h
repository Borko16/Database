#pragma once
#include <string>
#include <vector>
class Database;


class BaseCommand
{
protected:
	Database* database;
	size_t argsNeeded = 0;
	std::vector<std::string> args;

public:
	BaseCommand(Database* database, const std::vector<std::string>& args, size_t argsNeeded);
	virtual void execute() = 0;
	virtual ~BaseCommand() = default;

	void setArguments(const std::vector<std::string>& args, size_t argsNeeded);
};
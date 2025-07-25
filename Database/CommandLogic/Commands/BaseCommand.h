#pragma once
#include "../../Database/Database.h"
#include "../../Utils/PrintUtils.h"

class BaseCommand
{
public:
	BaseCommand(Database*& database, const std::vector<std::string>& args, size_t argsNeeded);
	virtual void execute() = 0;
	virtual ~BaseCommand() = default;
	void setArguments(const std::vector<std::string>& args, size_t argsNeeded);

protected:
	bool validateDatabase() const;
	Database*& database;
	size_t argsNeeded = 0;
	std::vector<std::string> args;
};
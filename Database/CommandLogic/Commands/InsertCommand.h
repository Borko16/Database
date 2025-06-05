#pragma once
#include "BaseCommand.h"

class InsertCommand : public BaseCommand
{
public:
	InsertCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
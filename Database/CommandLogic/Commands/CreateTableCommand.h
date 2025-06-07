#pragma once
#include "BaseCommand.h"

class CreateTableCommand : public BaseCommand
{
public:
	CreateTableCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};


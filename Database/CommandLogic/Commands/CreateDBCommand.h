#pragma once
#include "BaseCommand.h"

class CreateDBCommand : public BaseCommand
{
public:
	CreateDBCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};
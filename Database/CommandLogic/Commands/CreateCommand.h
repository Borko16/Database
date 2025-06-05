#pragma once
#include "BaseCommand.h"

class CreateCommand : public BaseCommand
{
public:
	CreateCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
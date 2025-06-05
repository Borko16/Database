#pragma once
#include "BaseCommand.h"

class AddColumnCommand : public BaseCommand
{
public:
	AddColumnCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};


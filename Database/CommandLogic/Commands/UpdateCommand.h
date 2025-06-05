#pragma once
#include "BaseCommand.h"

class UpdateCommand : public BaseCommand
{
public:
	UpdateCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
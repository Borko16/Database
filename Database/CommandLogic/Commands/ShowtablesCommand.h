#pragma once
#include "BaseCommand.h"

class ShowtablesCommand : public BaseCommand
{
public:
	ShowtablesCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
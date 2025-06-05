#pragma once
#include "BaseCommand.h"

class PrintCommand : public BaseCommand
{
public:
	PrintCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
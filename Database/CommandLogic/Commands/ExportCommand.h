#pragma once
#include "BaseCommand.h"

class ExportCommand : public BaseCommand
{
public:
	ExportCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
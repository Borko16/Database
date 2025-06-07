#pragma once
#include "BaseCommand.h"

class SaveAsCommand : public BaseCommand
{
public:
	SaveAsCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};
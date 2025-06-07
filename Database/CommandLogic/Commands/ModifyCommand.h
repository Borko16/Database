#pragma once
#include "BaseCommand.h"

class ModifyCommand : public BaseCommand
{
public:
	ModifyCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};
#pragma once
#include "BaseCommand.h"

class SelectCommand : public BaseCommand
{
public:
	SelectCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};
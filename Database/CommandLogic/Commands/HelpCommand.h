#pragma once
#include "BaseCommand.h"

class HelpCommand : public BaseCommand
{
public:
	HelpCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
	~HelpCommand() override = default;
};
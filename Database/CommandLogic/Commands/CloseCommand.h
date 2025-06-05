#pragma once
#include "BaseCommand.h"

class CloseCommand : public BaseCommand
{
public:
	CloseCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
	~CloseCommand() override = default;
};
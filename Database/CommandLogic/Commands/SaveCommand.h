#pragma once
#include "BaseCommand.h"

class SaveCommand : public BaseCommand
{
public:
	SaveCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
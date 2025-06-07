#pragma once
#include "BaseCommand.h"

class DeleteCommand : public BaseCommand
{
public:
	DeleteCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
};
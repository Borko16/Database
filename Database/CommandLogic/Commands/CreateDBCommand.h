#pragma once
#include "BaseCommand.h"

class CreateDBCommand : public BaseCommand
{
public:
	CreateDBCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	bool& hasUnsavedChanges;
};
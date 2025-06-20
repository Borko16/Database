#pragma once
#include "BaseCommand.h"

class InsertCommand : public BaseCommand
{
public:
	InsertCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	bool& hasUnsavedChanges;
};
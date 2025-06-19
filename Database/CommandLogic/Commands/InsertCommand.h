#pragma once
#include "BaseCommand.h"

class InsertCommand : public BaseCommand
{
private:
	bool& hasUnsavedChanges;

public:
	InsertCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;
};
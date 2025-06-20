#pragma once
#include "BaseCommand.h"

class AddColumnCommand : public BaseCommand
{
public:
	AddColumnCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	bool& hasUnsavedChanges;
};


#pragma once
#include "BaseCommand.h"

class ModifyCommand : public BaseCommand
{
public:
	ModifyCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	bool& hasUnsavedChanges;
};
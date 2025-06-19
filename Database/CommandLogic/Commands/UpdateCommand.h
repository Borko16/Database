#pragma once
#include "BaseCommand.h"

class UpdateCommand : public BaseCommand
{
private:
	bool& hasUnsavedChanges;
public:
	UpdateCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;
};
#pragma once
#include "BaseCommand.h"

class DeleteCommand : public BaseCommand
{
public:
	DeleteCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	bool& hasUnsavedChanges;
};
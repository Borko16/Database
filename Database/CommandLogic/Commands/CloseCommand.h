#pragma once
#include "BaseCommand.h"

class CloseCommand : public BaseCommand
{
private:
	const std::string& filePath;
	bool& hasUnsavedChanges;
public:
	CloseCommand(Database*& database, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;
};
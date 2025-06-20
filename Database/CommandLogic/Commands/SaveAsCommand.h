#pragma once
#include "BaseCommand.h"
class DatabaseMemento;

class SaveAsCommand : public BaseCommand
{
public:
	SaveAsCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	DatabaseMemento*& memento;
	std::string& filePath;
	bool& hasUnsavedChanges;
};
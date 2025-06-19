#pragma once
#include "BaseCommand.h"
class DatabaseMemento;

class SaveAsCommand : public BaseCommand
{
private:
	DatabaseMemento*& memento;
	std::string& filePath;
	bool& hasUnsavedChanges;

public:
	SaveAsCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;
};
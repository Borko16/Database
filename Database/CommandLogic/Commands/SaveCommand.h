#pragma once
#include "BaseCommand.h"
class DatabaseMemento;

class SaveCommand : public BaseCommand
{
public:
	SaveCommand(Database*& database,DatabaseMemento*& memento, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	DatabaseMemento*& memento;
	const std::string& filePath;
	bool& hasUnsavedChanges;
};
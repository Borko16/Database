#pragma once
#include "BaseCommand.h"
class DatabaseMemento;


class OpenCommand : public BaseCommand
{
public:
	OpenCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;

private:
	DatabaseMemento*& memento;
	std::string& filePath;
	bool& hasUnsavedChanges;
};
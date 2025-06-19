#pragma once
#include "BaseCommand.h"
class DatabaseMemento;


class OpenCommand : public BaseCommand
{
private:
	DatabaseMemento*& memento;
	std::string& filePath;
	bool& hasUnsavedChanges;
public:
	OpenCommand(Database*& database, DatabaseMemento*& memento, std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args);
	void execute() override;
};
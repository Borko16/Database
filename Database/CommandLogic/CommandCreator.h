#pragma once
#include <string>
#include <vector>
class Database;
class BaseCommand;
class DatabaseMemento;


class CommandCreator
{
public:
	BaseCommand* create(Database*& database, DatabaseMemento*& memento,
		std::string& filepath, bool& hasUnsavedChanges, const std::string& commandName, std::vector<std::string>& args) const;
};
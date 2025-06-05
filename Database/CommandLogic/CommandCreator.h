#pragma once
#include <string>
#include <vector>
class Database;
class BaseCommand;

class CommandCreator
{
public:
	BaseCommand* create(Database* database, const std::string& commandName, const std::vector<std::string>& args) const;
};
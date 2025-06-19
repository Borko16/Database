#include "BaseCommand.h"
#include <stdexcept>


BaseCommand::BaseCommand(Database*& database, const std::vector<std::string>& args, size_t argsNeeded)
	: database(database)
{
	setArguments(args, argsNeeded);
}

void BaseCommand::setArguments(const std::vector<std::string>& args, size_t argsNeeded)
{
	if (args.size() < argsNeeded)
	{
		throw std::invalid_argument("setArguments");
	}

	this->args = args;
}

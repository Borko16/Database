#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void DescribeCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string table = args[0];
	database->describe(table);
}

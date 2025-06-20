#include "InsertCommand.h"

InsertCommand::InsertCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 2), hasUnsavedChanges(hasUnsavedChanges)
{
}

void InsertCommand::execute()
{
	if (!validateDatabase()) return;
	const std::string table = args[0];
	args.erase(args.begin());

	if (database->insert(table, args))
	{
		hasUnsavedChanges = true;
	}
}
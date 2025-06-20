#include "AddColumnCommand.h"
#include "../../Database/Database.h"
#include <stdexcept>
#include "../../Utils/StringUtils.h"

AddColumnCommand::AddColumnCommand(Database*& database, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 3), hasUnsavedChanges(hasUnsavedChanges)
{
}

void AddColumnCommand::execute()
{
	if (!validateDatabase()) return;

	const std::string table = args[0];
	const std::string column = args[1];
	const std::string type = toLowerString(args[2]);

	if (database->addColumn(table, column, type))
	{
		hasUnsavedChanges = true;
	}
}

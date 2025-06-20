#include "CloseCommand.h"
#include "../../Utils/StringUtils.h"

CloseCommand::CloseCommand(Database*& database, const std::string& filePath, bool& hasUnsavedChanges, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0), filePath(filePath), hasUnsavedChanges(hasUnsavedChanges)
{
}

void CloseCommand::execute()
{
	if (!validateDatabase()) return;

	if (database && hasUnsavedChanges)
	{
		printUnsavedChanges();
		std::string input;
		std::cin >> input;

		if (toLowerString(input) == "yes")
		{
			if (database->saveToFile(filePath))
			{
				hasUnsavedChanges = false;
			}
			else
			{
				return;
			}
		}
	}

	printClosedDatabase(database->getName());
	delete database;
	database = nullptr;
}
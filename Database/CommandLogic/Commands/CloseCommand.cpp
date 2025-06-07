#include "CloseCommand.h"

CloseCommand::CloseCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{

}

void CloseCommand::execute()
{
}

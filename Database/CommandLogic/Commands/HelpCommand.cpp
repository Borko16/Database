#include "HelpCommand.h"

HelpCommand::HelpCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void HelpCommand::execute()
{
	printMessage("\nAvailable commands:\n");
	printMessage("open <file>\n");
	printMessage("create database name\n");
	printMessage("create table name\n");
	printMessage("save\n");
	printMessage("save as <file>\n");
	printMessage("close\n");
	printMessage("showtables\n");
	printMessage("describe <table>\n");
	printMessage("print <table> [<RPN>]\n");
	printMessage("export <table> <file>\n");
	printMessage("insert <table> <values...>\n");
	printMessage("delete <table> <col> <value>\n");
	printMessage("update <table> <col> <value> <newCol> <newValue>\n");
	printMessage("addcolumn <table> <col> <type>\n");
	printMessage("select <col> <value> <table>\n");
	printMessage("modify <table> <col> <type>\n");
	printMessage("exit\n");
	printMessage("help\n");
	printMessage("Note: Commands are case-insensitive. Use semicolon (;) to end each command.\n");
}

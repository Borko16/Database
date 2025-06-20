#include "HelpCommand.h"

HelpCommand::HelpCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void HelpCommand::execute()
{
	printValue("\nAvailable commands:\n");
	printValue("open <file>\n");
	printValue("create database name\n");
	printValue("create table name\n");
	printValue("save\n");
	printValue("save as <file>\n");
	printValue("close\n");
	printValue("showtables\n");
	printValue("describe <table>\n");
	printValue("print <table> [<RPN>]\n");
	printValue("export <table> <file>\n");
	printValue("insert <table> <values...>\n");
	printValue("delete <table> <col> <value>\n");
	printValue("update <table> <col> <value> <newCol> <newValue>\n");
	printValue("addcolumn <table> <col> <type>\n");
	printValue("select <col> <value> <table>\n");
	printValue("modify <table> <col> <type>\n");
	printValue("exit\n");
	printValue("help\n");
	printValue("Note: Commands are case-insensitive. Use semicolon (;) to end each command.\n");
}

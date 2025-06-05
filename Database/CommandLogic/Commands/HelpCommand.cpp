#include "HelpCommand.h"
#include <iostream>

HelpCommand::HelpCommand(Database* database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 0)
{
}

void HelpCommand::execute()
{
	std::cout << "\nAvailable commands:\n";
	std::cout << "open <file>\n";
	std::cout << "create\n";
	std::cout << "save\n";
	std::cout << "save as <file>\n";
	std::cout << "close\n";
	std::cout << "showtables\n";
	std::cout << "describe <table>\n";
	std::cout << "print <table> [<RPN>]\n";
	std::cout << "export <table> <file>\n";
	std::cout << "insert <table> <values...>\n";
	std::cout << "delete <table> <col> <value>\n";
	std::cout << "update <table> <col> <value> <newCol> <newValue>\n";
	std::cout << "addcolumn <table> <col> <type>\n";
	std::cout << "select <col> <value> <table>\n";
	std::cout << "modify <table> <col> <type>\n";
	std::cout << "exit\n";
	std::cout << "help\n";
	std::cout << "Note: Commands are case-insensitive. Use semicolon (;) to end each command.\n";
}

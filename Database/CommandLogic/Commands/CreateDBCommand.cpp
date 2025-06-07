#include "CreateDBCommand.h"
#include "../../Database/Database.h"
#include <iostream> // ��������
CreateDBCommand::CreateDBCommand(Database*& database, const std::vector<std::string>& args)
	: BaseCommand(database, args, 1)
{
}

void CreateDBCommand::execute() // � ������� ����� ���� ���� ���� � ���� �������. � �� �������� �� ���� �� ����� ������ �� ���� �������
{
	if (!database)
	{

		database = new Database(args[0]);
		std::cout << "successfully created\n";
	}
}

#pragma once
#include "BaseCommand.h"

class DescribeCommand : public BaseCommand
{
public:
	DescribeCommand(Database* database, const std::vector<std::string>& args);
	void execute() override;
};
#pragma once
#include "BaseCommand.h"

class OpenCommand : public BaseCommand
{

public:
	OpenCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
	virtual bool shouldAskToSave() const;
};
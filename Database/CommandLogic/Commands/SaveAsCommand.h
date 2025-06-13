#pragma once
#include "BaseCommand.h"

class SaveAsCommand : public BaseCommand
{
public:
	SaveAsCommand(Database*& database, const std::vector<std::string>& args);
	void execute() override;
	operator bool() const override;
	bool requiresSnapshot() const override;
	virtual bool shouldAskToSave() const;
};
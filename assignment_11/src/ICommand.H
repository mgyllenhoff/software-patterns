#ifndef ICOMMAND_H
#define ICOMMAND_H

// Command Pattern: Command
class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute() = 0;
};

#endif // ICOMMAND_H

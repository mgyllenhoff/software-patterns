#ifndef COMMAND_H
#define COMMAND_H

// Command Pattern: Command
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

#endif // COMMAND_H

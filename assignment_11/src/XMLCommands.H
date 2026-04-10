#ifndef XMLCOMMANDS_H
#define XMLCOMMANDS_H

#include "Command.H"
#include "AppContext.H"

// Command Pattern: ConcreteCommand
class ParseCommand : public Command
{
	AppContext &	ctx;
	std::string	filename;
public:
	ParseCommand(AppContext & ctx, const std::string & filename);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class DisplayCommand : public Command
{
	AppContext & ctx;
public:
	explicit DisplayCommand(AppContext & ctx);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class SerializeCommand : public Command
{
public:
	enum class Mode { PRETTY, MINIMAL };
private:
	AppContext &	ctx;
	Mode		mode;
	std::string	filename;
public:
	SerializeCommand(AppContext & ctx, Mode mode, const std::string & filename);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class AddElementCommand : public Command
{
	AppContext &	ctx;
	int		parentIndex;
	std::string	tagName;
public:
	AddElementCommand(AppContext & ctx, int parentIndex, const std::string & tagName);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class RemoveElementCommand : public Command
{
	AppContext &	ctx;
	int		index;
public:
	RemoveElementCommand(AppContext & ctx, int index);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class SetAttrCommand : public Command
{
	AppContext &	ctx;
	int		index;
	std::string	name;
	std::string	value;
public:
	SetAttrCommand(AppContext & ctx, int index,
		       const std::string & name, const std::string & value);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class RemoveAttrCommand : public Command
{
	AppContext &	ctx;
	int		index;
	std::string	name;
public:
	RemoveAttrCommand(AppContext & ctx, int index, const std::string & name);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class AddTextCommand : public Command
{
	AppContext &	ctx;
	int		index;
	std::string	text;
public:
	AddTextCommand(AppContext & ctx, int index, const std::string & text);
	void execute() override;
};

// Command Pattern: ConcreteCommand
class HelpCommand : public Command
{
public:
	void execute() override;
};

// Command Pattern: ConcreteCommand
// Prototype Pattern: Client
class CloneSubtreeCommand : public Command
{
	AppContext &	ctx;
	int		sourceIndex;
	int		targetParentIndex;
public:
	CloneSubtreeCommand(AppContext & ctx, int sourceIndex, int targetParentIndex);
	void execute() override;
};

#endif // XMLCOMMANDS_H

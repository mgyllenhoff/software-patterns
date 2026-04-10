#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include "AppContext.H"

// Command Pattern: Invoker
class CommandInterpreter
{
	AppContext &	ctx;

	bool dispatch(const std::string & line);
	static std::vector<std::string> tokenize(const std::string & line,
						  int maxTokens);
public:
	explicit CommandInterpreter(AppContext & ctx);
	void run();
};

#endif // COMMANDINTERPRETER_H

#ifndef INVOKER_H
#define INVOKER_H

#include <string>
#include <vector>
#include "AppContext.H"

// Command Pattern: Invoker
class Invoker
{
	AppContext &	ctx;

	bool dispatch(const std::string & line);
	static std::vector<std::string> tokenize(const std::string & line,
						  int maxTokens);
public:
	explicit Invoker(AppContext & ctx);
	void run();
};

#endif // INVOKER_H

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <climits>
#include "Invoker.H"
#include "XMLCommands.H"

Invoker::Invoker(AppContext & ctx) : ctx(ctx) {}

// Splits the line on whitespace into at most maxTokens tokens
std::vector<std::string> Invoker::tokenize(const std::string & line,
					    int maxTokens)
{
	std::vector<std::string> tokens;
	std::string::size_type pos = 0;
	const std::string::size_type len = line.size();

	while (pos < len)
	{
		// Skip leading whitespace
		while (pos < len && isspace((unsigned char)line[pos]))
			++pos;
		if (pos >= len) break;

		if ((int)tokens.size() == maxTokens - 1)
		{
			// Last token: capture rest of line (trimmed leading whitespace already)
			tokens.push_back(line.substr(pos));
			break;
		}

		// Find end of this token
		std::string::size_type end = pos;
		while (end < len && !isspace((unsigned char)line[end]))
			++end;

		tokens.push_back(line.substr(pos, end - pos));
		pos = end;
	}

	return tokens;
}

// Parse one line, create the matching ConcreteCommand, and call execute()
bool Invoker::dispatch(const std::string & line)
{
	std::vector<std::string> tokens = tokenize(line, INT_MAX);

	if (tokens.empty()) return true;

	const std::string & cmd = tokens[0];

	try
	{
		if (cmd == "quit" || cmd == "exit")
		{
			return false;
		}
		else if (cmd == "help")
		{
			HelpCommand().execute();
		}
		else if (cmd == "parse")
		{
			if (tokens.size() < 2)
				printf("Usage: parse <filename>\n");
			else
				ParseCommand(ctx, tokens[1]).execute();
		}
		else if (cmd == "display")
		{
			DisplayCommand(ctx).execute();
		}
		else if (cmd == "serialize")
		{
			if (tokens.size() < 3)
			{
				printf("Usage: serialize pretty|minimal <filename>\n");
			}
			else if (tokens[1] == "pretty")
			{
				SerializeCommand(ctx, SerializeCommand::Mode::PRETTY,
						 tokens[2]).execute();
			}
			else if (tokens[1] == "minimal")
			{
				SerializeCommand(ctx, SerializeCommand::Mode::MINIMAL,
						 tokens[2]).execute();
			}
			else
			{
				printf("Error: unknown serialize mode '%s'. Use 'pretty' or 'minimal'.\n",
				       tokens[1].c_str());
			}
		}
		else if (cmd == "add-element")
		{
			if (tokens.size() < 3)
				printf("Usage: add-element <index> <tag-name>\n");
			else
				AddElementCommand(ctx, std::stoi(tokens[1]), tokens[2]).execute();
		}
		else if (cmd == "remove-element")
		{
			if (tokens.size() < 2)
				printf("Usage: remove-element <index>\n");
			else
				RemoveElementCommand(ctx, std::stoi(tokens[1])).execute();
		}
		else if (cmd == "set-attr")
		{
			if (tokens.size() < 4)
				printf("Usage: set-attr <index> <name> <value>\n");
			else
				SetAttrCommand(ctx, std::stoi(tokens[1]),
					       tokens[2], tokens[3]).execute();
		}
		else if (cmd == "remove-attr")
		{
			if (tokens.size() < 3)
				printf("Usage: remove-attr <index> <name>\n");
			else
				RemoveAttrCommand(ctx, std::stoi(tokens[1]), tokens[2]).execute();
		}
		else if (cmd == "add-text")
		{
			// Re-tokenize with limit=3 so text after the index is one token
			std::vector<std::string> t3 = tokenize(line, 3);
			if (t3.size() < 3)
				printf("Usage: add-text <index> <text...>\n");
			else
				AddTextCommand(ctx, std::stoi(t3[1]), t3[2]).execute();
		}
		else if (cmd == "clone-subtree")
		{
			if (tokens.size() < 3)
				printf("Usage: clone-subtree <source-index> <parent-index>\n");
			else
				CloneSubtreeCommand(ctx, std::stoi(tokens[1]),
						    std::stoi(tokens[2])).execute();
		}
		else
		{
			printf("Unknown command '%s'. Type 'help' for a list of commands.\n",
			       cmd.c_str());
		}
	}
	catch (const std::invalid_argument &)
	{
		printf("Error: expected a numeric node index.\n");
	}
	catch (const std::out_of_range &)
	{
		printf("Error: node index out of range.\n");
	}

	return true;
}

// Blocks until "quit" is entered
void Invoker::run()
{
	std::string line;
	printf("> ");
	while (std::getline(std::cin, line))
	{
		if (!dispatch(line)) break;
		printf("> ");
	}
}

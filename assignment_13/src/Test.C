// Facade Pattern: Client
// The client interacts only with XMLFacade and has no direct knowledge
// of any subsystem class (DOM, tokenizer, serializer, validator, interpreter).

#include <stdio.h>
#include <string>
#include <vector>
#include "XMLFacade.H"

void printUsage(void)
{
	printf("Usage:\n");
	printf("\tTest t [file] ...\n");
	printf("\tTest s [file1] [file2]\n");
	printf("\tTest v [file]\n");
	printf("\tTest i [xmlfile]             (Builder + Interpreter demo)\n");
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(0);
	}

	XMLFacade facade;

	switch(argv[1][0])
	{
	case 'T':
	case 't':
	{
		std::vector<std::string> files;
		for (int i = 2; i < argc; i++)
			files.push_back(argv[i]);
		facade.tokenize(files);
		break;
	}
	case 'S':
	case 's':
		if (argc < 4) { printUsage(); exit(0); }
		facade.serialize(argv[2], argv[3]);
		break;
	case 'V':
	case 'v':
		facade.validate(argv[2]);
		break;
	case 'I':
	case 'i':
		facade.interpret(argv[2]);
		break;
	}
}

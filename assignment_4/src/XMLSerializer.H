#pragma once

#include <string>
#include <fstream>
#include <ios>

#include "Node.H"

class XMLSerializer
{
protected:
	std::fstream		file;

	// Hook methods — variant steps (pure virtual)
	virtual void		writeDeclarationSuffix() = 0;		// "\n" vs nothing after declaration
	virtual void		writeBeforeOpenTag() = 0;			// indentation vs nothing
	virtual void		writeAfterAttributes(int attrCount) = 0;	// trailing " " vs nothing
	virtual void		writeEmptyElementClose() = 0;		// "/>\n" vs "/>"
	virtual void		writeAfterOpenBracket() = 0;		// ">\n" + indent++ vs ">"
	virtual void		beforeChildrenEnd() = 0;			// indent-- + indentation vs nothing
	virtual void		writeAfterCloseTag() = 0;			// "\n" vs nothing
	virtual void		writeBeforeText() = 0;				// indentation vs nothing
	virtual void		writeAfterText() = 0;				// "\n" vs nothing

public:
	XMLSerializer(const std::string & filename)
		: file(filename.c_str(), std::ios_base::out) {}
	virtual ~XMLSerializer() {}

	// Template method — the invariant skeleton (non-virtual)
	void			serialize(dom::Node * node);
};

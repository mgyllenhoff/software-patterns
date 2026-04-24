#pragma once

#include <string>
#include <fstream>
#include <ios>
#include <ostream>

#include "Node.H"

class NodeProcessor;
class NodeVisitor;

class XMLSerializer
{
protected:
	std::fstream		file;

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

	void			serialize(dom::Node * node);

	static void		serializePretty(dom::Node * node, std::ostream & output);
	static void		serializeMinimal(dom::Node * node, std::ostream & output);
	static void		serializePrettyVisitor(dom::Node * node, std::ostream & output);
	static void		serializeMinimalVisitor(dom::Node * node, std::ostream & output);

private:
	static void		serializeWithProcessor(dom::Node * node, NodeProcessor & processor);
	static void		serializeWithVisitor(dom::Node * node, NodeVisitor & visitor);
};

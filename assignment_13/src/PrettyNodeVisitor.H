#ifndef PRETTYNODEVISITOR_H
#define PRETTYNODEVISITOR_H

#include <ostream>
#include "NodeVisitor.H"

class PrettyNodeVisitor : public NodeVisitor
{
private:
	std::ostream &	file;
	int		indentationLevel;

	void		writeIndentation();

public:
	PrettyNodeVisitor(std::ostream & out) : file(out), indentationLevel(0) {}
	virtual ~PrettyNodeVisitor() {}

	virtual void	visitDocumentEnter(dom::Document * doc);
	virtual void	visitDocumentLeave(dom::Document * doc);
	virtual void	visitElementEnter(dom::Element * elem);
	virtual void	visitElementLeave(dom::Element * elem);
	virtual void	visitText(dom::Text * text);
	virtual void	visitAttr(dom::Attr * attr);
};

#endif // PRETTYNODEVISITOR_H

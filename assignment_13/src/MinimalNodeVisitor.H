#ifndef MINIMALNODEVISITOR_H
#define MINIMALNODEVISITOR_H

#include <ostream>
#include "NodeVisitor.H"

class MinimalNodeVisitor : public NodeVisitor
{
private:
	std::ostream &	file;

public:
	MinimalNodeVisitor(std::ostream & out) : file(out) {}
	virtual ~MinimalNodeVisitor() {}

	virtual void	visitDocumentEnter(dom::Document * doc);
	virtual void	visitDocumentLeave(dom::Document * doc);
	virtual void	visitElementEnter(dom::Element * elem);
	virtual void	visitElementLeave(dom::Element * elem);
	virtual void	visitText(dom::Text * text);
	virtual void	visitAttr(dom::Attr * attr);
};

#endif // MINIMALNODEVISITOR_H

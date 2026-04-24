#ifndef NODEVISITOR_H
#define NODEVISITOR_H

namespace dom
{
	class Document;
	class Element;
	class Text;
	class Attr;
}

// Visitor Pattern: Visitor
class NodeVisitor
{
public:
	virtual ~NodeVisitor() {}

	virtual void	visitDocumentEnter(dom::Document * doc)		= 0;
	virtual void	visitDocumentLeave(dom::Document * doc)		= 0;
	virtual void	visitElementEnter(dom::Element * elem)		= 0;
	virtual void	visitElementLeave(dom::Element * elem)		= 0;
	virtual void	visitText(dom::Text * text)			= 0;
	virtual void	visitAttr(dom::Attr * attr)			= 0;
};

#endif // NODEVISITOR_H

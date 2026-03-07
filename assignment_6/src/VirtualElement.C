#include "VirtualElement.H"
#include "XMLTokenizer.H"
#include "XMLParser.H"
#include "XMLDOMBuilder.H"
#include "StandardDOMNodeFactory.H"

VirtualElement::VirtualElement(const std::string & tagName, dom::Document * doc,
                               const std::string & filename)
	: Element_Impl(tagName, doc),
	  filename(filename),
	  childrenStart(0),
	  materialized(false),
	  hasDeferred(false)
{
}

// Called by XMLDOMBuilder::openTagComplete() after the opening '>'
void VirtualElement::setChildrenStart(std::streampos pos)
{
	childrenStart = pos;
	hasDeferred   = true;
}

// On the first child access, reopen the source file at childrenStart,
// build an XMLDOMBuilder targeting this element, and
// drive it with XMLParser::parseChildren()
void VirtualElement::materialize()
{
	if (materialized) return;
	materialized = true;

	if (!hasDeferred) return;	// no children to parse

	XMLTokenizer * tok = new XMLTokenizer(filename, childrenStart);
	XMLDOMBuilder  builder(StandardDOMNodeFactory::Instance(), this);
	XMLParser      parser(tok, &builder);
	parser.parseChildren();
}

// Each calls materialize() before delegating to Element_Impl (which delegates to the inherited NodeList)
dom::Node *     VirtualElement::getFirstChild()  { materialize(); return Element_Impl::getFirstChild(); }
dom::Node *     VirtualElement::getLastChild()   { materialize(); return Element_Impl::getLastChild();  }
dom::NodeList * VirtualElement::getChildNodes()  { materialize(); return Element_Impl::getChildNodes(); }
bool            VirtualElement::hasChildNodes()  { materialize(); return Element_Impl::hasChildNodes(); }

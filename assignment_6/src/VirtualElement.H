#pragma once

#include "Element.H"

// Proxy: Proxy
// Virtual Proxy for dom::Element
class VirtualElement : public Element_Impl
{
	std::string    filename;	// path to the source XML file
	std::streampos childrenStart;	// byte offset just after the opening '>'
	bool           materialized;	// true once materialize() has been called
	bool           hasDeferred;	// false for self-closing elements

	void materialize();

public:
	VirtualElement(const std::string & tagName, dom::Document * doc,
	               const std::string & filename);
	void setChildrenStart(std::streampos pos);

	dom::Node *     getFirstChild()  override;
	dom::Node *     getLastChild()   override;
	dom::NodeList * getChildNodes()  override;
	bool            hasChildNodes()  override;
};

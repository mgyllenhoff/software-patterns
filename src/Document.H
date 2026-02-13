#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include "CompositeNode.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	// Factory Method: Creator
	// Composite Pattern: Composite
	// Decorator Pattern: Component
	class Document : public virtual CompositeNode
	{
	public:
		// Factory Method: FactoryMethod
		virtual Element *	createElement(const std::string & tagName)	= 0;
		// Factory Method: FactoryMethod
		virtual Text *		createTextNode(const std::string & data)	= 0;
		// Factory Method: FactoryMethod
		virtual Attr *		createAttribute(const std::string & name)	= 0;
		virtual Element *	getDocumentElement()				= 0;
	};
};

// Factory Method: ConcreteCreator
// Composite Pattern: Composite
// Decorator Pattern: ConcreteComponent
class Document_Impl : public virtual dom::Document, public virtual CompositeNode_Impl
{
public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);
	virtual dom::Text *	createTextNode(const std::string & data);
	virtual dom::Attr *	createAttribute(const std::string & name);
	virtual dom::Element *	getDocumentElement();
};

#endif // DOCUMENT_H

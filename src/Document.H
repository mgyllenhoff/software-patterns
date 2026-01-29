#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	// Creator
	class Document : public virtual Node
	{
	public:
		// FactoryMethod
		virtual Element *	createElement(const std::string & tagName)	= 0;
		// FactoryMethod
		virtual Text *		createTextNode(const std::string & data)	= 0;
		// FactoryMethod
		virtual Attr *		createAttribute(const std::string & name)	= 0;
		virtual Element *	getDocumentElement()				= 0;
	};
};

// ConcreteCreator
class Document_Impl : public virtual dom::Document, public virtual Node_Impl
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

#ifndef VALIDATING_DOCUMENT_H
#define VALIDATING_DOCUMENT_H

#include "ValidatingCompositeNode.H"
#include "Document.H"

// Decorator Pattern: ConcreteDecorator
class ValidatingDocument : public virtual dom::Document, public ValidatingCompositeNode
{
private:
	dom::Document *	documentDelegate;
public:
	ValidatingDocument(dom::Document * component, XMLValidator * validator)
		: ValidatingCompositeNode(component, validator),
		  documentDelegate(component) {}

	virtual ~ValidatingDocument() {}

	// Validated method
	virtual dom::Node *	appendChild(dom::Node * newChild);

	// Factory methods that wrap returned nodes in decorators
	virtual dom::Element *	createElement(const std::string & tagName);
	virtual dom::Text *	createTextNode(const std::string & data);
	virtual dom::Attr *	createAttribute(const std::string & name);

	// Delegation
	virtual dom::Element *	getDocumentElement(void);
};

#endif // VALIDATING_DOCUMENT_H

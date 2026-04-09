#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <string>
#include "Document.H"
#include "Element.H"
#include "XMLValidator.H"

// Layer 3: Application Logic Layer
class XMLEditor
{
private:
	XMLValidator &	validator;

public:

	explicit XMLEditor(XMLValidator & validator) : validator(validator) {}
	virtual ~XMLEditor() {}

	virtual dom::Element *	addElement(dom::Document * doc,
					   dom::Element * parent,
					   const std::string & tagName);
	virtual bool		removeElement(dom::Element * element);
	virtual bool		setAttribute(dom::Element * element,
					     const std::string & name,
					     const std::string & value);
	virtual bool		removeAttribute(dom::Element * element,
					        const std::string & name);
	virtual bool		addText(dom::Document * doc,
				        dom::Element * element,
				        const std::string & text);
	virtual void		save(dom::Document * doc, const std::string & filename);
};

#endif // XMLEDITOR_H

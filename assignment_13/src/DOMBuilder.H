#pragma once

#include <string>

#include "Document.H"

// Builder: Builder
class DOMBuilder
{
public:
	virtual void		beginElement(const std::string & name) = 0;
	virtual void		addAttribute(const std::string & name, const std::string & value) = 0;
	virtual void		addText(const std::string & data) = 0;
	virtual void		endElement() = 0;
	virtual dom::Document *	getDocument() = 0;

	virtual ~DOMBuilder() {}
};

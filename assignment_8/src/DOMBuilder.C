#include "DOMBuilder.H"
#include "Text.H"

DOMBuilder_Impl::DOMBuilder_Impl()
	: document(0),
	  depth(0),
	  totalNodeCount(0)
{
}

DOMBuilder_Impl::~DOMBuilder_Impl()
{
	delete document;
}

void DOMBuilder_Impl::attach(dom::Observer * obs)
{
	observers.push_back(obs);
}

void DOMBuilder_Impl::detach(dom::Observer * obs)
{
	observers.remove(obs);
}

void DOMBuilder_Impl::notify()
{
	for (dom::Observer * obs : observers)
		obs->update(this);
}

void DOMBuilder_Impl::beginDocument()
{
	document		= new Document_Impl;
	lastAction		= BEGIN_DOCUMENT;
	depth			= 0;
	totalNodeCount		= 1;

	notify();
}

void DOMBuilder_Impl::beginElement(const std::string & tagName)
{
	dom::Element * element	= document->createElement(tagName);

	if (elementStack.empty())
		document->appendChild(element);
	else
		elementStack.top()->appendChild(element);

	elementStack.push(element);
	depth++;
	totalNodeCount++;

	lastAction		= BEGIN_ELEMENT;
	currentNodeName		= tagName;

	notify();
}

void DOMBuilder_Impl::endElement()
{
	std::string tagName	= elementStack.top()->getTagName();
	elementStack.pop();
	depth--;

	lastAction		= END_ELEMENT;
	currentNodeName		= tagName;

	notify();
}

void DOMBuilder_Impl::addText(const std::string & data)
{
	dom::Text * text	= document->createTextNode(data);
	elementStack.top()->appendChild(text);
	totalNodeCount++;

	lastAction		= ADD_TEXT;
	currentValue		= data;

	notify();
}

void DOMBuilder_Impl::addAttribute(const std::string & name, const std::string & value)
{
	elementStack.top()->setAttribute(name, value);

	lastAction		= ADD_ATTRIBUTE;
	currentNodeName		= name;
	currentValue		= value;

	notify();
}

void DOMBuilder_Impl::endDocument()
{
	lastAction		= END_DOCUMENT;

	notify();
}

dom::Document * DOMBuilder_Impl::getDocument()
{
	return document;
}

DOMBuilder_Impl::BuildAction DOMBuilder_Impl::getLastAction() const
{
	return lastAction;
}

const std::string & DOMBuilder_Impl::getCurrentNodeName() const
{
	return currentNodeName;
}

const std::string & DOMBuilder_Impl::getCurrentValue() const
{
	return currentValue;
}

int DOMBuilder_Impl::getDepth() const
{
	return depth;
}

int DOMBuilder_Impl::getTotalNodeCount() const
{
	return totalNodeCount;
}

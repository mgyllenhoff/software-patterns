#include "DOMFlyweightFactory.H"
#include "ElementFlyweight.H"
#include "AttrFlyweight.H"
#include "TextFlyweight.H"

std::unordered_map<std::string, ElementFlyweight *>	DOMFlyweightFactory::elements;
std::unordered_map<std::string, AttrFlyweight *>	DOMFlyweightFactory::attrs;
std::unordered_map<std::string, TextFlyweight *>	DOMFlyweightFactory::texts;

const ElementFlyweight * DOMFlyweightFactory::getElement(const std::string & tagName)
{
	auto it = elements.find(tagName);
	if (it != elements.end())
		return it->second;

	ElementFlyweight * fw	= new ElementFlyweight(tagName);
	elements[tagName]	= fw;
	return fw;
}

const AttrFlyweight * DOMFlyweightFactory::getAttr(const std::string & attrName)
{
	auto it = attrs.find(attrName);
	if (it != attrs.end())
		return it->second;

	AttrFlyweight * fw	= new AttrFlyweight(attrName);
	attrs[attrName]		= fw;
	return fw;
}

const TextFlyweight * DOMFlyweightFactory::getText(const std::string & textData)
{
	auto it = texts.find(textData);
	if (it != texts.end())
		return it->second;

	TextFlyweight * fw	= new TextFlyweight(textData);
	texts[textData]		= fw;
	return fw;
}

void DOMFlyweightFactory::clear()
{
	for (auto & p : elements)	delete p.second;
	for (auto & p : attrs)		delete p.second;
	for (auto & p : texts)		delete p.second;
	elements.clear();
	attrs.clear();
	texts.clear();
}

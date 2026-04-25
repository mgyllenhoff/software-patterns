#ifndef DOMFLYWEIGHTFACTORY_H
#define DOMFLYWEIGHTFACTORY_H

#include <string>
#include <unordered_map>

class NodeFlyweight;
class ElementFlyweight;
class AttrFlyweight;
class TextFlyweight;

// Flyweight Pattern: FlyweightFactory
class DOMFlyweightFactory
{
private:
	// Three pools (one per concrete node type)
	static std::unordered_map<std::string, ElementFlyweight *>	elements;
	static std::unordered_map<std::string, AttrFlyweight *>		attrs;
	static std::unordered_map<std::string, TextFlyweight *>		texts;

public:
	static const ElementFlyweight *	getElement(const std::string & tagName);
	static const AttrFlyweight *	getAttr(const std::string & attrName);
	static const TextFlyweight *	getText(const std::string & textData);
	static void	clear();
};

#endif // DOMFLYWEIGHTFACTORY_H

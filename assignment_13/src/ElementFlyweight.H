#ifndef ELEMENTFLYWEIGHT_H
#define ELEMENTFLYWEIGHT_H

#include "NodeFlyweight.H"

// Flyweight Pattern: ConcreteFlyweight
//   Intrinsic state stored here: tagName
class ElementFlyweight : public NodeFlyweight
{
private:
	const std::string	tagName;	// intrinsic

public:
	explicit ElementFlyweight(const std::string & name) : tagName(name) {}
	const std::string & getIntrinsicName() const override { return tagName; }
};

#endif // ELEMENTFLYWEIGHT_H

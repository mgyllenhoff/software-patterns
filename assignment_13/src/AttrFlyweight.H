#ifndef ATTRFLYWEIGHT_H
#define ATTRFLYWEIGHT_H

#include "NodeFlyweight.H"

// Flyweight Pattern: ConcreteFlyweight
//   Intrinsic state stored here: attrName
class AttrFlyweight : public NodeFlyweight
{
private:
	const std::string	attrName;	// intrinsic

public:
	explicit AttrFlyweight(const std::string & name) : attrName(name) {}
	const std::string & getIntrinsicName() const override { return attrName; }
};

#endif // ATTRFLYWEIGHT_H
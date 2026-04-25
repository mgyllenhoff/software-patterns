#ifndef TEXTFLYWEIGHT_H
#define TEXTFLYWEIGHT_H

#include "NodeFlyweight.H"

// Flyweight Pattern: ConcreteFlyweight
//   Intrinsic state stored here: textData
class TextFlyweight : public NodeFlyweight
{
private:
	const std::string	textData;	// intrinsic

public:
	explicit TextFlyweight(const std::string & data) : textData(data) {}

	const std::string & getIntrinsicName() const override { return textData; }
};

#endif // TEXTFLYWEIGHT_H

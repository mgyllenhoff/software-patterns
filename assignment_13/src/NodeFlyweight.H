#ifndef NODEFLYWEIGHT_H
#define NODEFLYWEIGHT_H

#include <string>

// Flyweight Pattern: Flyweight
class NodeFlyweight
{
public:
	virtual ~NodeFlyweight() {}

	// Returns the intrinsic name carried by this flyweight
	//   Element:   tag name
	//   Attr:      attr name
	//   Text:      text data
	virtual const std::string &	getIntrinsicName() const = 0;
};

#endif // NODEFLYWEIGHT_H

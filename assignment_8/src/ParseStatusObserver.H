#ifndef PARSESTATUSOBSERVER_H
#define PARSESTATUSOBSERVER_H

#include "Observer.H"
#include "DOMBuilder.H"

// Observer Pattern: ConcreteObserver
class ParseStatusObserver : public dom::Observer
{
private:
	DOMBuilder_Impl *	builder;

public:
	ParseStatusObserver(DOMBuilder_Impl * b);
	virtual ~ParseStatusObserver();

	virtual void	update(dom::Subject * subject)	override;
};

#endif // PARSESTATUSOBSERVER_H

#ifndef PARSESTATUSOBSERVER_H
#define PARSESTATUSOBSERVER_H

#include "Observer.H"
#include "DOMParseMediator.H"

// Mediator Pattern: Colleague
// Observer Pattern: ConcreteObserver
class ParseStatusObserver : public dom::Observer
{
private:
	DOMParseMediator *	mediator;	// Knows its Mediator, not DOMBuilder_Impl directly

public:
	ParseStatusObserver(DOMParseMediator * m);
	virtual ~ParseStatusObserver();

	virtual void	update(dom::Subject * subject)	override;
};

#endif // PARSESTATUSOBSERVER_H

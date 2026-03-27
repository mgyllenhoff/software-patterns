#ifndef DOMPARSE_MEDIATOR_H
#define DOMPARSE_MEDIATOR_H

#include <string>

#include "Mediator.H"
#include "Observer.H"
#include "DOMBuilder.H"

class ParseStatusObserver;	// Forward declaration to break circular dependency

// Mediator Pattern: ConcreteMediator
// Observer Pattern: ConcreteObserver (bridges Subject::notify() → Mediator::changed() per GoF)
class DOMParseMediator : public dom::Mediator, public dom::Observer
{
private:
	DOMBuilder_Impl *	builder; // subject colleague
	ParseStatusObserver *	statusObserver;	// display colleague

public:
	DOMParseMediator(DOMBuilder_Impl * b);
	virtual ~DOMParseMediator();

	void	setObserver(ParseStatusObserver * obs);

	// dom::Mediator changes routes from DOMBuilder colleague to ParseStatusObserver colleague
	virtual void	changed(dom::Subject * colleague)	override;

	// dom::Observer bridges Subject::notify() into Mediator::changed()
	virtual void	update(dom::Subject * subject)		override;

	// State accessors delegating to builder and queried by ParseStatusObserver (pull model)
	DOMBuilder_Impl::BuildAction	getLastAction()		const;
	const std::string &		getCurrentNodeName()	const;
	const std::string &		getCurrentValue()	const;
	int				getDepth()		const;
	int				getTotalNodeCount()	const;
};

#endif // DOMPARSE_MEDIATOR_H

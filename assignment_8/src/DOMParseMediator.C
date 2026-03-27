#include "DOMParseMediator.H"
#include "ParseStatusObserver.H"

DOMParseMediator::DOMParseMediator(DOMBuilder_Impl * b)
	: builder(b),
	  statusObserver(0)
{
}

DOMParseMediator::~DOMParseMediator()
{
}

void DOMParseMediator::setObserver(ParseStatusObserver * obs)
{
	statusObserver = obs;
}

void DOMParseMediator::update(dom::Subject * subject)
{
	changed(subject);
}

void DOMParseMediator::changed(dom::Subject * colleague)
{
	if (colleague == builder && statusObserver)
		statusObserver->update(colleague);
}

DOMBuilder_Impl::BuildAction DOMParseMediator::getLastAction() const
{
	return builder->getLastAction();
}

const std::string & DOMParseMediator::getCurrentNodeName() const
{
	return builder->getCurrentNodeName();
}

const std::string & DOMParseMediator::getCurrentValue() const
{
	return builder->getCurrentValue();
}

int DOMParseMediator::getDepth() const
{
	return builder->getDepth();
}

int DOMParseMediator::getTotalNodeCount() const
{
	return builder->getTotalNodeCount();
}

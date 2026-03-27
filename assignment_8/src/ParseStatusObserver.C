#include <stdio.h>
#include "ParseStatusObserver.H"

ParseStatusObserver::ParseStatusObserver(DOMParseMediator * m)
	: mediator(m)
{
}

ParseStatusObserver::~ParseStatusObserver()
{
}

void ParseStatusObserver::update(dom::Subject * subject)
{
	(void)subject;	// State is queried from the Mediator, which delegates to DOMBuilder_Impl
	DOMBuilder_Impl::BuildAction	action		= mediator->getLastAction();
	const std::string &		nodeName	= mediator->getCurrentNodeName();
	const std::string &		value		= mediator->getCurrentValue();
	int				depth		= mediator->getDepth();
	int				total		= mediator->getTotalNodeCount();

	switch (action)
	{
	case DOMBuilder_Impl::BEGIN_DOCUMENT:
		printf("[Parse] Document started. Total nodes: %d\n", total);
		break;

	case DOMBuilder_Impl::BEGIN_ELEMENT:
		printf("[Parse]%*s+ Element '<%s>' opened. Depth: %d, Total nodes: %d\n",
		       depth * 2, "", nodeName.c_str(), depth, total);
		break;

	case DOMBuilder_Impl::END_ELEMENT:
		printf("[Parse]%*s- Element '</%s>' closed. Depth: %d\n",
		       (depth + 1) * 2, "", nodeName.c_str(), depth);
		break;

	case DOMBuilder_Impl::ADD_TEXT:
		printf("[Parse]%*sText node: \"%s\". Total nodes: %d\n",
		       (depth + 1) * 2, "", value.c_str(), total);
		break;

	case DOMBuilder_Impl::ADD_ATTRIBUTE:
		printf("[Parse]%*sAttribute '%s'='%s' set.\n",
		       (depth + 1) * 2, "", nodeName.c_str(), value.c_str());
		break;

	case DOMBuilder_Impl::END_DOCUMENT:
		printf("[Parse] Document complete. Total nodes: %d\n", total);
		break;
	}
}

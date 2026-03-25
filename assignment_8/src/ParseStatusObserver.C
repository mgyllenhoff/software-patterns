#include <stdio.h>
#include "ParseStatusObserver.H"

ParseStatusObserver::ParseStatusObserver(DOMBuilder_Impl * b)
	: builder(b)
{
}

ParseStatusObserver::~ParseStatusObserver()
{
}

void ParseStatusObserver::update(dom::Subject * subject)
{
	(void)subject;	// Pull model: state is queried directly from the stored builder reference
	DOMBuilder_Impl::BuildAction	action		= builder->getLastAction();
	const std::string &		nodeName	= builder->getCurrentNodeName();
	const std::string &		value		= builder->getCurrentValue();
	int				depth		= builder->getDepth();
	int				total		= builder->getTotalNodeCount();

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

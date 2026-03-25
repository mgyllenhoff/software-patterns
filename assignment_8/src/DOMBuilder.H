#ifndef DOMBUILDER_H
#define DOMBUILDER_H

#include <list>
#include <stack>
#include <string>

#include "Document.H"
#include "Element.H"
#include "Observer.H"

namespace dom
{
	// Builder Pattern: Builder
	class Builder
	{
	public:
		virtual ~Builder() {}

		virtual void		beginDocument()						= 0;
		virtual void		beginElement(const std::string & tagName)		= 0;
		virtual void		endElement()						= 0;
		virtual void		addText(const std::string & data)			= 0;
		virtual void		addAttribute(const std::string & name,
						     const std::string & value)			= 0;
		virtual void		endDocument()						= 0;
		virtual Document *	getDocument()						= 0;
	};
};

// Builder Pattern: ConcreteBuilder
// Observer Pattern: ConcreteSubject
class DOMBuilder_Impl : public dom::Builder, public dom::Subject
{
public:
	enum BuildAction
	{
		BEGIN_DOCUMENT,
		BEGIN_ELEMENT,
		END_ELEMENT,
		ADD_TEXT,
		ADD_ATTRIBUTE,
		END_DOCUMENT
	};

private:
	std::list<dom::Observer *>	observers;

	dom::Document *			document;
	std::stack<dom::Element *>	elementStack;

	BuildAction			lastAction;
	std::string			currentNodeName;
	std::string			currentValue;
	int				depth;
	int				totalNodeCount;

public:
	DOMBuilder_Impl();
	virtual ~DOMBuilder_Impl();

	// dom::Subject interface
	virtual void	attach(dom::Observer * obs)	override;
	virtual void	detach(dom::Observer * obs)	override;
	virtual void	notify()			override;

	// dom::Builder interface
	virtual void		beginDocument()						override;
	virtual void		beginElement(const std::string & tagName)		override;
	virtual void		endElement()						override;
	virtual void		addText(const std::string & data)			override;
	virtual void		addAttribute(const std::string & name,
					     const std::string & value)			override;
	virtual void		endDocument()						override;
	virtual dom::Document *	getDocument()						override;

	// State query accessors for ConcreteObserver (pull model)
	BuildAction		getLastAction()		const;
	const std::string &	getCurrentNodeName()	const;
	const std::string &	getCurrentValue()	const;
	int			getDepth()		const;
	int			getTotalNodeCount()	const;
};

#endif // DOMBUILDER_H

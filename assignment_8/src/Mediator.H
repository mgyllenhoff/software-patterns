#ifndef MEDIATOR_H
#define MEDIATOR_H

namespace dom
{
	class Subject;

	// Mediator Pattern: Mediator
	class Mediator
	{
	public:
		virtual ~Mediator() {}

		virtual void	changed(Subject * colleague)	= 0;
	};
};

#endif // MEDIATOR_H

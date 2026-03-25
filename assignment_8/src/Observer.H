#ifndef OBSERVER_H
#define OBSERVER_H

namespace dom
{
	class Observer;

	// Observer Pattern: Subject
	class Subject
	{
	public:
		virtual ~Subject() {}

		virtual void	attach(Observer * obs)	= 0;
		virtual void	detach(Observer * obs)	= 0;
		virtual void	notify()		= 0;
	};

	// Observer Pattern: Observer
	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void	update(Subject * subject)	= 0;
	};
};

#endif // OBSERVER_H

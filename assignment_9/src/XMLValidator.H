#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "Element.H"

class ValidChildren
{
	friend class XMLValidator;	// Memento: Originator accesses private state for snapshot
private:
	std::string			thisElement;
	std::vector<std::string>	validChildren;
	std::vector<bool>		childIsAttribute;
	bool				_canHaveText;
public:
	ValidChildren(std::string _thisElement) : thisElement(_thisElement), _canHaveText(false)	{}

	virtual std::string	getThisElement(void)			{ return thisElement; }
	virtual bool		canHaveText(void)			{ return _canHaveText; }
	virtual void		setCanHaveText(bool __canHaveText)	{ _canHaveText = __canHaveText; }

	virtual void		addValidChild(const std::string & child, bool isAttribute);
	virtual bool		childIsValid(const std::string & child, bool isAttribute);
};

// Memento: Memento
class XMLValidatorMemento
{
	friend class XMLValidator;	// Only the Originator may access state
private:
	struct ValidChildrenSnapshot
	{
		std::string			thisElement;
		std::vector<std::string>	validChildren;
		std::vector<bool>		childIsAttribute;
		bool				canHaveText;
	};
	std::vector<ValidChildrenSnapshot>	state;

	const std::vector<ValidChildrenSnapshot> &	GetState(void)						{ return state; }
	void						SetState(const std::vector<ValidChildrenSnapshot> & s)	{ state = s; }

	XMLValidatorMemento() {}	// only XMLValidator may construct
};

// Memento: Originator
class XMLValidator
{
private:
	std::vector<ValidChildren *>	schema;
public:
	XMLValidator(void)	{}
	~XMLValidator() { for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);
	virtual bool					canRootElement(std::string newElement);
	virtual bool					canAddElement(dom::Element * element, std::string newElement);
	virtual bool					canAddText(dom::Element * element);
	virtual bool					canAddAttribute(dom::Element * element, std::string newAttribute);

	virtual XMLValidatorMemento *			CreateMemento(void);
	virtual void					SetMemento(XMLValidatorMemento * memento);
};

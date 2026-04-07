#ifndef XMLAPPLICATION_H
#define XMLAPPLICATION_H

#include "Document.H"
#include "XMLLoader.H"
#include "XMLEditor.H"
#include "XMLDisplay.H"
#include "XMLValidator.H"

// Layer 4: Presentation Layer
class XMLApplication
{
private:
	dom::Document *	document;
	std::string	outputFile;

	// Layer 3 services
	XMLValidator	validator;
	XMLLoader	loader;
	XMLEditor	editor;

	// Layer 4 peer
	XMLDisplay	display;

	// UI helpers
	virtual void	printMenu(void);
	virtual void	redraw(void);
	virtual int	readInt(const char * prompt);
	virtual void	readLine(const char * prompt, std::string & out);

	// Edit command handlers (each reads from stdin and calls XMLEditor)
	virtual void	handleAddElement(void);
	virtual void	handleRemoveElement(void);
	virtual void	handleSetAttribute(void);
	virtual void	handleRemoveAttribute(void);
	virtual void	handleAddText(void);

public:
	XMLApplication(void);
	virtual ~XMLApplication(void);

	virtual void	run(const std::string & inputFile,
			    const std::string & outputFile);
};

#endif // XMLAPPLICATION_H

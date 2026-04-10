#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "Document.H"
#include "XMLLoader.H"
#include "XMLEditor.H"
#include "XMLDisplay.H"

// Shared mutable state threaded through every Command
struct AppContext
{
	dom::Document *&	document; // reference to XMLApplication::document
	XMLLoader &		loader;
	XMLEditor &		editor;
	XMLDisplay &		display;

	AppContext(dom::Document *& doc,
		   XMLLoader &      ldr,
		   XMLEditor &      edt,
		   XMLDisplay &     dsp)
		: document(doc), loader(ldr), editor(edt), display(dsp) {}
};

#endif // APPCONTEXT_H

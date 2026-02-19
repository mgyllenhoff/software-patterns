#include "MinimalXMLSerializer.H"

// All hooks that control formatting are no-ops.
// writeEmptyElementClose and writeAfterOpenBracket still write the
// required XML punctuation (">" and "/>") — they just omit newlines.

void MinimalXMLSerializer::writeDeclarationSuffix()		{}
void MinimalXMLSerializer::writeBeforeOpenTag()			{}
void MinimalXMLSerializer::writeAfterAttributes(int)	{}
void MinimalXMLSerializer::writeEmptyElementClose()		{ file << "/>"; }
void MinimalXMLSerializer::writeAfterOpenBracket()		{ file << ">"; }
void MinimalXMLSerializer::beforeChildrenEnd()			{}
void MinimalXMLSerializer::writeAfterCloseTag()			{}
void MinimalXMLSerializer::writeBeforeText()			{}
void MinimalXMLSerializer::writeAfterText()				{}

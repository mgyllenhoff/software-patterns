#include "MinimalXMLSerializer.H"

void MinimalXMLSerializer::writeDeclarationSuffix()		{}
void MinimalXMLSerializer::writeBeforeOpenTag()			{}
void MinimalXMLSerializer::writeAfterAttributes(int)	{}
void MinimalXMLSerializer::writeEmptyElementClose()		{ file << "/>"; }
void MinimalXMLSerializer::writeAfterOpenBracket()		{ file << ">"; }
void MinimalXMLSerializer::beforeChildrenEnd()			{}
void MinimalXMLSerializer::writeAfterCloseTag()			{}
void MinimalXMLSerializer::writeBeforeText()			{}
void MinimalXMLSerializer::writeAfterText()				{}

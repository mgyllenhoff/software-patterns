#include "PrettyXMLSerializer.H"

void PrettyXMLSerializer::writeIndentation()
{
	for (int i = 0; i < indentationLevel; i++)
		file << "\t";
}

void PrettyXMLSerializer::writeDeclarationSuffix()
{
	file << "\n";
}

void PrettyXMLSerializer::writeBeforeOpenTag()
{
	writeIndentation();
}

void PrettyXMLSerializer::writeAfterAttributes(int attrCount)
{
	if (attrCount > 0)
		file << " ";
}

void PrettyXMLSerializer::writeEmptyElementClose()
{
	file << "/>";
	file << "\n";
}

void PrettyXMLSerializer::writeAfterOpenBracket()
{
	file << ">";
	file << "\n";
	indentationLevel++;
}

void PrettyXMLSerializer::beforeChildrenEnd()
{
	indentationLevel--;
	writeIndentation();
}

void PrettyXMLSerializer::writeAfterCloseTag()
{
	file << "\n";
}

void PrettyXMLSerializer::writeBeforeText()
{
	writeIndentation();
}

void PrettyXMLSerializer::writeAfterText()
{
	file << "\n";
}

#pragma once

#include "XMLSerializer.H"

// Template Method: ConcreteClass
class PrettyXMLSerializer : public XMLSerializer
{
private:
	int				indentationLevel;
	void			writeIndentation();

protected:
	void			writeDeclarationSuffix() override;
	void			writeBeforeOpenTag() override;
	void			writeAfterAttributes(int attrCount) override;
	void			writeEmptyElementClose() override;
	void			writeAfterOpenBracket() override;
	void			beforeChildrenEnd() override;
	void			writeAfterCloseTag() override;
	void			writeBeforeText() override;
	void			writeAfterText() override;

public:
	PrettyXMLSerializer(const std::string & filename)
		: XMLSerializer(filename), indentationLevel(0) {}
};

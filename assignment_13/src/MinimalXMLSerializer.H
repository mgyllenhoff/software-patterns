#pragma once

#include "XMLSerializer.H"

class MinimalXMLSerializer : public XMLSerializer
{
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
	MinimalXMLSerializer(const std::string & filename)
		: XMLSerializer(filename) {}
};

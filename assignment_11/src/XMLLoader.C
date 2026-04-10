#include "XMLLoader.H"
#include "XMLTokenizer.H"	// Layer 1
#include "Document.H"		// Layer 2
#include "Element.H"		// Layer 2
#include "Text.H"			// Layer 2
#include <fstream>

// Strip leading and trailing whitespace
std::string XMLLoader::trimToken(const std::string & s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos) return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

// If ATTRIBUTE tokens look like " name=" then trim whitespace and strip trailing '='
std::string XMLLoader::cleanAttributeName(const std::string & s)
{
	std::string trimmed = trimToken(s);
	if (!trimmed.empty() && trimmed.back() == '=')
		trimmed.pop_back();
	return trimToken(trimmed);
}

// If ATTRIBUTE_VALUE tokens look like "\"value\"" then strip the surrounding quotes
std::string XMLLoader::cleanAttributeValue(const std::string & s)
{
	if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
		return s.substr(1, s.size() - 2);
	return s;
}

// State-machine XML parser
dom::Document * XMLLoader::load(const std::string & filename)
{
	// Verify the file exists and is readable before constructing the document
	std::ifstream check(filename);
	if (!check.good())
		return nullptr;
	check.close();

	XMLTokenizer	tokenizer(filename);
	dom::Document *	doc	= new Document_Impl();

	// Stack of open elements
	std::vector<dom::Element *>	stack;

	bool		inProlog	= false;	// inside <?xml ... ?>
	bool		inClosingTag	= false;	// just saw </
	bool		expectAttrValue	= false;	// ATTRIBUTE token seen, awaiting value
	std::string	pendingAttr;			// attribute name being built

	XMLTokenizer::XMLToken * token = nullptr;

	do
	{
		delete token;
		token = tokenizer.getNextToken();

		switch (token->getTokenType())
		{
		// Prolog: Skip everything between <? and ?>
		case XMLTokenizer::XMLToken::PROLOG_START:
			inProlog = true;
			break;

		case XMLTokenizer::XMLToken::PROLOG_END:
			inProlog = false;
			break;

		// TAG_END closes an opening tag (children may follow) or the prolog
		case XMLTokenizer::XMLToken::TAG_END:
			if (inProlog)
				inProlog = false;	// tokenizer may emit TAG_END for ?>
			// else opening tag is complete and element stays on stack so
			// subsequent children are appended to it 
			break;

		// TAG_CLOSE_START signals a closing </tag> sequence
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			inClosingTag = true;
			break;

		// ELEMENT - either the tag name in an opening tag or in </tag>
		case XMLTokenizer::XMLToken::ELEMENT:
		{
			if (inProlog) break;	// skip "xml" identifier inside prolog

			if (inClosingTag)
			{
				// Closing tag: pop the top element and attach it to its parent
				inClosingTag = false;
				if (!stack.empty())
				{
					dom::Element * elem = stack.back();
					stack.pop_back();
					if (!stack.empty())
						stack.back()->appendChild(elem);
					else
						doc->appendChild(elem);
				}
			}
			else
			{
				// Opening tag: create a new element and push onto the stack
				dom::Element * elem = doc->createElement(trimToken(token->getToken()));
				stack.push_back(elem);
			}
			break;
		}

		// ATTRIBUTE — attribute name (token includes trailing '=')
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			if (inProlog) break;
			pendingAttr	= cleanAttributeName(token->getToken());
			expectAttrValue	= true;
			break;

		// ATTRIBUTE_VALUE — quoted attribute value, e.g. "hello"
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			if (inProlog || !expectAttrValue || stack.empty()) break;
			stack.back()->setAttribute(pendingAttr, cleanAttributeValue(token->getToken()));
			expectAttrValue = false;
			break;

		// NULL_TAG_END — self-closing tag />
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			if (!stack.empty())
			{
				dom::Element * elem = stack.back();
				stack.pop_back();
				if (!stack.empty())
					stack.back()->appendChild(elem);
				else
					doc->appendChild(elem);
			}
			break;

		// VALUE — text content between tags (e.g. "Hello World")
		case XMLTokenizer::XMLToken::VALUE:
		{
			if (inProlog || stack.empty()) break;
			std::string text = trimToken(token->getToken());
			if (!text.empty())
			{
				dom::Text * textNode = doc->createTextNode(text);
				stack.back()->appendChild(textNode);
			}
			break;
		}

		default:
			break;
		}

	} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

	delete token;
	return doc;
}

#include "DOMDocumentAdapter.H"
#include "DOMElementAdapter.H"
#include "DOMTextAdapter.H"
#include "DOMAttrAdapter.H"

XERCES::DOMElement * DOMDocumentAdapter::createElement(const XERCES::XMLCh * tagName)
{
    if (!tagName)
        return nullptr;
    dom::Element * elem = _docAdaptee->createElement(std::string(tagName));
    return elem ? new DOMElementAdapter(elem) : nullptr;
}

XERCES::DOMText * DOMDocumentAdapter::createTextNode(const XERCES::XMLCh * data)
{
    if (!data)
        return nullptr;
    dom::Text * text = _docAdaptee->createTextNode(std::string(data));
    return text ? new DOMTextAdapter(text) : nullptr;
}

XERCES::DOMAttr * DOMDocumentAdapter::createAttribute(const XERCES::XMLCh * name)
{
    if (!name)
        return nullptr;
    dom::Attr * attr = _docAdaptee->createAttribute(std::string(name));
    return attr ? new DOMAttrAdapter(attr) : nullptr;
}

XERCES::DOMElement * DOMDocumentAdapter::getDocumentElement() const
{
    dom::Element * elem = _docAdaptee->getDocumentElement();
    return elem ? new DOMElementAdapter(elem) : nullptr;
}

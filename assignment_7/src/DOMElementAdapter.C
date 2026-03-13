#include "DOMElementAdapter.H"
#include "DOMAttrAdapter.H"
#include "DOMNodeListAdapter.H"
#include "DOMNodeAdapter.H"

const XERCES::XMLCh * DOMElementAdapter::getTagName() const
{
    return _elemAdaptee->getTagName().c_str();
}

const XERCES::XMLCh * DOMElementAdapter::getAttribute(const XERCES::XMLCh * name) const
{
    if (!name)
        return nullptr;
    return _elemAdaptee->getAttribute(std::string(name)).c_str();
}

XERCES::DOMAttr * DOMElementAdapter::getAttributeNode(const XERCES::XMLCh * name) const
{
    if (!name)
        return nullptr;
    dom::Attr * attr = _elemAdaptee->getAttributeNode(std::string(name));
    return attr ? new DOMAttrAdapter(attr) : nullptr;
}

XERCES::DOMNodeList * DOMElementAdapter::getElementsByTagName(const XERCES::XMLCh * name) const
{
    if (!name)
        return nullptr;
    dom::NodeList * list = _elemAdaptee->getElementsByTagName(std::string(name));
    return list ? new DOMNodeListAdapter(list) : nullptr;
}

void DOMElementAdapter::setAttribute(const XERCES::XMLCh * name, const XERCES::XMLCh * value)
{
    if (name && value)
        _elemAdaptee->setAttribute(std::string(name), std::string(value));
}

XERCES::DOMAttr * DOMElementAdapter::setAttributeNode(XERCES::DOMAttr * newAttr)
{
    if (!newAttr)
        return nullptr;
    DOMNodeImplBase * base = dynamic_cast<DOMNodeImplBase *>(newAttr);
    if (!base)
        return nullptr;
    dom::Attr * domAttr = dynamic_cast<dom::Attr *>(base->getDomNode());
    if (!domAttr)
        return nullptr;
    dom::Attr * old = _elemAdaptee->setAttributeNode(domAttr);
    return old ? new DOMAttrAdapter(old) : nullptr;
}

XERCES::DOMAttr * DOMElementAdapter::removeAttributeNode(XERCES::DOMAttr * oldAttr)
{
    if (!oldAttr)
        return nullptr;
    DOMNodeImplBase * base = dynamic_cast<DOMNodeImplBase *>(oldAttr);
    if (!base)
        return nullptr;
    dom::Attr * domAttr = dynamic_cast<dom::Attr *>(base->getDomNode());
    if (!domAttr)
        return nullptr;
    dom::Attr * removed = _elemAdaptee->removeAttributeNode(domAttr);
    return removed ? new DOMAttrAdapter(removed) : nullptr;
}

void DOMElementAdapter::removeAttribute(const XERCES::XMLCh * name)
{
    if (name)
        _elemAdaptee->removeAttribute(std::string(name));
}

bool DOMElementAdapter::hasAttribute(const XERCES::XMLCh * name) const
{
    if (!name)
        return false;
    return _elemAdaptee->hasAttribute(std::string(name));
}

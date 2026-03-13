#include "DOMNamedNodeMapAdapter.H"
#include "DOMNodeAdapter.H"

XERCES::DOMNode * DOMNamedNodeMapAdapter::getNamedItem(const XERCES::XMLCh * name) const
{
    if (!_adaptee || !name)
        return nullptr;
    dom::Node * node = _adaptee->getNamedItem(std::string(name));
    return createDOMNodeAdapter(node);
}

XERCES::DOMNode * DOMNamedNodeMapAdapter::setNamedItem(XERCES::DOMNode * arg)
{
    if (!_adaptee || !arg)
        return nullptr;
    DOMNodeImplBase * base = dynamic_cast<DOMNodeImplBase *>(arg);
    if (!base)
        return nullptr;
    dom::Node * result = _adaptee->setNamedItem(base->getDomNode());
    return createDOMNodeAdapter(result);
}

XERCES::DOMNode * DOMNamedNodeMapAdapter::removeNamedItem(const XERCES::XMLCh * name)
{
    if (!_adaptee || !name)
        return nullptr;
    dom::Node * result = _adaptee->removeNamedItem(std::string(name));
    return createDOMNodeAdapter(result);
}

XERCES::DOMNode * DOMNamedNodeMapAdapter::item(XERCES::XMLSize_t index) const
{
    if (!_adaptee || index >= static_cast<XERCES::XMLSize_t>(_adaptee->size()))
        return nullptr;

    dom::NodeList::iterator it = _adaptee->begin();
    for (XERCES::XMLSize_t i = 0; i < index; ++i)
        ++it;

    return createDOMNodeAdapter(*it);
}

XERCES::XMLSize_t DOMNamedNodeMapAdapter::getLength() const
{
    return _adaptee ? static_cast<XERCES::XMLSize_t>(_adaptee->size()) : 0;
}

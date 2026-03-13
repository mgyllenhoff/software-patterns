#include "DOMNodeListAdapter.H"
#include "DOMNodeAdapter.H"

XERCES::DOMNode * DOMNodeListAdapter::item(XERCES::XMLSize_t index) const
{
    if (!_adaptee || index >= static_cast<XERCES::XMLSize_t>(_adaptee->size()))
        return nullptr;

    dom::NodeList::iterator it = _adaptee->begin();
    for (XERCES::XMLSize_t i = 0; i < index; ++i)
        ++it;

    return createDOMNodeAdapter(*it);
}

XERCES::XMLSize_t DOMNodeListAdapter::getLength() const
{
    return _adaptee ? static_cast<XERCES::XMLSize_t>(_adaptee->size()) : 0;
}

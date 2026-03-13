#include "DOMAttrAdapter.H"
#include "DOMElementAdapter.H"

const XERCES::XMLCh * DOMAttrAdapter::getName() const
{
    return _attrAdaptee->getName().c_str();
}

const XERCES::XMLCh * DOMAttrAdapter::getValue() const
{
    return _attrAdaptee->getValue().c_str();
}

void DOMAttrAdapter::setValue(const XERCES::XMLCh * value)
{
    if (value)
        _attrAdaptee->setValue(std::string(value));
}

XERCES::DOMElement * DOMAttrAdapter::getOwnerElement() const
{
    dom::Element * elem = _attrAdaptee->getOwnerElement();
    return elem ? new DOMElementAdapter(elem) : nullptr;
}

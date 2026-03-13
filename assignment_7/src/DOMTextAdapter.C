#include "DOMTextAdapter.H"

const XERCES::XMLCh * DOMTextAdapter::getData() const
{
    return _textAdaptee->getData().c_str();
}

void DOMTextAdapter::setData(const XERCES::XMLCh * data)
{
    if (data)
        _textAdaptee->setData(std::string(data));
}

XERCES::XMLSize_t DOMTextAdapter::getLength() const
{
    return static_cast<XERCES::XMLSize_t>(_textAdaptee->getLength());
}

const XERCES::XMLCh * DOMTextAdapter::substringData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count) const
{
    return _textAdaptee->substringData(static_cast<int>(offset), static_cast<int>(count)).c_str();
}

void DOMTextAdapter::appendData(const XERCES::XMLCh * arg)
{
    if (arg)
        _textAdaptee->appendData(std::string(arg));
}

void DOMTextAdapter::insertData(XERCES::XMLSize_t offset, const XERCES::XMLCh * arg)
{
    if (arg)
        _textAdaptee->insertData(static_cast<int>(offset), std::string(arg));
}

void DOMTextAdapter::deleteData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count)
{
    _textAdaptee->deleteData(static_cast<int>(offset), static_cast<int>(count));
}

void DOMTextAdapter::replaceData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count, const XERCES::XMLCh * arg)
{
    if (arg)
        _textAdaptee->replaceData(static_cast<int>(offset), static_cast<int>(count), std::string(arg));
}

XERCES::DOMText * DOMTextAdapter::splitText(XERCES::XMLSize_t offset)
{
    dom::Text * newText = _textAdaptee->splitText(static_cast<int>(offset));
    return newText ? new DOMTextAdapter(newText) : nullptr;
}

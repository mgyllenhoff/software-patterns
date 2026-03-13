#ifndef DOMNAMEDNODEMAPADAPTER_H
#define DOMNAMEDNODEMAPADAPTER_H

#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include "NamedNodeMap.H"

// Adapter Pattern: Adapter
class DOMNamedNodeMapAdapter : public XERCES::DOMNamedNodeMap
{
private:
    dom::NamedNodeMap * _adaptee;

public:
    explicit DOMNamedNodeMapAdapter(dom::NamedNodeMap * map) : _adaptee(map) {}
    virtual ~DOMNamedNodeMapAdapter() {}

    virtual XERCES::DOMNode *   getNamedItem(const XERCES::XMLCh * name) const override;
    virtual XERCES::DOMNode *   setNamedItem(XERCES::DOMNode * arg) override;
    virtual XERCES::DOMNode *   removeNamedItem(const XERCES::XMLCh * name) override;
    virtual XERCES::DOMNode *   item(XERCES::XMLSize_t index) const override;
    virtual XERCES::XMLSize_t   getLength() const override;

    // NS variant stubs
    virtual XERCES::DOMNode *   getNamedItemNS(const XERCES::XMLCh * /*nsURI*/, const XERCES::XMLCh * /*localName*/) const override { return nullptr; }
    virtual XERCES::DOMNode *   setNamedItemNS(XERCES::DOMNode * /*arg*/) override { return nullptr; }
    virtual XERCES::DOMNode *   removeNamedItemNS(const XERCES::XMLCh * /*nsURI*/, const XERCES::XMLCh * /*localName*/) override { return nullptr; }

    virtual void                release() override {}
};

#endif // DOMNAMEDNODEMAPADAPTER_H

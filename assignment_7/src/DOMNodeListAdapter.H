#ifndef DOMNODELISTADAPTER_H
#define DOMNODELISTADAPTER_H

#include <xercesc/dom/DOMNodeList.hpp>
#include "NodeList.H"

// Adapter Pattern: Adapter
class DOMNodeListAdapter : public XERCES::DOMNodeList
{
private:
    dom::NodeList * _adaptee;

public:
    explicit DOMNodeListAdapter(dom::NodeList * nodeList) : _adaptee(nodeList) {}
    virtual ~DOMNodeListAdapter() {}

    virtual XERCES::DOMNode *   item(XERCES::XMLSize_t index) const override;
    virtual XERCES::XMLSize_t   getLength() const override;
    virtual void                release() override {}
};

#endif // DOMNODELISTADAPTER_H

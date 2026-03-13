#if !defined(XERCESC_INCLUDE_GUARD_DOMNAMEDNODEMAP_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNAMEDNODEMAP_HPP

#include <xercesc/dom/DOMNodeList.hpp>

namespace XERCES
{

// Adapter Pattern: Target
class DOMNamedNodeMap
{
protected:
    DOMNamedNodeMap() {}
    DOMNamedNodeMap(const DOMNamedNodeMap &) {}
private:
    DOMNamedNodeMap & operator=(const DOMNamedNodeMap &);
public:
    virtual ~DOMNamedNodeMap() {}

    virtual DOMNode *   getNamedItem(const XMLCh *name) const = 0;
    virtual DOMNode *   setNamedItem(DOMNode *arg) = 0;
    virtual DOMNode *   removeNamedItem(const XMLCh *name) = 0;
    virtual DOMNode *   item(XMLSize_t index) const = 0;
    virtual XMLSize_t   getLength() const = 0;

    virtual DOMNode *   getNamedItemNS(const XMLCh *namespaceURI, const XMLCh *localName) const = 0;
    virtual DOMNode *   setNamedItemNS(DOMNode *arg) = 0;
    virtual DOMNode *   removeNamedItemNS(const XMLCh *namespaceURI, const XMLCh *localName) = 0;

    virtual void        release() = 0;
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMNAMEDNODEMAP_HPP

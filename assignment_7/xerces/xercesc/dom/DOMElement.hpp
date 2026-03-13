#if !defined(XERCESC_INCLUDE_GUARD_DOMELEMENT_HPP)
#define XERCESC_INCLUDE_GUARD_DOMELEMENT_HPP

#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

namespace XERCES
{

// Adapter Pattern: Target
class DOMElement : public DOMNode
{
protected:
    DOMElement() {}
    DOMElement(const DOMElement &) {}
private:
    DOMElement & operator=(const DOMElement &);
public:
    virtual ~DOMElement() {}

    virtual const XMLCh *       getTagName() const = 0;
    virtual const XMLCh *       getAttribute(const XMLCh *name) const = 0;
    virtual DOMAttr *           getAttributeNode(const XMLCh *name) const = 0;
    virtual DOMNodeList *       getElementsByTagName(const XMLCh *name) const = 0;
    virtual void                setAttribute(const XMLCh *name, const XMLCh *value) = 0;
    virtual DOMAttr *           setAttributeNode(DOMAttr *newAttr) = 0;
    virtual DOMAttr *           removeAttributeNode(DOMAttr *oldAttr) = 0;
    virtual void                removeAttribute(const XMLCh *name) = 0;
    virtual bool                hasAttribute(const XMLCh *name) const = 0;

    virtual const XMLCh *       getAttributeNS(const XMLCh *namespaceURI, const XMLCh *localName) const = 0;
    virtual void                setAttributeNS(const XMLCh *namespaceURI, const XMLCh *qualifiedName, const XMLCh *value) = 0;
    virtual void                removeAttributeNS(const XMLCh *namespaceURI, const XMLCh *localName) = 0;
    virtual DOMAttr *           getAttributeNodeNS(const XMLCh *namespaceURI, const XMLCh *localName) const = 0;
    virtual DOMAttr *           setAttributeNodeNS(DOMAttr *newAttr) = 0;
    virtual DOMNodeList *       getElementsByTagNameNS(const XMLCh *namespaceURI, const XMLCh *localName) const = 0;
    virtual bool                hasAttributeNS(const XMLCh *namespaceURI, const XMLCh *localName) const = 0;

    virtual void                setIdAttribute(const XMLCh *name, bool isId) = 0;
    virtual void                setIdAttributeNS(const XMLCh *namespaceURI, const XMLCh *localName, bool isId) = 0;
    virtual void                setIdAttributeNode(const DOMAttr *idAttr, bool isId) = 0;
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMELEMENT_HPP

#ifndef DOMELEMENTADAPTER_H
#define DOMELEMENTADAPTER_H

#include <xercesc/dom/DOMElement.hpp>
#include "DOMNodeAdapter.H"
#include "Element.H"

// Adapter Pattern: Adapter
class DOMElementAdapter : public DOMNodeImplBase, public XERCES::DOMElement
{
private:
    dom::Element * _elemAdaptee;

public:
    explicit DOMElementAdapter(dom::Element * elem)
        : DOMNodeImplBase(elem), _elemAdaptee(elem) {}
    virtual ~DOMElementAdapter() {}

    // DOMNode pure virtual overrides
    virtual const XERCES::XMLCh *           getNodeName() const override         { return _getNodeName(); }
    virtual const XERCES::XMLCh *           getNodeValue() const override        { return _getNodeValue(); }
    virtual XERCES::DOMNode::NodeType       getNodeType() const override         { return _getNodeType(); }
    virtual XERCES::DOMNode *               getParentNode() const override       { return _getParentNode(); }
    virtual XERCES::DOMNodeList *           getChildNodes() const override       { return _getChildNodes(); }
    virtual XERCES::DOMNode *               getFirstChild() const override       { return _getFirstChild(); }
    virtual XERCES::DOMNode *               getLastChild() const override        { return _getLastChild(); }
    virtual XERCES::DOMNode *               getPreviousSibling() const override  { return _getPreviousSibling(); }
    virtual XERCES::DOMNode *               getNextSibling() const override      { return _getNextSibling(); }
    virtual XERCES::DOMNamedNodeMap *       getAttributes() const override       { return _getAttributes(); }
    virtual XERCES::DOMDocument *           getOwnerDocument() const override    { return _getOwnerDocument(); }
    virtual XERCES::DOMNode *               insertBefore(XERCES::DOMNode * newChild, XERCES::DOMNode * refChild) override { return _insertBefore(newChild, refChild); }
    virtual XERCES::DOMNode *               replaceChild(XERCES::DOMNode * newChild, XERCES::DOMNode * oldChild) override { return _replaceChild(newChild, oldChild); }
    virtual XERCES::DOMNode *               removeChild(XERCES::DOMNode * oldChild) override { return _removeChild(oldChild); }
    virtual XERCES::DOMNode *               appendChild(XERCES::DOMNode * newChild) override { return _appendChild(newChild); }
    virtual bool                            hasChildNodes() const override       { return _hasChildNodes(); }
    virtual void                            setNodeValue(const XERCES::XMLCh * v) override { _setNodeValue(v); }
    virtual const XERCES::XMLCh *           getLocalName() const override        { return _getLocalName(); }
    virtual bool                            hasAttributes() const override       { return _hasAttributes(); }
    virtual bool                            isSameNode(const XERCES::DOMNode * other) const override { return _isSameNode(other); }
    virtual const XERCES::XMLCh *           getTextContent() const override      { return _getTextContent(); }
    virtual XERCES::DOMNode *               cloneNode(bool) const override       { return nullptr; }
    virtual void                            normalize() override                 {}
    virtual bool                            isSupported(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return false; }
    virtual const XERCES::XMLCh *           getNamespaceURI() const override     { return nullptr; }
    virtual const XERCES::XMLCh *           getPrefix() const override           { return nullptr; }
    virtual void                            setPrefix(const XERCES::XMLCh *) override {}
    virtual bool                            isEqualNode(const XERCES::DOMNode *) const override { return false; }
    virtual void *                          setUserData(const XERCES::XMLCh *, void *, XERCES::DOMUserDataHandler *) override { return nullptr; }
    virtual void *                          getUserData(const XERCES::XMLCh *) const override { return nullptr; }
    virtual const XERCES::XMLCh *           getBaseURI() const override          { return nullptr; }
    virtual short                           compareDocumentPosition(const XERCES::DOMNode *) const override { return 0; }
    virtual void                            setTextContent(const XERCES::XMLCh *) override {}
    virtual const XERCES::XMLCh *           lookupPrefix(const XERCES::XMLCh *) const override { return nullptr; }
    virtual bool                            isDefaultNamespace(const XERCES::XMLCh *) const override { return false; }
    virtual const XERCES::XMLCh *           lookupNamespaceURI(const XERCES::XMLCh *) const override { return nullptr; }
    virtual void *                          getFeature(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return nullptr; }
    virtual void                            release() override                   {}

    // DOMElement methods implementations
    virtual const XERCES::XMLCh *   getTagName() const override;
    virtual const XERCES::XMLCh *   getAttribute(const XERCES::XMLCh * name) const override;
    virtual XERCES::DOMAttr *       getAttributeNode(const XERCES::XMLCh * name) const override;
    virtual XERCES::DOMNodeList *   getElementsByTagName(const XERCES::XMLCh * name) const override;
    virtual void                    setAttribute(const XERCES::XMLCh * name, const XERCES::XMLCh * value) override;
    virtual XERCES::DOMAttr *       setAttributeNode(XERCES::DOMAttr * newAttr) override;
    virtual XERCES::DOMAttr *       removeAttributeNode(XERCES::DOMAttr * oldAttr) override;
    virtual void                    removeAttribute(const XERCES::XMLCh * name) override;
    virtual bool                    hasAttribute(const XERCES::XMLCh * name) const override;

    // DOMElement methods stubs
    virtual const XERCES::XMLCh *   getAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return nullptr; }
    virtual void                    setAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *, const XERCES::XMLCh *) override {}
    virtual void                    removeAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *) override {}
    virtual XERCES::DOMAttr *       getAttributeNodeNS(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return nullptr; }
    virtual XERCES::DOMAttr *       setAttributeNodeNS(XERCES::DOMAttr *) override { return nullptr; }
    virtual XERCES::DOMNodeList *   getElementsByTagNameNS(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return nullptr; }
    virtual bool                    hasAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return false; }
    virtual void                    setIdAttribute(const XERCES::XMLCh *, bool) override {}
    virtual void                    setIdAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *, bool) override {}
    virtual void                    setIdAttributeNode(const XERCES::DOMAttr *, bool) override {}
};

#endif // DOMELEMENTADAPTER_H

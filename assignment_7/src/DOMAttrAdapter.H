#ifndef DOMATTRADAPTER_H
#define DOMATTRADAPTER_H

#include <xercesc/dom/DOMAttr.hpp>
#include "DOMNodeAdapter.H"
#include "Attr.H"

// Adapter Pattern: Adapter
class DOMAttrAdapter : public DOMNodeImplBase, public XERCES::DOMAttr
{
private:
    dom::Attr * _attrAdaptee;

public:
    explicit DOMAttrAdapter(dom::Attr * attr)
        : DOMNodeImplBase(attr), _attrAdaptee(attr) {}
    virtual ~DOMAttrAdapter() {}

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
    virtual XERCES::DOMNamedNodeMap *       getAttributes() const override       { return nullptr; }
    virtual XERCES::DOMDocument *           getOwnerDocument() const override    { return _getOwnerDocument(); }
    virtual XERCES::DOMNode *               insertBefore(XERCES::DOMNode * newChild, XERCES::DOMNode * refChild) override { return _insertBefore(newChild, refChild); }
    virtual XERCES::DOMNode *               replaceChild(XERCES::DOMNode * newChild, XERCES::DOMNode * oldChild) override { return _replaceChild(newChild, oldChild); }
    virtual XERCES::DOMNode *               removeChild(XERCES::DOMNode * oldChild) override { return _removeChild(oldChild); }
    virtual XERCES::DOMNode *               appendChild(XERCES::DOMNode * newChild) override { return _appendChild(newChild); }
    virtual bool                            hasChildNodes() const override       { return _hasChildNodes(); }
    virtual void                            setNodeValue(const XERCES::XMLCh * v) override { _setNodeValue(v); }
    virtual const XERCES::XMLCh *           getLocalName() const override        { return _getLocalName(); }
    virtual bool                            hasAttributes() const override       { return false; }
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

    // DOMAttr method implementations
    virtual const XERCES::XMLCh *   getName() const override;
    virtual const XERCES::XMLCh *   getValue() const override;
    virtual void                    setValue(const XERCES::XMLCh * value) override;
    virtual XERCES::DOMElement *    getOwnerElement() const override;

    // DOMAttr methods stubs
    virtual bool                    getSpecified() const override    { return true; }
    virtual bool                    isId() const override            { return false; }
};

#endif // DOMATTRADAPTER_H

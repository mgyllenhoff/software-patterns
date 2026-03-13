#ifndef DOMNODEADAPTER_H
#define DOMNODEADAPTER_H

#include <xercesc/dom/DOMNode.hpp>
#include "Node.H"

// Factory function
// Creates the appropriate adapter subclass based on node type
XERCES::DOMNode * createDOMNodeAdapter(dom::Node * node);

// Shared non-virtual base for all adapters. Holds the adaptee (dom::Node *)
// and provides protected helper methods that implement the DOMNode interface by
// delegating to the patterns_class DOM. Every adapter class inherits from this
// base so that child-management functions can recover the underlying dom::Node *
// from any XERCES::DOMNode * that is one of our adapters via getDomNode().
class DOMNodeImplBase
{
protected:
    dom::Node *     _adaptee;

    explicit DOMNodeImplBase(dom::Node * n) : _adaptee(n) {}

    // Shared DOMNode implementations (implemented in DOMNodeAdapter.C)
    const XERCES::XMLCh *           _getNodeName() const;
    const XERCES::XMLCh *           _getNodeValue() const;
    void                            _setNodeValue(const XERCES::XMLCh * v);
    XERCES::DOMNode::NodeType       _getNodeType() const;
    XERCES::DOMNode *               _getParentNode() const;
    XERCES::DOMNodeList *           _getChildNodes() const;
    XERCES::DOMNode *               _getFirstChild() const;
    XERCES::DOMNode *               _getLastChild() const;
    XERCES::DOMNode *               _getPreviousSibling() const;
    XERCES::DOMNode *               _getNextSibling() const;
    XERCES::DOMNamedNodeMap *       _getAttributes() const;
    XERCES::DOMDocument *           _getOwnerDocument() const;
    XERCES::DOMNode *               _insertBefore(XERCES::DOMNode * newChild, XERCES::DOMNode * refChild);
    XERCES::DOMNode *               _replaceChild(XERCES::DOMNode * newChild, XERCES::DOMNode * oldChild);
    XERCES::DOMNode *               _removeChild(XERCES::DOMNode * oldChild);
    XERCES::DOMNode *               _appendChild(XERCES::DOMNode * newChild);
    bool                            _hasChildNodes() const;
    const XERCES::XMLCh *           _getLocalName() const;
    bool                            _hasAttributes() const;
    bool                            _isSameNode(const XERCES::DOMNode * other) const;
    const XERCES::XMLCh *           _getTextContent() const;

public:
    virtual ~DOMNodeImplBase() {}

    dom::Node * getDomNode() const { return _adaptee; }
};


// Adapter Pattern: Adapter
class DOMNodeAdapter : public DOMNodeImplBase, public XERCES::DOMNode
{
public:
    explicit DOMNodeAdapter(dom::Node * n) : DOMNodeImplBase(n) {}
    virtual ~DOMNodeAdapter() {}

    // DOMNode pure virtual override implementations
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
    virtual void                            setNodeValue(const XERCES::XMLCh * nodeValue) override { _setNodeValue(nodeValue); }
    virtual const XERCES::XMLCh *           getLocalName() const override        { return _getLocalName(); }
    virtual bool                            hasAttributes() const override       { return _hasAttributes(); }
    virtual bool                            isSameNode(const XERCES::DOMNode * other) const override { return _isSameNode(other); }
    virtual const XERCES::XMLCh *           getTextContent() const override      { return _getTextContent(); }

    // DOMNode pure virtual override stubs
    virtual XERCES::DOMNode *   cloneNode(bool /*deep*/) const override             { return nullptr; }
    virtual void                normalize() override                                {}
    virtual bool                isSupported(const XERCES::XMLCh * /*feature*/, const XERCES::XMLCh * /*version*/) const override { return false; }
    virtual const XERCES::XMLCh * getNamespaceURI() const override                  { return nullptr; }
    virtual const XERCES::XMLCh * getPrefix() const override                        { return nullptr; }
    virtual void                setPrefix(const XERCES::XMLCh * /*prefix*/) override {}
    virtual bool                isEqualNode(const XERCES::DOMNode * /*arg*/) const override { return false; }
    virtual void *              setUserData(const XERCES::XMLCh * /*key*/, void * /*data*/, XERCES::DOMUserDataHandler * /*handler*/) override { return nullptr; }
    virtual void *              getUserData(const XERCES::XMLCh * /*key*/) const override { return nullptr; }
    virtual const XERCES::XMLCh * getBaseURI() const override                       { return nullptr; }
    virtual short               compareDocumentPosition(const XERCES::DOMNode * /*other*/) const override { return 0; }
    virtual void                setTextContent(const XERCES::XMLCh * /*textContent*/) override {}
    virtual const XERCES::XMLCh * lookupPrefix(const XERCES::XMLCh * /*namespaceURI*/) const override { return nullptr; }
    virtual bool                isDefaultNamespace(const XERCES::XMLCh * /*namespaceURI*/) const override { return false; }
    virtual const XERCES::XMLCh * lookupNamespaceURI(const XERCES::XMLCh * /*prefix*/) const override { return nullptr; }
    virtual void *              getFeature(const XERCES::XMLCh * /*feature*/, const XERCES::XMLCh * /*version*/) const override { return nullptr; }
    virtual void                release() override                                  {}
};

#endif // DOMNODEADAPTER_H

#ifndef DOMTEXTADAPTER_H
#define DOMTEXTADAPTER_H

#include <xercesc/dom/DOMText.hpp>
#include "DOMNodeAdapter.H"
#include "Text.H"

// Adapter Pattern: Adapter
class DOMTextAdapter : public DOMNodeImplBase, public XERCES::DOMText
{
private:
    dom::Text * _textAdaptee;

public:
    explicit DOMTextAdapter(dom::Text * text)
        : DOMNodeImplBase(text), _textAdaptee(text) {}
    virtual ~DOMTextAdapter() {}

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

    // DOMText method implementations
    virtual const XERCES::XMLCh *   getData() const override;
    virtual void                    setData(const XERCES::XMLCh * data) override;
    virtual XERCES::XMLSize_t       getLength() const override;
    virtual const XERCES::XMLCh *   substringData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count) const override;
    virtual void                    appendData(const XERCES::XMLCh * arg) override;
    virtual void                    insertData(XERCES::XMLSize_t offset, const XERCES::XMLCh * arg) override;
    virtual void                    deleteData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count) override;
    virtual void                    replaceData(XERCES::XMLSize_t offset, XERCES::XMLSize_t count, const XERCES::XMLCh * arg) override;
    virtual XERCES::DOMText *       splitText(XERCES::XMLSize_t offset) override;

    // DOMText method stubs
    virtual bool                    getIsElementContentWhitespace() const override { return false; }
    virtual const XERCES::XMLCh *   getWholeText() const override                 { return nullptr; }
    virtual XERCES::DOMText *       replaceWholeText(const XERCES::XMLCh *) override { return nullptr; }
};

#endif // DOMTEXTADAPTER_H

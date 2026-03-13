#ifndef DOMDOCUMENTADAPTER_H
#define DOMDOCUMENTADAPTER_H

#include <xercesc/dom/DOMDocument.hpp>
#include "DOMNodeAdapter.H"
#include "Document.H"

// Adapter Pattern: Adapter
class DOMDocumentAdapter : public DOMNodeImplBase, public XERCES::DOMDocument
{
private:
    dom::Document * _docAdaptee;

public:
    explicit DOMDocumentAdapter(dom::Document * doc)
        : DOMNodeImplBase(doc), _docAdaptee(doc) {}
    virtual ~DOMDocumentAdapter() {}

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
    virtual XERCES::DOMDocument *           getOwnerDocument() const override    { return nullptr; }
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

    // DOMDocument method implementations
    virtual XERCES::DOMElement *    createElement(const XERCES::XMLCh * tagName) override;
    virtual XERCES::DOMText *       createTextNode(const XERCES::XMLCh * data) override;
    virtual XERCES::DOMAttr *       createAttribute(const XERCES::XMLCh * name) override;
    virtual XERCES::DOMElement *    getDocumentElement() const override;

    // DOMDocument method stubs
    virtual XERCES::DOMDocumentFragment *       createDocumentFragment() override { return nullptr; }
    virtual XERCES::DOMComment *                createComment(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMCDATASection *           createCDATASection(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMProcessingInstruction *  createProcessingInstruction(const XERCES::XMLCh *, const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMEntityReference *        createEntityReference(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMDocumentType *           getDoctype() const override { return nullptr; }
    virtual XERCES::DOMImplementation *         getImplementation() const override { return nullptr; }
    virtual XERCES::DOMNodeList *               getElementsByTagName(const XERCES::XMLCh *) const override { return nullptr; }
    virtual XERCES::DOMNode *                   importNode(const XERCES::DOMNode *, bool) override { return nullptr; }
    virtual XERCES::DOMElement *                createElementNS(const XERCES::XMLCh *, const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMAttr *                   createAttributeNS(const XERCES::XMLCh *, const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMNodeList *               getElementsByTagNameNS(const XERCES::XMLCh *, const XERCES::XMLCh *) const override { return nullptr; }
    virtual XERCES::DOMElement *                getElementById(const XERCES::XMLCh *) const override { return nullptr; }
    virtual const XERCES::XMLCh *               getInputEncoding() const override { return nullptr; }
    virtual const XERCES::XMLCh *               getXmlEncoding() const override { return nullptr; }
    virtual bool                                getXmlStandalone() const override { return false; }
    virtual void                                setXmlStandalone(bool) override {}
    virtual const XERCES::XMLCh *               getXmlVersion() const override { return nullptr; }
    virtual void                                setXmlVersion(const XERCES::XMLCh *) override {}
    virtual const XERCES::XMLCh *               getDocumentURI() const override { return nullptr; }
    virtual void                                setDocumentURI(const XERCES::XMLCh *) override {}
    virtual bool                                getStrictErrorChecking() const override { return false; }
    virtual void                                setStrictErrorChecking(bool) override {}
    virtual XERCES::DOMNode *                   renameNode(XERCES::DOMNode *, const XERCES::XMLCh *, const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMNode *                   adoptNode(XERCES::DOMNode *) override { return nullptr; }
    virtual void                                normalizeDocument() override {}
    virtual XERCES::DOMConfiguration *          getDOMConfig() const override { return nullptr; }
    virtual XERCES::DOMEntity *                 createEntity(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMDocumentType *           createDocumentType(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMNotation *               createNotation(const XERCES::XMLCh *) override { return nullptr; }
    virtual XERCES::DOMElement *                createElementNS(const XERCES::XMLCh *, const XERCES::XMLCh *, const XERCES::XMLFileLoc, const XERCES::XMLFileLoc) override { return nullptr; }
};

#endif // DOMDOCUMENTADAPTER_H

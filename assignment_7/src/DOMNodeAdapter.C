#include "DOMNodeAdapter.H"
#include "DOMNodeListAdapter.H"
#include "DOMNamedNodeMapAdapter.H"
#include "DOMDocumentAdapter.H"
#include "DOMElementAdapter.H"
#include "DOMAttrAdapter.H"
#include "DOMTextAdapter.H"
#include "Element.H"

// Adapter Pattern: Adapter
XERCES::DOMNode * createDOMNodeAdapter(dom::Node * node)
{
    if (!node)
        return nullptr;

    switch (node->getNodeType())
    {
    case dom::Node::DOCUMENT_NODE:
        return new DOMDocumentAdapter(dynamic_cast<dom::Document *>(node));
    case dom::Node::ELEMENT_NODE:
        return new DOMElementAdapter(dynamic_cast<dom::Element *>(node));
    case dom::Node::ATTRIBUTE_NODE:
        return new DOMAttrAdapter(dynamic_cast<dom::Attr *>(node));
    case dom::Node::TEXT_NODE:
        return new DOMTextAdapter(dynamic_cast<dom::Text *>(node));
    default:
        return new DOMNodeAdapter(node);
    }
}

// Helper: extract dom::Node * from any XERCES::DOMNode * that is one of our adapters
static dom::Node * unwrap(XERCES::DOMNode * xNode)
{
    if (!xNode)
        return nullptr;
    DOMNodeImplBase * base = dynamic_cast<DOMNodeImplBase *>(xNode);
    return base ? base->getDomNode() : nullptr;
}

// DOMNodeImplBase shared implementations
const XERCES::XMLCh * DOMNodeImplBase::_getNodeName() const
{
    return _adaptee->getNodeName().c_str();
}

const XERCES::XMLCh * DOMNodeImplBase::_getNodeValue() const
{
    return _adaptee->getNodeValue().c_str();
}

void DOMNodeImplBase::_setNodeValue(const XERCES::XMLCh * v)
{
    _adaptee->setNodeValue(std::string(v));
}

XERCES::DOMNode::NodeType DOMNodeImplBase::_getNodeType() const
{
    // Map patterns_class node type constants to W3C / Xerces constants
    switch (_adaptee->getNodeType())
    {
    case dom::Node::ATTRIBUTE_NODE:  return XERCES::DOMNode::ATTRIBUTE_NODE;   // 0 → 2
    case dom::Node::DOCUMENT_NODE:   return XERCES::DOMNode::DOCUMENT_NODE;    // 1 → 9
    case dom::Node::ELEMENT_NODE:    return XERCES::DOMNode::ELEMENT_NODE;     // 2 → 1
    case dom::Node::TEXT_NODE:       return XERCES::DOMNode::TEXT_NODE;        // 3 → 3
    default:                         return static_cast<XERCES::DOMNode::NodeType>(_adaptee->getNodeType());
    }
}

XERCES::DOMNode * DOMNodeImplBase::_getParentNode() const
{
    return createDOMNodeAdapter(_adaptee->getParentNode());
}

XERCES::DOMNodeList * DOMNodeImplBase::_getChildNodes() const
{
    return new DOMNodeListAdapter(_adaptee->getChildNodes());
}

XERCES::DOMNode * DOMNodeImplBase::_getFirstChild() const
{
    return createDOMNodeAdapter(_adaptee->getFirstChild());
}

XERCES::DOMNode * DOMNodeImplBase::_getLastChild() const
{
    return createDOMNodeAdapter(_adaptee->getLastChild());
}

XERCES::DOMNode * DOMNodeImplBase::_getPreviousSibling() const
{
    return createDOMNodeAdapter(_adaptee->getPreviousSibling());
}

XERCES::DOMNode * DOMNodeImplBase::_getNextSibling() const
{
    return createDOMNodeAdapter(_adaptee->getNextSibling());
}

XERCES::DOMNamedNodeMap * DOMNodeImplBase::_getAttributes() const
{
    dom::Element * elem = dynamic_cast<dom::Element *>(_adaptee);
    if (!elem)
        return nullptr;
    return new DOMNamedNodeMapAdapter(elem->getAttributes());
}

XERCES::DOMDocument * DOMNodeImplBase::_getOwnerDocument() const
{
    dom::Document * doc = _adaptee->getOwnerDocument();
    if (!doc)
        return nullptr;
    return new DOMDocumentAdapter(doc);
}

XERCES::DOMNode * DOMNodeImplBase::_insertBefore(XERCES::DOMNode * newChild, XERCES::DOMNode * refChild)
{
    dom::Node * domNew = unwrap(newChild);
    dom::Node * domRef = unwrap(refChild);
    if (!domNew)
        return nullptr;
    return createDOMNodeAdapter(_adaptee->insertBefore(domNew, domRef));
}

XERCES::DOMNode * DOMNodeImplBase::_replaceChild(XERCES::DOMNode * newChild, XERCES::DOMNode * oldChild)
{
    dom::Node * domNew = unwrap(newChild);
    dom::Node * domOld = unwrap(oldChild);
    if (!domNew || !domOld)
        return nullptr;
    return createDOMNodeAdapter(_adaptee->replaceChild(domNew, domOld));
}

XERCES::DOMNode * DOMNodeImplBase::_removeChild(XERCES::DOMNode * oldChild)
{
    dom::Node * domOld = unwrap(oldChild);
    if (!domOld)
        return nullptr;
    return createDOMNodeAdapter(_adaptee->removeChild(domOld));
}

XERCES::DOMNode * DOMNodeImplBase::_appendChild(XERCES::DOMNode * newChild)
{
    dom::Node * domNew = unwrap(newChild);
    if (!domNew)
        return nullptr;
    return createDOMNodeAdapter(_adaptee->appendChild(domNew));
}

bool DOMNodeImplBase::_hasChildNodes() const
{
    return _adaptee->hasChildNodes();
}

const XERCES::XMLCh * DOMNodeImplBase::_getLocalName() const
{
    return _adaptee->getLocalName().c_str();
}

bool DOMNodeImplBase::_hasAttributes() const
{
    dom::Element * elem = dynamic_cast<dom::Element *>(_adaptee);
    return elem ? elem->hasAttributes() : false;
}

bool DOMNodeImplBase::_isSameNode(const XERCES::DOMNode * other) const
{
    if (!other)
        return false;
    const DOMNodeImplBase * base = dynamic_cast<const DOMNodeImplBase *>(other);
    return base ? (base->_adaptee == _adaptee) : false;
}

const XERCES::XMLCh * DOMNodeImplBase::_getTextContent() const
{
    // Delegate to node value for text/attr nodes
    // For elements return null (stub)
    return _adaptee->getNodeValue().c_str();
}

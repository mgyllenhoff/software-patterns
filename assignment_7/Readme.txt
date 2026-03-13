While Bridge and Adapter can both be used to separate an interface from an implementation using an intermediate class, they ultimately solve different 
design problems. The Bridge pattern solves the problem of when you have an abstraction that needs to vary independently from its implementation. It 
prevents creating all combinations of subclasses that would otherwise be required. On the other hand, the Adapter pattern solves the issue of two 
existing interfaces that are incompatible. It allows one interface to work where the other is expected without changing either. Object Adapter is also 
more flexible because it uses composition rather than inheritance, allowing it to adapt different subclasses of the adaptee.

In this assignment, both dom::Document and dom::Node are complete, pre-existing types. So are XERCES::DOMDocument and XERCES::DOMNode. We are not 
designing a new abstraction hierarchy, we are just getting pre-existing, incompatible ones to work together. That design issue more closely resembles 
the purpose of the Adapter pattern.

Bridge separates the Abstraction hierarchy from its Implementation hierarchy. There is no refined abstraction needed on the XERCES side.
XERCES::DOMDocument is the client-facing interface for the document level and XERCES::DOMNode is the client-facing interface for the node level. These
are the interfaces we want to expose, so there is nothing to refine (no need for a Refined Abstraction class).

Between the Object and Class approaches of the Adapter pattern, the Object approach becomes the obvious choice when considering the child management 
functions. They receive a XERCES::DOMNode* argument and must route it into dom::Node::appendChild(dom::Node*). This works cleanly with composition and 
getDomNode().

Class Adapter inherits from both XERCES::DOMNode and dom::Node to merge the two type hierarchies. When newChild arrives as XERCES::DOMNode*, especially 
if it comes from a different call chain, there is no reliable way to extract its underlying dom::Node*. Object Adapter instead holds a dom::Node* by 
composition (DOMNodeImplBase::_adaptee). Every adapter is a DOMNodeImplBase, so dynamic_cast<DOMNodeImplBase*>(newChild)->getDomNode() always recovers 
the underlying node regardless of which adapter subclass it is. 

Adapter Pattern Class Structure:
    Target: XERCES::DOMDocument, XERCES::DOMNode, XERCES::DOMElement, XERCES::DOMAttr, XERCES::DOMText, XERCES::DOMNodeList, XERCES::DOMNamedNodeMap
    Adapter: DOMDocumentAdapter, DOMNodeAdapter, DOMElementAdapter, DOMAttrAdapter, DOMTextAdapter, DOMNodeListAdapter, DOMNamedNodeMapAdapter
    Adaptee: dom::Document, dom::Node, dom::Element, dom::Attr, dom::Text, dom::NodeList, dom::NamedNodeMap

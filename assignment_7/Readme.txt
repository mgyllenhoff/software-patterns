While Bridge and Adapter can both be used to separate an interface from an implementation using an intermediate class, they ultimately solve different 
design problems. The Bridge pattern solves the problem of when you have an abstraction that needs to vary independently from its implementation. It 
prevents creating all combinations of subclasses that would otherwise be required. On the other hand, the Adapter pattern solves the issue of two 
existing interfaces that are incompatible. You can make one interface work where the other is expected, without changing either. Object Adapter is also 
more flexible since it can adapt any adoptee that implements the required interface, not just a specific subclass. 

In this assignment, both dom::Document and dom::Node are complete, pre-existing types. So are XERCES::DOMDocument and XERCES::DOMNode. We are not 
designing a new abstraction hierarchy, we are just getting pre-existing, incompatible ones to work together. That design issue more closely resembles 
the purpose of the Adapter pattern.

Bridge uses a Refined Abstraction class on top of the Abstraction class. There is no refined abstraction needed on the XERCES side. XERCES::DOMDocument 
is the client-facing interface for the document level, just as XERCES::DOMNode is the client-facing interface for the node level. Both are the 
interfaces we want to expose, so there is nothing to refine.

Between the Object and Class approaches of the Adapter pattern, the Object approach becomes the obvious choice when considering the child management 
functions. They receive a XERCES::DOMNode* argument and must route it into dom::Node::appendChild(dom::Node*). This works cleanly with composition and 
getDomNode().

Class Adapter inherits from both XERCES::DOMNode and dom::Node to merge the two type hierarchies. When newChild arrives as XERCES::DOMNode*, especially 
if it arrived from a different call chain, there is no clean way to extract its underlying dom::Node*. Object Adapter holds a dom::Node* by composition 
(DOMNodeImplBase::_adaptee). Every adapter IS-A DOMNodeImplBase, so dynamic_cast<DOMNodeImplBase*>(newChild)->getDomNode() always recovers the underlying 
node regardless of which adapter subclass it is. 

Adapter Pattern Class Structure:
    Target: XERCES::DOMDocument, XERCES::DOMNode, XERCES::DOMElement, XERCES::DOMAttr, XERCES::DOMText, XERCES::DOMNodeList, XERCES::DOMNamedNodeMap
    Adapter: DOMDocumentAdapter, DOMNodeAdapter, DOMElementAdapter, DOMAttrAdapter, DOMTextAdapter, DOMNodeListAdapter, DOMNamedNodeMapAdapter
    Adaptee: dom::Document, dom::Node, dom::Element, dom::Attr, dom::Text, dom::NodeList, dom::NamedNodeMap

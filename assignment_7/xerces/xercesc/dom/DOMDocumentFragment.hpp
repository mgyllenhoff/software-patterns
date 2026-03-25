#if !defined(XERCESC_INCLUDE_GUARD_DOMDOCUMENTFRAGMENT_HPP)
#define XERCESC_INCLUDE_GUARD_DOMDOCUMENTFRAGMENT_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMDocumentFragment : public DOMNode
{
protected:
    DOMDocumentFragment() {}
private:
    DOMDocumentFragment & operator=(const DOMDocumentFragment &);
public:
    virtual ~DOMDocumentFragment() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMDOCUMENTFRAGMENT_HPP

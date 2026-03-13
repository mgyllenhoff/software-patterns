#if !defined(XERCESC_INCLUDE_GUARD_DOMDOCUMENTTYPE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMDOCUMENTTYPE_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMDocumentType : public DOMNode
{
protected:
    DOMDocumentType() {}
private:
    DOMDocumentType & operator=(const DOMDocumentType &);
public:
    virtual ~DOMDocumentType() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMDOCUMENTTYPE_HPP

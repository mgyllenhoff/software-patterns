#if !defined(XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCE_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMEntityReference : public DOMNode
{
protected:
    DOMEntityReference() {}
private:
    DOMEntityReference & operator=(const DOMEntityReference &);
public:
    virtual ~DOMEntityReference() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCE_HPP

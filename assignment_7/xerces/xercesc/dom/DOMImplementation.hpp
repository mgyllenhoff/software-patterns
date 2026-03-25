#if !defined(XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATION_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMImplementation
{
protected:
    DOMImplementation() {}
private:
    DOMImplementation & operator=(const DOMImplementation &);
public:
    virtual ~DOMImplementation() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATION_HPP

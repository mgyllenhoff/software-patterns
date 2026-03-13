#if !defined(XERCESC_INCLUDE_GUARD_DOMNOTATION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNOTATION_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMNotation : public DOMNode
{
protected:
    DOMNotation() {}
private:
    DOMNotation & operator=(const DOMNotation &);
public:
    virtual ~DOMNotation() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMNOTATION_HPP

#if !defined(XERCESC_INCLUDE_GUARD_DOMCDATASECTION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCDATASECTION_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMCDATASection : public DOMNode
{
protected:
    DOMCDATASection() {}
private:
    DOMCDATASection & operator=(const DOMCDATASection &);
public:
    virtual ~DOMCDATASection() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMCDATASECTION_HPP

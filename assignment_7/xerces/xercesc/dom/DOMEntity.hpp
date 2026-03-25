#if !defined(XERCESC_INCLUDE_GUARD_DOMENTITY_HPP)
#define XERCESC_INCLUDE_GUARD_DOMENTITY_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMEntity : public DOMNode
{
protected:
    DOMEntity() {}
private:
    DOMEntity & operator=(const DOMEntity &);
public:
    virtual ~DOMEntity() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMENTITY_HPP

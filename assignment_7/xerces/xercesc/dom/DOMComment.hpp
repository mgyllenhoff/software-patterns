#if !defined(XERCESC_INCLUDE_GUARD_DOMCOMMENT_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCOMMENT_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMComment : public DOMNode
{
protected:
    DOMComment() {}
private:
    DOMComment & operator=(const DOMComment &);
public:
    virtual ~DOMComment() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMCOMMENT_HPP

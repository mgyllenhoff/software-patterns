#if !defined(XERCESC_INCLUDE_GUARD_DOMATTR_HPP)
#define XERCESC_INCLUDE_GUARD_DOMATTR_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMElement;
class DOMTypeInfo;

// Adapter Pattern: Target
class DOMAttr : public DOMNode
{
protected:
    DOMAttr() {}
    DOMAttr(const DOMAttr &) {}
private:
    DOMAttr & operator=(const DOMAttr &);
public:
    virtual ~DOMAttr() {}

    virtual const XMLCh *   getName() const = 0;
    virtual bool            getSpecified() const = 0;
    virtual const XMLCh *   getValue() const = 0;
    virtual void            setValue(const XMLCh *value) = 0;
    virtual DOMElement *    getOwnerElement() const = 0;
    virtual bool            isId() const = 0;
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMATTR_HPP

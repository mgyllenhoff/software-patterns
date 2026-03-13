#if !defined(XERCESC_INCLUDE_GUARD_DOMNODEFILTER_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNODEFILTER_HPP

namespace XERCES
{

class DOMNodeFilter
{
protected:
    DOMNodeFilter() {}
private:
    DOMNodeFilter & operator=(const DOMNodeFilter &);
public:
    virtual ~DOMNodeFilter() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMNODEFILTER_HPP

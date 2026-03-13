#if !defined(XERCESC_INCLUDE_GUARD_DOMNODELIST_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNODELIST_HPP

#include <cstddef>
#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

typedef std::size_t XMLSize_t;

// Adapter Pattern: Target
class DOMNodeList
{
protected:
    DOMNodeList() {}
    DOMNodeList(const DOMNodeList &) {}
private:
    DOMNodeList & operator=(const DOMNodeList &);
public:
    virtual ~DOMNodeList() {}

    virtual DOMNode *   item(XMLSize_t index) const = 0;
    virtual XMLSize_t   getLength() const = 0;
    virtual void        release() = 0;
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMNODELIST_HPP

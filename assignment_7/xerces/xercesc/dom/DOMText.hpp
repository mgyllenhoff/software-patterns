#if !defined(XERCESC_INCLUDE_GUARD_DOMTEXT_HPP)
#define XERCESC_INCLUDE_GUARD_DOMTEXT_HPP

#include <xercesc/dom/DOMNodeList.hpp>

namespace XERCES
{

// Adapter Pattern: Target
class DOMText : public DOMNode
{
protected:
    DOMText() {}
    DOMText(const DOMText &) {}
private:
    DOMText & operator=(const DOMText &);
public:
    virtual ~DOMText() {}

    virtual const XMLCh *   getData() const = 0;
    virtual XMLSize_t       getLength() const = 0;
    virtual const XMLCh *   substringData(XMLSize_t offset, XMLSize_t count) const = 0;
    virtual void            appendData(const XMLCh *arg) = 0;
    virtual void            insertData(XMLSize_t offset, const XMLCh *arg) = 0;
    virtual void            deleteData(XMLSize_t offset, XMLSize_t count) = 0;
    virtual void            replaceData(XMLSize_t offset, XMLSize_t count, const XMLCh *arg) = 0;
    virtual void            setData(const XMLCh *data) = 0;

    virtual DOMText *       splitText(XMLSize_t offset) = 0;
    virtual bool            getIsElementContentWhitespace() const = 0;
    virtual const XMLCh *   getWholeText() const = 0;
    virtual DOMText *       replaceWholeText(const XMLCh *content) = 0;
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMTEXT_HPP

#if !defined(XERCESC_INCLUDE_GUARD_DOMCONFIGURATION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCONFIGURATION_HPP

namespace XERCES
{

class DOMConfiguration
{
protected:
    DOMConfiguration() {}
private:
    DOMConfiguration & operator=(const DOMConfiguration &);
public:
    virtual ~DOMConfiguration() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMCONFIGURATION_HPP

#if !defined(XERCESC_INCLUDE_GUARD_DOMUSERDATAHANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_DOMUSERDATAHANDLER_HPP

namespace XERCES
{

class DOMUserDataHandler
{
protected:
    DOMUserDataHandler() {}
private:
    DOMUserDataHandler & operator=(const DOMUserDataHandler &);
public:
    virtual ~DOMUserDataHandler() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMUSERDATAHANDLER_HPP

#if !defined(XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTION_HPP)
#define XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTION_HPP

#include <xercesc/dom/DOMNode.hpp>

namespace XERCES
{

class DOMProcessingInstruction : public DOMNode
{
protected:
    DOMProcessingInstruction() {}
private:
    DOMProcessingInstruction & operator=(const DOMProcessingInstruction &);
public:
    virtual ~DOMProcessingInstruction() {}
};

};

#endif // XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTION_HPP

#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <string>
#include <fstream>
#include <ios>

#include "Node.H"
#include "NodeProcessor.H"

// Context
class XMLSerializer
{
private:
    std::fstream file;
    
	// Helper method that delegates to the strategy
    void serialize(dom::Node* node, NodeProcessor& processor);

public:
    XMLSerializer(const std::string & filename) 
        : file(filename.c_str(), std::ios_base::out) {}
    ~XMLSerializer() {}

    virtual void serializePretty(dom::Node * node);
    virtual void serializeMinimal(dom::Node * node);
};

#endif
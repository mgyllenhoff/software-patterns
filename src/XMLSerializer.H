#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <string>
#include <fstream>
#include <ios>
#include <ostream>

#include "Node.H"
#include "NodeProcessor.H"

// Context (for both Strategy patterns)
// Strategy Pattern 1 (Node Processing): NodeProcessor is the Strategy interface
// Strategy Pattern 2 (Output Stream): std::ostream is the Strategy interface
class XMLSerializer
{
private:
	std::fstream* ownedFile;

	// Strategy Pattern 2: Strategy (std::ostream)
	// ConcreteStrategies: std::cout, std::cerr, std::ofstream, std::ostringstream
	std::ostream& output;
    
    void serialize(dom::Node* node, NodeProcessor& processor);

public:
    XMLSerializer(std::ostream& out) 
        : ownedFile(nullptr), output(out) {}
    
    XMLSerializer(const std::string& filename) 
        : ownedFile(new std::fstream(filename.c_str(), std::ios_base::out)),
          output(*ownedFile) {}
    
    ~XMLSerializer() 
    {
        if (ownedFile != nullptr)
        {
            ownedFile->close();
            delete ownedFile;
        }
    }

    virtual void serializePretty(dom::Node * node);
    virtual void serializeMinimal(dom::Node * node);
};

#endif
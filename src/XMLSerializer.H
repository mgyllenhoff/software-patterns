#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <string>
#include <fstream>
#include <ios>
#include <ostream>

#include "Node.H"
#include "NodeProcessor.H"

// Context (for both strategy patterns)
class XMLSerializer
{
private:
	std::fstream* ownedFile;

	// Strategy (std::ostream)
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
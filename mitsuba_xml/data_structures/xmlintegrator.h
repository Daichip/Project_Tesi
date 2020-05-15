#ifndef XMLINTEGRATOR_H
#define XMLINTEGRATOR_H

#include <string>

namespace ms{

class XMLIntegrator
{
public:
    XMLIntegrator();

    // Methods
    inline void setType(std::string &newType) { mType = newType; }

    inline std::string& getType() { return mType; }

private:
    // Attributes
    std::string mType;
};

} // end namespace ms
#endif // XMLINTEGRATOR_H

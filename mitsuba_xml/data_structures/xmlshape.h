#ifndef XMLSHAPE_H
#define XMLSHAPE_H

#include <string>
#include <array>

#include "Eigen/Dense"

#include "mitsuba_xml/data_structures/xmlbsdf.h"


namespace ms{

class XMLShape
{
public:
    XMLShape();
    XMLShape(std::string shapeName, ms::XMLBsdf& bsdf );

    ~XMLShape();

    // Getters
    inline std::string& getShapeName() { return mShapeName; };
    inline ms::XMLBsdf& getBsdf() { return mBsdf; };

    // Setters
    inline void setShapeName(const std::string &shapeName) { mShapeName = shapeName; };
    inline void setBsdf(const ms::XMLBsdf &bsdf) { mBsdf = bsdf; };


private:
    std::string mShapeName;
    ms::XMLBsdf mBsdf;
};

} // end of namespace ms

#endif // XMLSHAPE_H

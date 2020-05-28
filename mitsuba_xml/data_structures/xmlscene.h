#ifndef XMLSCENE_H
#define XMLSCENE_H

#include <string>
#include <vector>

#include "mitsuba_xml/data_structures/xmlintegrator.h"
#include "mitsuba_xml/data_structures/xmlsensor.h"
#include "mitsuba_xml/data_structures/xmlshape.h"
#include "mitsuba_xml/data_structures/xmlbsdf.h"

namespace ms{

class XMLScene
{
public:
    XMLScene();
    XMLScene(ms::XMLSensor& sensor, ms::XMLIntegrator& integrator, std::vector<ms::XMLShape>& shapes);


    inline XMLIntegrator& integrator() { return mIntegrator; };
    inline XMLSensor& sensor() { return mSensor; };
    inline XMLBsdf& bsdf() { return mBsdf; } ;
    inline std::vector<XMLShape>& shapes() { return mShapes; } ;

    inline void setIntegrator(const XMLIntegrator &integrator) { mIntegrator = integrator; } ;
    inline void setSensor(const XMLSensor &sensor) { mSensor = sensor; } ;
    inline void setShapes(const std::vector<XMLShape> &shapes) { mShapes = shapes; } ;
    inline void setBsdf(const XMLBsdf &bsdf) { mBsdf = bsdf; };


private:
    // attributes
    std::string mSceneName;

    XMLIntegrator mIntegrator;
    XMLSensor mSensor;
    XMLBsdf mBsdf;
    std::vector<XMLShape> mShapes; // can have multiple shapes
};

} // end namespace ms
#endif // XMLSCENE_H

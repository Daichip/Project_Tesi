#ifndef XMLSCENE_H
#define XMLSCENE_H

#include <string>
#include <vector>

#include "mitsuba_xml/data_structures/xmlintegrator.h"
#include "mitsuba_xml/data_structures/xmlsensor.h"
#include "mitsuba_xml/data_structures/xmlshape.h"

namespace ms{

class XMLScene
{
public:
    XMLScene();

    inline XMLIntegrator& integrator() { return mIntegrator; };
    inline XMLSensor& sensor() { return mSensor; };
    inline std::vector<XMLShape>& shapes() { return mShapes; } ;

    inline void setIntegrator(const XMLIntegrator &integrator) { mIntegrator = integrator; } ;
    inline void setSensor(const XMLSensor &sensor) { mSensor = sensor; } ;
    inline void setShapes(const std::vector<XMLShape> &shapes) { mShapes = shapes; } ;

private:
    // attributes
    std::string mSceneName;

    XMLIntegrator mIntegrator;
    XMLSensor mSensor;
    std::vector<XMLShape> mShapes; // can have multiple shapes
};

} // end namespace ms
#endif // XMLSCENE_H

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
    XMLScene(ms::XMLSensor& sensor, ms::XMLIntegrator& integrator, std::vector<XMLBsdf>& bsdfs, std::vector<ms::XMLShape>& shapes);

    ~XMLScene();


    inline XMLIntegrator& getIntegrator() { return mIntegrator; };
    inline XMLSensor& getSensor() { return mSensor; };
    inline std::vector<XMLBsdf>& getBsdfs() { return mBsdfs; } ;
    inline std::vector<XMLShape>& getShapes() { return mShapes; } ;
    inline int getNumberOfShapesPresent() { return mNumberOfShapesPresent; }

    inline void setIntegrator(const XMLIntegrator &integrator) { mIntegrator = integrator; } ;
    inline void setSensor(const XMLSensor &sensor) { mSensor = sensor; } ;
    inline void setShapes(const std::vector<XMLShape> &shapes) { mShapes = shapes; } ;
    inline void setBsdfs(const std::vector<XMLBsdf> &bsdfv) { mBsdfs = bsdfv; };
    inline void addBsdf(XMLBsdf& bsdf) { mBsdfs.push_back(bsdf); };
    inline void addShape(XMLShape& shape) { mShapes.push_back(shape); };
    inline void setNumberOfShapesPresent(int nosp) { mNumberOfShapesPresent = nosp; };



private:
    // attributes
    std::string mSceneName;

    XMLIntegrator mIntegrator;
    XMLSensor mSensor;
    std::vector<XMLBsdf> mBsdfs;
    std::vector<XMLShape> mShapes; // can have multiple shapes

    int mNumberOfShapesPresent;
};

} // end namespace ms
#endif // XMLSCENE_H

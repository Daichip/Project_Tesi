#include "xmlscene.h"

ms::XMLScene::XMLScene():
    mIntegrator(XMLIntegrator()),
    mSensor(XMLSensor()),
    mShapes(std::vector<XMLShape> {XMLShape()})
{

}


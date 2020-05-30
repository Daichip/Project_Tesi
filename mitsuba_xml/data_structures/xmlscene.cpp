#include "xmlscene.h"

ms::XMLScene::XMLScene():
    mIntegrator(XMLIntegrator()),
    mSensor(XMLSensor()),
    mBsdfs(std::vector<XMLBsdf> {XMLBsdf()}),
    mShapes(std::vector<XMLShape> {XMLShape()})
{

}


ms::XMLScene::XMLScene(ms::XMLSensor& sensor,
                       ms::XMLIntegrator& integrator,
                       std::vector<XMLBsdf>& bsdfs,
                       std::vector<ms::XMLShape>& shapes):
    mIntegrator(integrator),
    mSensor(sensor),
    mBsdfs(bsdfs),
    mShapes(shapes)
{

}


ms::XMLScene::~XMLScene()
{
    mBsdfs.clear();
    mShapes.clear();
}

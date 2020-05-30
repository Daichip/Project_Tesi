#include "xmlshape.h"


ms::XMLShape::XMLShape():
    mShapeName("sphere"),
    mBsdf(ms::XMLBsdf())
{

}


ms::XMLShape::XMLShape(std::string shapeName, ms::XMLBsdf& bsdf):
    mShapeName(shapeName),
    mBsdf(bsdf)
{

}


ms::XMLShape::~XMLShape()
{

}

#include "xmlshape.h"

ms::XMLShape::XMLShape(std::string shapeName,
                       float bsdfAlpha, float bsdfIntIor, std::string bsdfDistribution, std::string bsdfId, std::string bsdfRGBName, std::string bsdfType, std::array<float, 3> bsdfRGBValue,
                       std::string bsdfTransformName, std::array<float, 3> bsdfTransformLAOrigin, std::array<float, 3> bsdfTransformLATarget, std::array<float, 3> bsdfTransformLAUp, std::array<float, 3> bsdfTransformTranslate):
    mShapeName(shapeName),
    mBsdfAlpha(bsdfAlpha),
    mBsdfIntIor(bsdfIntIor),
    mBsdfDistribution(bsdfDistribution),
    mBsdfId(bsdfId),
    mBsdfRGBName(bsdfRGBName),
    mBsdfType(bsdfType),
    mBsdfRGBValue(bsdfRGBValue),
    mBsdfTransformName(bsdfTransformName),
    mBsdfTransformLAOrigin(bsdfTransformLAOrigin),
    mBsdfTransformLATarget(bsdfTransformLATarget),
    mBsdfTransformLAUp(bsdfTransformLAUp),
    mBsdfTransformTranslate(bsdfTransformTranslate)
{

}


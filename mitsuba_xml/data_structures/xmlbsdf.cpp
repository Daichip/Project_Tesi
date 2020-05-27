#include "xmlbsdf.h"

ms::XMLBsdf::XMLBsdf():
    mBsdfAlpha(1.0),
    mBsdfIntIor(1.0),
    mBsdfDistribution("ggx"),
    mBsdfId("bsdfId"),
    mBsdfRGBName("radiance"),
    mBsdfType("roughplastic"),
    mBsdfRGBValue(std::array<float, 3> {13.25, 14.0, 14.0}),
    mBsdfTransformName("to_world"),
    mBsdfTransformLAOrigin(std::array<float, 3> {-1, -1, -1}),
    mBsdfTransformLATarget(std::array<float, 3> {-1, -1, -1}),
    mBsdfTransformLAUp(std::array<float, 3> {-1, -1, -1}),
    mBsdfTransformTranslate(std::array<float, 3> {-1, -1, -1})
{

}



ms::XMLBsdf::XMLBsdf(float bsdfAlpha, float bsdfIntIor,
                     std::string bsdfDistribution, std::string bsdfId, std::string bsdfRGBName, std::string bsdfType, std::string bsdfTransformName,
                     std::array<float, 3> bsdfRGBValue, std::array<float, 3> bsdfTransformLAOrigin, std::array<float, 3> bsdfTransformLATarget,
                     std::array<float, 3> bsdfTransformLAUp, std::array<float, 3> bsdfTransformTranslate):
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

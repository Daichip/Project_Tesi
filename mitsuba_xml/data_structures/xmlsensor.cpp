#include "xmlsensor.h"

ms::XMLSensor::XMLSensor():
    mNearClipValue(0.01),
    mFarClipValue(10000),
    mFocusDistance(0),
    mFov(45.0),
    mFovAxis("y"),
    mSensorType("perspective"),
    mTransformName("to_world"),
    mTransformTarget(std::array<float, 3> {0, 0, -1}),
    mTransformOrigin(std::array<float, 3> {0, 0, 0}),
    mTransformUp(std::array<float, 3> {0, 1, 0}),
    mTransformRot(std::array<float, 3> {0, 0, 0}),
    mSamplerName("independent"),
    mSampleCount(512),
    mFilmName("hdrfilm"),
    mFilmHeight(1080),
    mFilmWidth(1920),
    mFilterName("gaussian")
{
    std::cout << "Target: " << getTransformTarget()[0] << ", " << getTransformTarget()[1] <<  ", " << getTransformTarget()[2] << std::endl;
    std::cout << "Origin: " << getTransformOrigin()[0] << ", " << getTransformOrigin()[1] <<  ", " << getTransformOrigin()[2] << std::endl;
    std::cout << "Up: " << getTransformUp()[0] << ", " << getTransformUp()[1] <<  ", " << getTransformUp()[2] << std::endl;
}



ms::XMLSensor::XMLSensor(const float nearClipValue, const float farClipValue, const float focusDistance, const float fov,
                         const std::string &fovAxis, const std::string &transformationMatrix, const std::string &sensorName, const std::string &transformName,
                         const std::array<float, 3> &transformTarget, const std::array<float, 3> &transformOrigin, const std::array<float, 3> &transformUp, const std::array<float, 3> &transformRot,
                         const std::string &samplerName, const int sampleCount, const std::string &filmName,
                         const int filmHeight, const int filmWidth, const std::string &filterName) :
    mNearClipValue(nearClipValue),
    mFarClipValue(farClipValue),
    mFocusDistance(focusDistance),
    mFov(fov),
    mFovAxis(fovAxis),
    mSensorType(sensorName),
    mTransformName(transformName),
    mTransformTarget(transformTarget),
    mTransformOrigin(transformOrigin),
    mTransformUp(transformUp),
    mTransformRot(transformRot),
    mTransformationMatrix(transformationMatrix),
    mSamplerName(samplerName),
    mSampleCount(sampleCount),
    mFilmName(filmName),
    mFilmHeight(filmHeight),
    mFilmWidth(filmWidth),
    mFilterName(filterName)
{

}


ms::XMLSensor::~XMLSensor()
{

}


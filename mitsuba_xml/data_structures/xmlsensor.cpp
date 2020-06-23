#include "xmlsensor.h"

ms::XMLSensor::XMLSensor():
    mNearClipValue(0.01),
    mFarClipValue(10000),
    mFocusDistance(0),
    mFov(45.0),
    mFovAxis("y"),
    mSensorType("perspective"),
    mTransformName("to_world"),
    mTransformTarget(std::array<float, 3> {0, 0, 0}),
    mTransformOrigin(std::array<float, 3> {0, 0, 5}),
    mTransformUp(std::array<float, 3> {1, 0, 0}),
    mTransformRot(std::array<float, 3> {0, 0, 0}),
    mSamplerName("independent"),
    mSampleCount(128),
    mFilmName("hdrfilm"),
    mFilmHeight(1080),
    mFilmWidth(1920),
    mFilterName("gaussian")
{
    std::cout << "Target: " << getTransformTarget()[0] << ", " << getTransformTarget()[1] <<  ", " << getTransformTarget()[2] << std::endl;
    std::cout << "Origin: " << getTransformOrigin()[0] << ", " << getTransformOrigin()[1] <<  ", " << getTransformOrigin()[2] << std::endl;
    std::cout << "Up: " << getTransformUp()[0] << ", " << getTransformUp()[1] <<  ", " << getTransformUp()[2] << std::endl;
}



ms::XMLSensor::XMLSensor(float nearClipValue, float farClipValue, float focusDistance, float fov, std::string &fovAxis, std::string modelViewMatrix, std::string &sensorName, std::string &transformName,
                         std::array<float, 3> &transformTarget, std::array<float, 3> &transformOrigin, std::array<float, 3> &transformUp, std::array<float, 3> &transformRot,
                         std::string &samplerName, int sampleCount, std::string &filmName, int filmHeight, int filmWidth, std::string &filterName):
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
    mModelViewMatrix(modelViewMatrix),
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


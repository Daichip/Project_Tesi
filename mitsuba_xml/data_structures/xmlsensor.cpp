#include "xmlsensor.h"

ms::XMLSensor::XMLSensor():
    mNearClipValue(0.1),
    mFarClipValue(50.0),
    mFocusDistance(15.0),
    mFov(45.0),
    mFovAxis("x"),
    mSensorType("perspective"),
    mTransformName("to_world"),
    mTransformTarget(Eigen::Vector3d(0, 0, 0)),
    mTransformOrigin(Eigen::Vector3d(0, 0, 0)),
    mTransformUp(Eigen::Vector3d(0, 0, 0)),
    mSamplerName("independent"),
    mSampleCount(512),
    mFilmName("hdrfilm"),
    mFilmHeight(1080),
    mFilmWidth(1920),
    mFilterName("gaussian")
{

}



ms::XMLSensor::XMLSensor(float nearClipValue, float farClipValue, float focusDistance, float fov, std::string &fovAxis, std::string &sensorName, std::string &transformName, Eigen::Vector3d &transformTarget, Eigen::Vector3d &transformOrigin, Eigen::Vector3d &transformUp,
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
    mSamplerName(samplerName),
    mSampleCount(sampleCount),
    mFilmName(filmName),
    mFilmHeight(filmHeight),
    mFilmWidth(filmWidth),
    mFilterName(filterName)
{

}

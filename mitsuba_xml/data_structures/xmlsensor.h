#ifndef XMLSENSOR_H
#define XMLSENSOR_H

#include <string>
#include <array>
#include <iostream>

namespace ms{

class XMLSensor
{
public:
    XMLSensor();
    XMLSensor(float nearClipValue, float farClipValue, float focusDistance, float fov,
              std::string &fovAxis, std::string modelViewMatrix, std::string &sensorName, std::string &transformName,
              std::array<float, 3> &transformTarget, std::array<float, 3> &transformOrigin, std::array<float, 3> &transformUp, std::array<float, 3> &transformRot,
              std::string &samplerName, int sampleCount, std::string &filmName,
              int filmHeight, int filmWidth, std::string &filterName);

    ~XMLSensor();

    inline int getFilmHeight() const { return mFilmHeight; };
    inline int getFilmWidth() const { return mFilmWidth; };
    inline int getSampleCount() const { return mSampleCount; };
    inline float getFarClipValue() const { return mFarClipValue; };
    inline float getNearClipValue() const { return mNearClipValue; };
    inline float getFocusDistance() const { return mFocusDistance; };
    inline float getFov() const { return mFov; };
    inline std::string& getFovAxis() { return mFovAxis; };
    inline std::string& getFilmName() { return mFilmName; };
    inline std::string& getFilterName() { return mFilterName; };
    inline std::string& getSamplerName() { return mSamplerName; };
    inline std::string& getSensorType() { return mSensorType; };
    inline std::string& getTransformName() { return mTransformName; };
    inline std::string& getModelViewMatrix() { return mModelViewMatrix; };
    inline std::array<float, 3>& getTransformOrigin() { return mTransformOrigin; };
    inline std::array<float, 3>& getTransformTarget() { return mTransformTarget; };
    inline std::array<float, 3>& getTransformUp() { return mTransformUp; };
    inline std::array<float, 3> getTransformORot() { return mTransformORot; };
    inline std::array<float, 3>& getTransformRot() { return mTransformRot; };

    inline void setFarClipValue(float farClipValue) { mFarClipValue = farClipValue; };
    inline void setFilmHeight(int filmHeight) { mFilmHeight = filmHeight; };
    inline void setFilmName(const std::string &filmName) {mFilmName = filmName;} ;
    inline void setFilmWidth(int filmWidth) { mFilmWidth = filmWidth; } ;
    inline void setFilterName(const std::string &filterName) { mFilterName = filterName; };
    inline void setFocusDistance(float value) { mFocusDistance = value; };
    inline void setFov(float fov) { mFov = fov; };
    inline void setFovAxis(const std::string &fovAxis) { mFovAxis = fovAxis; } ;
    inline void setModelViewMatrix(const std::string& modelViewMatrix) { mModelViewMatrix = modelViewMatrix; };
    inline void setNearClipValue(float nearClipValue) { mNearClipValue = nearClipValue; };
    inline void setSampleCount(int sampleCount) {mSampleCount = sampleCount;} ;
    inline void setSamplerName(const std::string &samplerName) { mSamplerName = samplerName; };
    inline void setSensorName(const std::string &sensorName) { mSensorType = sensorName; };
    inline void setTransformName(const std::string &transformName) { mTransformName = transformName; };
    inline void setTransformOrigin(const std::array<float, 3> &transformOrigin) { mTransformOrigin = transformOrigin; };
    inline void setTransformTarget(const std::array<float, 3> &transformTarget) { mTransformTarget = transformTarget; };
    inline void setTransformUp(const std::array<float, 3> &transformUp) { mTransformUp = transformUp; };
    inline void setTransformRot(const std::array<float, 3> &transformRot) { mTransformRot = transformRot; };
    inline void setTransformORot(const std::array<float, 3> &transformORot) { mTransformORot = transformORot; };



private:
    // Attributes
    float mNearClipValue;
    float mFarClipValue;
    float mFocusDistance;
    float mFov;
    std::string mFovAxis;
    std::string mSensorType;
    std::string mTransformName;
    std::array<float, 3> mTransformTarget;
    std::array<float, 3> mTransformOrigin;
    std::array<float, 3> mTransformUp;
    std::array<float, 3> mTransformORot = {0, 0, 0};
    std::array<float, 3> mTransformRot;
    std::string mModelViewMatrix;
    std::string mSamplerName;
    int mSampleCount;
    std::string mFilmName;
    int mFilmHeight;
    int mFilmWidth;
    std::string mFilterName;
};

} // end of namespace ms

#endif // XMLSENSOR_H

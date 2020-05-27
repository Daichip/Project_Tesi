#ifndef XMLSENSOR_H
#define XMLSENSOR_H

#include <string>
#include "Eigen/Dense"

namespace ms{

class XMLSensor
{
public:
    XMLSensor();
    XMLSensor(float nearClipValue, float farClipValue, float focusDistance, float fov,
              std::string &fovAxis, std::string &sensorName, std::string &transformName,
              Eigen::Vector3d &transformTarget, Eigen::Vector3d &transformOrigin, Eigen::Vector3d &transformUp,
              std::string &samplerName, int sampleCount, std::string &filmName,
              int filmHeight, int filmWidth, std::string &filterName);

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
    inline Eigen::Vector3d& getTransformOrigin() { return mTransformOrigin; };
    inline Eigen::Vector3d& getTransformTarget() { return mTransformTarget; };
    inline Eigen::Vector3d& getTransformUp() { return mTransformUp; };

    inline void setFarClipValue(float farClipValue) { mFarClipValue = farClipValue; };
    inline void setFilmHeight(int filmHeight) { mFilmHeight = filmHeight; };
    inline void setFilmName(const std::string &filmName) {mFilmName = filmName;} ;
    inline void setFilmWidth(int filmWidth) { mFilmWidth = filmWidth; } ;
    inline void setFilterName(const std::string &filterName) { mFilterName = filterName; };
    inline void setFocusDistance(float value) { mFocusDistance = value; };
    inline void setFov(float fov) { mFov = fov; };
    inline void setFovAxis(const std::string &fovAxis) { mFovAxis = fovAxis; } ;
    inline void setNearClipValue(float nearClipValue) { mNearClipValue = nearClipValue; };
    inline void setSampleCount(int sampleCount) {mSampleCount = sampleCount;} ;
    inline void setSamplerName(const std::string &samplerName) { mSamplerName = samplerName; };
    inline void setSensorName(const std::string &sensorName) { mSensorType = sensorName; };
    inline void setTransformName(const std::string &transformName) { mTransformName = transformName; };
    inline void setTransformOrigin(const Eigen::Vector3d &transformOrigin) { mTransformOrigin = transformOrigin; };
    inline void setTransformTarget(const Eigen::Vector3d &transformTarget) { mTransformTarget = transformTarget; };
    inline void setTransformUp(const Eigen::Vector3d &transformUp) { mTransformUp = transformUp; };

private:
    // Attributes
    float mNearClipValue;
    float mFarClipValue;
    float mFocusDistance;
    float mFov;
    std::string mFovAxis;
    std::string mSensorType;
    std::string mTransformName;
    Eigen::Vector3d mTransformTarget;
    Eigen::Vector3d mTransformOrigin;
    Eigen::Vector3d mTransformUp;
    std::string mSamplerName;
    int mSampleCount;
    std::string mFilmName;
    int mFilmHeight;
    int mFilmWidth;
    std::string mFilterName;
};

} // end of namespace ms

#endif // XMLSENSOR_H

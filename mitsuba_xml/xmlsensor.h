#ifndef XMLSENSOR_H
#define XMLSENSOR_H

#include <string>
#include "Eigen/Dense"

namespace ms{

class XMLSensor
{
public:
    XMLSensor();
    XMLSensor(float nearClipValue, float farClipValue, float focusDistance, float fov, std::string &fovAxis, std::string &sensorName, std::string &transformName, Eigen::Vector3d &transformTarget, Eigen::Vector3d &transformOrigin, Eigen::Vector3d &transformUp,
              std::string &samplerName, int sampleCount, std::string &filmName, int filmHeight, int filmWidth, std::string &filterName);

    inline int filmHeight() const { return mFilmHeight; };
    inline int filmWidth() const { return mFilmWidth; };
    inline int sampleCount() const { return mSampleCount; };
    inline float farClipValue() const { return mFarClipValue; };
    inline float nearClipValue() const { return mNearClipValue; };
    inline float getFocusDistance() const { return mFocusDistance; };
    inline float getFov() const { return mFov; };
    inline std::string getFovAxis() const { return mFovAxis; };
    inline std::string filmName() const { return mFilmName; };
    inline std::string filterName() const { return mFilterName; };
    inline std::string samplerName() const { return mSamplerName; };
    inline std::string sensorName() const { return mSensorName; };
    inline std::string transformName() const { return mTransformName; };
    inline Eigen::Vector3d transformOrigin() const { return mTransformOrigin; };
    inline Eigen::Vector3d transformTarget() const { return mTransformTarget; };
    inline Eigen::Vector3d transformUp() const { return mTransformUp; };

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
    inline void setSensorName(const std::string &sensorName) { mSensorName = sensorName; };
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
    std::string mSensorName;
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

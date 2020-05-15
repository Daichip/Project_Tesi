#ifndef XMLSHAPE_H
#define XMLSHAPE_H

#include <string>
#include <array>

#include "Eigen/Dense"


namespace ms{

class XMLShape
{
public:
    XMLShape(std::string shapeName,
             float bsdfAlpha, float bsdfIntIor, std::string bsdfDistribution, std::string bsdfId, std::string bsdfRGBName, std::string bsdfType, std::array<float, 3> bsdfRGBValue,
             std::string bsdfTransformName, std::array<float, 3> bsdfTransformLAOrigin, std::array<float, 3> bsdfTransformLATarget, std::array<float, 3> bsdfTransformLAUp, std::array<float, 3> bsdfTransformTranslate);


    inline std::string shapeName() const { return mShapeName; };
    // BSDF
    inline float bsdfAlpha() const { return mBsdfAlpha; };
    inline float bsdfIntIor() const { return mBsdfIntIor; };
    inline std::string bsdfDistribution() const { return mBsdfDistribution; };
    inline std::string bsdfId() const { return mBsdfId; };
    inline std::string bsdfRGBName() const { return mBsdfRGBName; };
    inline std::string bsdfType() const { return mBsdfType; };
    inline std::array<float, 3> bsdfRGBValue() const { return mBsdfRGBValue; };
    // BSDF Transform
    inline std::string bsdfTransformName() const { return mBsdfTransformName; };
    inline std::array<float, 3>& bsdfTransformLAOrigin() { return mBsdfTransformLAOrigin; };
    inline std::array<float, 3>& bsdfTransformLATarget() { return mBsdfTransformLATarget; };
    inline std::array<float, 3>& bsdfTransformLAUp() { return mBsdfTransformLAUp; };
    inline std::array<float, 3>& bsdfTransformTranslate() { return mBsdfTransformTranslate; };


    inline void setShapeName(const std::string &shapeName);
    // BSDF
    inline void setBsdfAlpha(float bsdfAlpha);
    inline void setBsdfIntIor(float bsdfIntIor);
    inline void setBsdfDistribution(const std::string &bsdfDistribution);
    inline void setBsdfId(const std::string &bsdfId);
    inline void setBsdfRGBName(const std::string &bsdfRGBName);
    inline void setBsdfRGBValue(const std::array<float, 3> &bsdfRGBValue);
    inline void setBsdfType(const std::string &bsdfType);
    // BSDF Transform
    inline void setBsdfTransformName(const std::string &bsdfTransformName);
    inline void setBsdfTransformLAOrigin(const std::array<float, 3> &bsdfTransformLAOrigin);
    inline void setBsdfTransformLATarget(const std::array<float, 3> &bsdfTransformLATarget);
    inline void setBsdfTransformLAUp(const std::array<float, 3> &bsdfTransformLAUp);
    inline void setBsdfTransformTranslate(const std::array<float, 3> &bsdfTransformTranslate);

private:
    std::string mShapeName;
    // BSDF
    float mBsdfAlpha; // es: 0.1
    float mBsdfIntIor; // es: 1.5
    std::string mBsdfDistribution; // es: ggx
    std::string mBsdfId;
    std::string mBsdfRGBName; // es: diffuse_reflectance
    std::string mBsdfType;
    std::array<float, 3> mBsdfRGBValue; // es: 0.1, 0.1, 0.75
    // BSDF TRANSFORM
    std::string mBsdfTransformName;
    std::array<float, 3> mBsdfTransformLAOrigin;
    std::array<float, 3> mBsdfTransformLATarget;
    std::array<float, 3> mBsdfTransformLAUp;
    std::array<float, 3> mBsdfTransformTranslate;
//    std::string mBsdfTransformRotateAxis;

    //TODO: implement rotation



};

} // end of namespace ms

#endif // XMLSHAPE_H

#ifndef XMLBSDF_H
#define XMLBSDF_H

#include <string>
#include <array>

namespace ms{

class XMLBsdf
{
public:
    XMLBsdf();
    XMLBsdf(float bsdfAlpha, float bsdfIntIor,
            std::string bsdfDistribution, std::string bsdfId, std::string bsdfRGBName, std::string bsdfType, std::string bsdfTransformName,
            std::array<float, 3> bsdfRGBValue, std::array<float, 3> bsdfTransformLAOrigin, std::array<float, 3> bsdfTransformLATarget,
            std::array<float, 3> bsdfTransformLAUp, std::array<float, 3> bsdfTransformTranslate);

    // BSDF
    inline float getAlpha() const { return mBsdfAlpha; };
    inline float getIntIor() const { return mBsdfIntIor; };
    inline std::string getDistribution() const { return mBsdfDistribution; };
    inline std::string getId() const { return mBsdfId; };
    inline std::string getRGBName() const { return mBsdfRGBName; };
    inline std::string getType() const { return mBsdfType; };
    inline std::array<float, 3> getBsdfRGBValue() const { return mBsdfRGBValue; };
    // BSDF Transform
    inline std::string getTransformName() const { return mBsdfTransformName; };
    inline std::array<float, 3>& getTransformLAOrigin() { return mBsdfTransformLAOrigin; };
    inline std::array<float, 3>& getTransformLATarget() { return mBsdfTransformLATarget; };
    inline std::array<float, 3>& getTransformLAUp() { return mBsdfTransformLAUp; };
    inline std::array<float, 3>& getTransformTranslate() { return mBsdfTransformTranslate; };


    // BSDF
    inline void setAlpha(float bsdfAlpha);
    inline void setIntIor(float bsdfIntIor);
    inline void setDistribution(const std::string &bsdfDistribution);
    inline void setId(const std::string &bsdfId);
    inline void setRGBName(const std::string &bsdfRGBName);
    inline void setRGBValue(const std::array<float, 3> &bsdfRGBValue);
    inline void setType(const std::string &bsdfType);
    // BSDF Transform
    inline void setTransformName(const std::string &bsdfTransformName);
    inline void setTransformLAOrigin(const std::array<float, 3> &bsdfTransformLAOrigin);
    inline void setTransformLATarget(const std::array<float, 3> &bsdfTransformLATarget);
    inline void setTransformLAUp(const std::array<float, 3> &bsdfTransformLAUp);
    inline void setTransformTranslate(const std::array<float, 3> &bsdfTransformTranslate);



private:
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


    //TODO: implement rotation
    //    std::string mBsdfTransformRotateAxis;
};

} // end of namespace ms

#endif // XMLBSDF_H

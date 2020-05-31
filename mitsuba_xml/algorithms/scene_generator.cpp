#include "mitsuba_xml/algorithms/scene_generator.h"

//***********************************************************************************************
void eigenMatToString(std::ostringstream& vts, Eigen::Vector3d& mat)
{
    std::vector<float> vec;
    vec.push_back(mat[0]);
    vec.push_back(mat[1]);
    vec.push_back(mat[2]);


    if (!vec.empty())
      {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
            std::ostream_iterator<float>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
      }

//      std::cout << vts.str() << std::endl;
}

void arrayToString(std::ostringstream& vts, std::array<float, 3> arr)
{
    std::vector<float> vec;
    vec.push_back(arr[0]);
    vec.push_back(arr[1]);
    vec.push_back(arr[2]);


    if (!vec.empty())
      {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
            std::ostream_iterator<float>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
      }

//      std::cout << vts.str() << std::endl;
}




//***********************************************************************************************

void ms::generateScene()
{
    // Step 0: create the new XML file
    TiXmlDocument doc;
    TiXmlDeclaration decl( "1.0", "utf-8", "" ); // Create the declaration [XML Version and encoding]

    // Step 1: create the scene
    TiXmlElement dScene("scene");
    dScene.SetAttribute("version", "2.0.0");

    // Step 2: set up the integrator and the sensor
    // Integrator
    TiXmlElement dIntegrator("integrator");
    dIntegrator.SetAttribute("type", "path");

    // Sensor
    TiXmlElement dSensor("sensor");
    dSensor.SetAttribute("type", "perspective");

    // Sensor - Far Clip
    TiXmlElement dSensorFarClip("float");
    dSensorFarClip.SetAttribute("name", "far_clip");
    dSensorFarClip.SetAttribute("value", "55.0");

    // Sensor - Near Clip
    TiXmlElement dSensorNearClip("float");
    dSensorNearClip.SetAttribute("name", "near_clip");
    dSensorNearClip.SetAttribute("value", "0.1");

    // Sensor - Focus Distance
    TiXmlElement dSensorFocusDistance("float");
    dSensorFocusDistance.SetAttribute("name", "focus_distance");
    dSensorFocusDistance.SetAttribute("value", "15.0");

    // Sensor - Fov
    TiXmlElement dSensorFov("float");
    dSensorFov.SetAttribute("name", "fov");
    dSensorFov.SetAttribute("value", "45.0");

    // Sensor - Fov Axis
    TiXmlElement dSensorFovAxis("string");
    dSensorFovAxis.SetAttribute("name", "fov_axis");
    dSensorFovAxis.SetAttribute("value", "x");

    // Sensor - Transform
    TiXmlElement dSensorTransform("transform");
    dSensorTransform.SetAttribute("name", "to_world");

    // Sensor - Transform - LookAt
    TiXmlElement dSensorTransformLA("lookat");
    dSensorTransformLA.SetAttribute("target", "0, 2.75, -13.8");
    dSensorTransformLA.SetAttribute("origin", "0, 2.75, -14.8");
    dSensorTransformLA.SetAttribute("up", "0, 1, 0");

    // Sensor - Sampler
    TiXmlElement dSensorSampler("sampler");
    dSensorSampler.SetAttribute("type", "independent");

    // Sensor - Sampler - Sample Count
    TiXmlElement dSensorSamplerSC("integer");
    dSensorSamplerSC.SetAttribute("name", "sample_count");
    dSensorSamplerSC.SetAttribute("value", "512");

    // Sensor - Film
    TiXmlElement dSensorFilm("film");
    dSensorFilm.SetAttribute("type", "hdrfilm");

    // Sensor - Film - Height
    TiXmlElement dSensorFilmH("integer");
    dSensorFilmH.SetAttribute("name", "height");
    dSensorFilmH.SetAttribute("value", "1080");

    // Sensor - Film - Width
    TiXmlElement dSensorFilmW("integer");
    dSensorFilmW.SetAttribute("name", "width");
    dSensorFilmW.SetAttribute("value", "1920");

    // Sensor - Film - Filter
    TiXmlElement dSensorFilmFilter("rfilter");
    dSensorFilmFilter.SetAttribute("type", "gaussian");
    // Step 2: Add the shapes
    // Define the materials
    // BSDF - Rough Plastic
    TiXmlElement dBsdfRoughPlastic("bsdf");
    dBsdfRoughPlastic.SetAttribute("type", "roughplastic");
    dBsdfRoughPlastic.SetAttribute("id", "bsdfroughplastic");

    // BSDF - Rough Plastic - GGX Distribution
    TiXmlElement dBsdfRoughPlasticGGXDist("string");
    dBsdfRoughPlasticGGXDist.SetAttribute("name", "distribution");
    dBsdfRoughPlasticGGXDist.SetAttribute("value", "ggx");

    // BSDF - Rough Plastic - Alpha
    TiXmlElement dBsdfRoughPlasticAlpha("float");
    dBsdfRoughPlasticAlpha.SetAttribute("name", "alpha");
    dBsdfRoughPlasticAlpha.SetAttribute("value", "0.1");
    // BSDF - Rough Plastic - Int IoR
    TiXmlElement dBsdfRoughPlasticIor("float");
    dBsdfRoughPlasticIor.SetAttribute("name", "int_ior");
    dBsdfRoughPlasticIor.SetAttribute("value", "1.5");

    // BSDF - Rough Plastic - RGB
    TiXmlElement dBsdfRoughPlasticRgb("rgb");
    dBsdfRoughPlasticRgb.SetAttribute("name", "diffuse_reflectance");
    dBsdfRoughPlasticRgb.SetAttribute("value", "0.1, 0.1, 0.75");

    // Shapes
    TiXmlElement dShape("shape");
    dShape.SetAttribute("type", "sphere");

    // Shape - Sphere Obj - Center
    TiXmlElement dShapePoint("point");
    dShapePoint.SetAttribute("name", "center");
    dShapePoint.SetAttribute("x", "0");
    dShapePoint.SetAttribute("y", "2");
    dShapePoint.SetAttribute("z", "0");

    // Shape - BSDF Reference
    TiXmlElement dBsdfRef("ref");
    dBsdfRef.SetAttribute("name", "bsdf");
    dBsdfRef.SetAttribute("id", "bsdfroughplastic");

    // Shape - Sphere Light
    TiXmlElement dShapeEmit("shape");
    dShapeEmit.SetAttribute("type", "sphere");

    // Shape - Sphere Light - Center
    TiXmlElement dShapeEPoint("point");
    dShapeEPoint.SetAttribute("name", "center");
    dShapeEPoint.SetAttribute("x", "0");
    dShapeEPoint.SetAttribute("y", "7");
    dShapeEPoint.SetAttribute("z", "0");

    // Test - Sphere Light - Emitter
    TiXmlElement dEmitter("emitter");
    dEmitter.SetAttribute("type", "area");

    // Test - Sphere Light - Emitter - Spectrum
    TiXmlElement dEmitterSpectrum("spectrum");
    dEmitterSpectrum.SetAttribute("name", "radiance");
    dEmitterSpectrum.SetAttribute("value", "1");



    // Step 4: add all elements
    doc.InsertEndChild(decl); // Add the declaration to the document


    dSensorSampler.InsertEndChild(dSensorSamplerSC);

    dSensorTransform.InsertEndChild(dSensorTransformLA);

    dSensorFilm.InsertEndChild(dSensorFilmH);
    dSensorFilm.InsertEndChild(dSensorFilmW);
    dSensorFilm.InsertEndChild(dSensorFilmFilter);

    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticGGXDist);
    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticAlpha);
    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticIor);
    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticRgb);

    dSensor.InsertEndChild(dSensorFarClip);
    dSensor.InsertEndChild(dSensorNearClip);
    dSensor.InsertEndChild(dSensorFocusDistance);
    dSensor.InsertEndChild(dSensorFov);
    dSensor.InsertEndChild(dSensorFovAxis);
    dSensor.InsertEndChild(dSensorTransform);
    dSensor.InsertEndChild(dSensorFilm);
    dSensor.InsertEndChild(dSensorSampler);


    dEmitter.InsertEndChild(dEmitterSpectrum);
    dShapeEmit.InsertEndChild(dShapeEPoint);
    dShapeEmit.InsertEndChild(dEmitter);

    dShape.InsertEndChild(dShapePoint);
    dShape.InsertEndChild(dBsdfRef);

    dScene.InsertEndChild(dBsdfRoughPlastic);
    dScene.InsertEndChild(dSensor);
    dScene.InsertEndChild(dIntegrator);
    dScene.InsertEndChild(dShapeEmit);
    dScene.InsertEndChild(dShape);

    doc.InsertEndChild(dScene);

    // Step 5: save the XML document
    try {
        std::system("mkdir $HOME/SavedScene");
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }

//    doc.SaveFile("$HOME/SavedScene/Project_Tesi_Scene.xml");

    doc.SaveFile("/home/dfara/SavedScene/Project_Tesi_Scene.xml");
}

void ms::generateScene(ms::XMLScene& scene, std::string filename)
{
    // Step 0: create the new XML file
    TiXmlDocument doc;
    TiXmlDeclaration decl( "1.0", "utf-8", "" ); // Create the declaration [XML Version and encoding]

    // Step 1: create the scene
    TiXmlElement dScene("scene");
    dScene.SetAttribute("version", "2.0.0");

    // Step 2: set up the integrator and the sensor
    // Integrator
    TiXmlElement dIntegrator("integrator");
    dIntegrator.SetAttribute("type", scene.getIntegrator().getType());

    // Sensor
    TiXmlElement dSensor("sensor");
    dSensor.SetAttribute("type", scene.getSensor().getSensorType());

    // Sensor - Far Clip
    TiXmlElement dSensorFarClip("float");
    dSensorFarClip.SetAttribute("name", "far_clip");
    dSensorFarClip.SetAttribute("value", scene.getSensor().getFarClipValue());

    // Sensor - Near Clip
    TiXmlElement dSensorNearClip("float");
    dSensorNearClip.SetAttribute("name", "near_clip");
    dSensorNearClip.SetAttribute("value", scene.getSensor().getNearClipValue());

    // Sensor - Focus Distance
    TiXmlElement dSensorFocusDistance("float");
    dSensorFocusDistance.SetAttribute("name", "focus_distance");
    dSensorFocusDistance.SetAttribute("value", scene.getSensor().getFocusDistance());

    // Sensor - Fov
    TiXmlElement dSensorFov("float");
    dSensorFov.SetAttribute("name", "fov");
    dSensorFov.SetAttribute("value", scene.getSensor().getFov());

    // Sensor - Fov Axis
    TiXmlElement dSensorFovAxis("string");
    dSensorFovAxis.SetAttribute("name", "fov_axis");
    dSensorFovAxis.SetAttribute("value", scene.getSensor().getFovAxis());

    // Sensor - Transform
    TiXmlElement dSensorTransform("transform");
    dSensorTransform.SetAttribute("name", scene.getSensor().getTransformName());

    // Sensor - Transform - LookAt
    TiXmlElement dSensorTransformLA("lookat");
    std::ostringstream vts;
    eigenMatToString(vts, scene.getSensor().getTransformTarget());
    dSensorTransformLA.SetAttribute("target", vts.str());

    eigenMatToString(vts, scene.getSensor().getTransformOrigin());
    dSensorTransformLA.SetAttribute("origin", vts.str());

    eigenMatToString(vts, scene.getSensor().getTransformUp());
    dSensorTransformLA.SetAttribute("up", vts.str());

    // Sensor - Sampler
    TiXmlElement dSensorSampler("sampler");
    dSensorSampler.SetAttribute("type", "independent");

    // Sensor - Sampler - Sample Count
    TiXmlElement dSensorSamplerSC("integer");
    dSensorSamplerSC.SetAttribute("name", "sample_count");
    dSensorSamplerSC.SetAttribute("value", scene.getSensor().getSampleCount());

    // Sensor - Film
    TiXmlElement dSensorFilm("film");
    dSensorFilm.SetAttribute("type", "hdrfilm");

    // Sensor - Film - Height
    TiXmlElement dSensorFilmH("integer");
    dSensorFilmH.SetAttribute("name", "height");
    dSensorFilmH.SetAttribute("value", scene.getSensor().getFilmHeight());

    // Sensor - Film - Width
    TiXmlElement dSensorFilmW("integer");
    dSensorFilmW.SetAttribute("name", "width");
    dSensorFilmW.SetAttribute("value", scene.getSensor().getFilmWidth());

    // Sensor - Film - Filter
    TiXmlElement dSensorFilmFilter("rfilter");
    dSensorFilmFilter.SetAttribute("type", scene.getSensor().getFilterName());

    // Step 2: Add the shapes

    // Define the materials
    // BSDF - Rough Plastic
    std::vector<TiXmlElement> xmlBsdfs;
    for(XMLBsdf& bsdf : scene.getBsdfs())
    {
        TiXmlElement dBsdfRoughPlastic("bsdf");
        dBsdfRoughPlastic.SetAttribute("type", bsdf.getType());
        dBsdfRoughPlastic.SetAttribute("id", bsdf.getId());

        // BSDF - Rough Plastic - GGX Distribution
        TiXmlElement dBsdfRoughPlasticGGXDist("string");
        dBsdfRoughPlasticGGXDist.SetAttribute("name", "distribution");
        dBsdfRoughPlasticGGXDist.SetAttribute("value", bsdf.getDistribution());

        // BSDF - Rough Plastic - Alpha
        TiXmlElement dBsdfRoughPlasticAlpha("float");
        dBsdfRoughPlasticAlpha.SetAttribute("name", "alpha");
        dBsdfRoughPlasticAlpha.SetAttribute("value", bsdf.getAlpha());
        // BSDF - Rough Plastic - Int IoR
        TiXmlElement dBsdfRoughPlasticIor("float");
        dBsdfRoughPlasticIor.SetAttribute("name", "int_ior");
        dBsdfRoughPlasticIor.SetAttribute("value", bsdf.getIntIor());

        // BSDF - Rough Plastic - RGB
        TiXmlElement dBsdfRoughPlasticRgb("rgb");
        dBsdfRoughPlasticRgb.SetAttribute("name", bsdf.getRGBName());
        arrayToString(vts, bsdf.getBsdfRGBValue());
        dBsdfRoughPlasticRgb.SetAttribute("value", vts.str());

        dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticGGXDist);
        dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticAlpha);
        dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticIor);
        dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticRgb);

        xmlBsdfs.push_back(dBsdfRoughPlastic);
    }

    // Shape - Sphere Light
    TiXmlElement dShapeEmit("shape");
    dShapeEmit.SetAttribute("type", "sphere");

    // Shape - Sphere Light - Center
    TiXmlElement dShapeEPoint("point");
    dShapeEPoint.SetAttribute("name", "center");
    dShapeEPoint.SetAttribute("x", "0");
    dShapeEPoint.SetAttribute("y", "7");
    dShapeEPoint.SetAttribute("z", "0");

    // Test - Sphere Light - Emitter
    TiXmlElement dEmitter("emitter");
    dEmitter.SetAttribute("type", "area");

    // Test - Sphere Light - Emitter - Spectrum
    TiXmlElement dEmitterSpectrum("spectrum");
    dEmitterSpectrum.SetAttribute("name", "radiance");
    dEmitterSpectrum.SetAttribute("value", "1");

    // Shapes
//    for(ms::XMLShape& shape : scene.shapes())
//    {

//    }
    TiXmlElement dShape("shape");
    dShape.SetAttribute("type", "sphere");

    // Shape - Sphere Obj - Center
    TiXmlElement dShapePoint("point");
    dShapePoint.SetAttribute("name", "center");
    dShapePoint.SetAttribute("x", "0");
    dShapePoint.SetAttribute("y", "2");
    dShapePoint.SetAttribute("z", "0");

    // Shape - BSDF Reference
    TiXmlElement dBsdfRef("ref");
    dBsdfRef.SetAttribute("name", "bsdf");
    dBsdfRef.SetAttribute("id", "bsdfroughplastic");





    // Step 4: add all elements
    doc.InsertEndChild(decl); // Add the declaration to the document


    dSensorSampler.InsertEndChild(dSensorSamplerSC);

    dSensorTransform.InsertEndChild(dSensorTransformLA);

    dSensorFilm.InsertEndChild(dSensorFilmH);
    dSensorFilm.InsertEndChild(dSensorFilmW);
    dSensorFilm.InsertEndChild(dSensorFilmFilter);

//    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticGGXDist);
//    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticAlpha);
//    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticIor);
//    dBsdfRoughPlastic.InsertEndChild(dBsdfRoughPlasticRgb);

    dSensor.InsertEndChild(dSensorFarClip);
    dSensor.InsertEndChild(dSensorNearClip);
    dSensor.InsertEndChild(dSensorFocusDistance);
    dSensor.InsertEndChild(dSensorFov);
    dSensor.InsertEndChild(dSensorFovAxis);
    dSensor.InsertEndChild(dSensorTransform);
    dSensor.InsertEndChild(dSensorFilm);
    dSensor.InsertEndChild(dSensorSampler);


    dEmitter.InsertEndChild(dEmitterSpectrum);
    dShapeEmit.InsertEndChild(dShapeEPoint);
    dShapeEmit.InsertEndChild(dEmitter);

    dShape.InsertEndChild(dShapePoint);
    dShape.InsertEndChild(dBsdfRef);

//    dScene.InsertEndChild(dBsdfRoughPlastic);
    for(TiXmlElement bsdfElem : xmlBsdfs)
    {
        dScene.InsertEndChild(bsdfElem);
    }
    dScene.InsertEndChild(dSensor);
    dScene.InsertEndChild(dIntegrator);
    dScene.InsertEndChild(dShapeEmit);
    dScene.InsertEndChild(dShape);

    doc.InsertEndChild(dScene);

    // Step 5: save the XML document
    try {
        std::system("mkdir $HOME/SavedScene");
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }
//    doc.SaveFile("$HOME/SavedScene/" + filename);
    doc.SaveFile("/home/dfara/SavedScene/" + filename);


}

void generateScene(ms::XMLScene& scene, std::map<int, int>& map, std::string filename="scene.xml")
{
    // Step 0: create the new XML file
    TiXmlDocument doc;
    TiXmlDeclaration decl( "1.0", "utf-8", "" ); // Create the declaration [XML Version and encoding]

    // Step 1: create the scene
    TiXmlElement dScene("scene");
    dScene.SetAttribute("version", "2.0.0");

    // Step 2: set up the integrator and the sensor
    // Integrator
    TiXmlElement dIntegrator("integrator");
    dIntegrator.SetAttribute("type", scene.getIntegrator().getType());

    // Sensor
    TiXmlElement dSensor("sensor");
    dSensor.SetAttribute("type", scene.getSensor().getSensorType());

    // Sensor - Far Clip
    TiXmlElement dSensorFarClip("float");
    dSensorFarClip.SetAttribute("name", "far_clip");
    dSensorFarClip.SetAttribute("value", scene.getSensor().getFarClipValue());

    // Sensor - Near Clip
    TiXmlElement dSensorNearClip("float");
    dSensorNearClip.SetAttribute("name", "near_clip");
    dSensorNearClip.SetAttribute("value", scene.getSensor().getNearClipValue());

    // Sensor - Focus Distance
    TiXmlElement dSensorFocusDistance("float");
    dSensorFocusDistance.SetAttribute("name", "focus_distance");
    dSensorFocusDistance.SetAttribute("value", scene.getSensor().getFocusDistance());

    // Sensor - Fov
    TiXmlElement dSensorFov("float");
    dSensorFov.SetAttribute("name", "fov");
    dSensorFov.SetAttribute("value", scene.getSensor().getFov());

    // Sensor - Fov Axis
    TiXmlElement dSensorFovAxis("string");
    dSensorFovAxis.SetAttribute("name", "fov_axis");
    dSensorFovAxis.SetAttribute("value", scene.getSensor().getFovAxis());

    // Sensor - Transform
    TiXmlElement dSensorTransform("transform");
    dSensorTransform.SetAttribute("name", scene.getSensor().getTransformName());

    // Sensor - Transform - LookAt
    TiXmlElement dSensorTransformLA("lookat");
    std::ostringstream vts;
    eigenMatToString(vts, scene.getSensor().getTransformTarget());
    dSensorTransformLA.SetAttribute("target", vts.str());

    eigenMatToString(vts, scene.getSensor().getTransformOrigin());
    dSensorTransformLA.SetAttribute("origin", vts.str());

    eigenMatToString(vts, scene.getSensor().getTransformUp());
    dSensorTransformLA.SetAttribute("up", vts.str());

    // Sensor - Sampler
    TiXmlElement dSensorSampler("sampler");
    dSensorSampler.SetAttribute("type", "independent");

    // Sensor - Sampler - Sample Count
    TiXmlElement dSensorSamplerSC("integer");
    dSensorSamplerSC.SetAttribute("name", "sample_count");
    dSensorSamplerSC.SetAttribute("value", scene.getSensor().getSampleCount());

    // Sensor - Film
    TiXmlElement dSensorFilm("film");
    dSensorFilm.SetAttribute("type", "hdrfilm");

    // Sensor - Film - Height
    TiXmlElement dSensorFilmH("integer");
    dSensorFilmH.SetAttribute("name", "height");
    dSensorFilmH.SetAttribute("value", scene.getSensor().getFilmHeight());

    // Sensor - Film - Width
    TiXmlElement dSensorFilmW("integer");
    dSensorFilmW.SetAttribute("name", "width");
    dSensorFilmW.SetAttribute("value", scene.getSensor().getFilmWidth());

    // Sensor - Film - Filter
    TiXmlElement dSensorFilmFilter("rfilter");
    dSensorFilmFilter.SetAttribute("type", scene.getSensor().getFilterName());

    // Step 2: Add the shapes
    // Shape - Sphere Light
    TiXmlElement dShapeEmit("shape");
    dShapeEmit.SetAttribute("type", "sphere");

    // Shape - Sphere Light - Center
    TiXmlElement dShapeEPoint("point");
    dShapeEPoint.SetAttribute("name", "center");
    dShapeEPoint.SetAttribute("x", "0");
    dShapeEPoint.SetAttribute("y", "7");
    dShapeEPoint.SetAttribute("z", "0");

    // Test - Sphere Light - Emitter
    TiXmlElement dEmitter("emitter");
    dEmitter.SetAttribute("type", "area");

    // Test - Sphere Light - Emitter - Spectrum
    TiXmlElement dEmitterSpectrum("spectrum");
    dEmitterSpectrum.SetAttribute("name", "radiance");
    dEmitterSpectrum.SetAttribute("value", "100");

    // Other Shapes
    std::vector<TiXmlElement> xmlShapes;


}



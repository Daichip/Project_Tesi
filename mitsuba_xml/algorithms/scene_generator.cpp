#include "mitsuba_xml/algorithms/scene_generator.h"

//***********************************************************************************************
void eigenMatToString(std::ostringstream& vts, const Eigen::Vector3d& mat)
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

void arrayToString(std::ostringstream& vts, const std::array<float, 3>& arr)
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

void ms::generateScene(ms::XMLScene& scene, std::map<int, ms::Mats>& map)
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

    // Sensor - Fov
    TiXmlElement dSensorFov("float");
    dSensorFov.SetAttribute("name", "fov");
    dSensorFov.SetAttribute("value", scene.getSensor().getFov());

    // Sensor - Transform
    TiXmlElement dSensorTransform("transform");
    dSensorTransform.SetAttribute("name", scene.getSensor().getTransformName());

    // Sensor - Transform - LookAt
    TiXmlElement dSensorTransformLA("lookat");
    std::ostringstream vts;
    arrayToString(vts, scene.getSensor().getTransformTarget());
    dSensorTransformLA.SetAttribute("target", vts.str());

    vts = std::ostringstream();
    arrayToString(vts, scene.getSensor().getTransformOrigin());
    dSensorTransformLA.SetAttribute("origin", vts.str());

    vts = std::ostringstream();
    arrayToString(vts, scene.getSensor().getTransformUp());
    dSensorTransformLA.SetAttribute("up", vts.str());

    TiXmlElement dSensorTransformMatrix("matrix");
    dSensorTransformMatrix.SetAttribute("value", scene.getSensor().getTransformationMatrix());


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

    // Step 2: Add the shapes and the lights

    // Constant Light Emitter
    TiXmlElement dCEmitter("emitter");
    dCEmitter.SetAttribute("type", "constant");

    TiXmlElement dEmitterSpectrum("spectrum");
    dEmitterSpectrum.SetAttribute("name", "radiance");
    dEmitterSpectrum.SetAttribute("value", "1.0");

    // Other Shapes
    std::vector<TiXmlElement> xmlShapes;

    for(std::map<int, ms::Mats>::iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        xmlShapes.push_back(ms::generateShape(iter->first, iter->second));
    }

    // Step 3: add all elements
    doc.InsertEndChild(decl); // Add the declaration to the document

    dSensorSampler.InsertEndChild(dSensorSamplerSC);

    dSensorTransform.InsertEndChild(dSensorTransformLA);
    dSensorTransform.InsertEndChild(dSensorTransformMatrix);

    dSensorFilm.InsertEndChild(dSensorFilmH);
    dSensorFilm.InsertEndChild(dSensorFilmW);
    dSensorFilm.InsertEndChild(dSensorFilmFilter);

    dSensor.InsertEndChild(dSensorFov);
    dSensor.InsertEndChild(dSensorTransform);
    dSensor.InsertEndChild(dSensorFilm);
    dSensor.InsertEndChild(dSensorSampler);

    dCEmitter.InsertEndChild(dEmitterSpectrum);

    dScene.InsertEndChild(dSensor);
    dScene.InsertEndChild(dIntegrator);
    dScene.InsertEndChild(dCEmitter);

    for(TiXmlElement shape : xmlShapes)
    {
        dScene.InsertEndChild(shape);
    }

    doc.InsertEndChild(dScene);


    // Step 4: save the XML document
    doc.SaveFile("Results/Scene.xml");

}




TiXmlElement ms::generateShape(int meshIndex, int matIndex)
{
//    <shape type="obj" id="Mesh_3">
//            <string name="filename" value="2.obj"/>
//            <bsdf type="roughplastic">
//                <string name="distribution" value="ggx"/>
//                <float name="alpha" value="0.1"/>
//                <float name="int_ior" value="1.49"/>
//                <rgb name="diffuse_reflectance" value="0.1, 0.1, 0.75"/>
//            </bsdf>
//        </shape>


    TiXmlElement dShape("shape");
    dShape.SetAttribute("type", "obj");

    TiXmlElement dFilename("string");
    dFilename.SetAttribute("name", "filename");
    dFilename.SetAttribute("value", std::to_string(meshIndex) + ".obj");
    dShape.InsertEndChild(dFilename);

    dShape.InsertEndChild(ms::generateBsdf(matIndex));

    return dShape;
}


TiXmlElement ms::generateBsdf(int matType)
{
    TiXmlElement dBsdf("bsdf");
    TiXmlElement dBsdfProps("string");

    TiXmlElement dBsdfRoughPlasticAlpha("float");
    TiXmlElement dBsdfRoughPlasticIor("float");
    TiXmlElement dBsdfRoughPlasticRgb("rgb");

    switch (matType) {

        // Plastic Green
        case 0:
            dBsdf.SetAttribute("type", "roughplastic");
            dBsdfProps.SetAttribute("name", "distribution");
            dBsdfProps.SetAttribute("value", "ggx");

            // BSDF - Rough Plastic - Alpha

            dBsdfRoughPlasticAlpha.SetAttribute("name", "alpha");
            dBsdfRoughPlasticAlpha.SetAttribute("value", "0.1");
            // BSDF - Rough Plastic - Int IoR
            dBsdfRoughPlasticIor.SetAttribute("name", "int_ior");
            dBsdfRoughPlasticIor.SetAttribute("value", "1.5");

            // BSDF - Rough Plastic - RGB
            dBsdfRoughPlasticRgb.SetAttribute("name", "diffuse_reflectance");
            dBsdfRoughPlasticRgb.SetAttribute("value", "0.1, 0.75, 0.1");

            dBsdf.InsertEndChild(dBsdfProps);
            dBsdf.InsertEndChild(dBsdfRoughPlasticAlpha);
            dBsdf.InsertEndChild(dBsdfRoughPlasticIor);
            dBsdf.InsertEndChild(dBsdfRoughPlasticRgb);
            break;

        // Plastic Red
        case 1:
            dBsdf.SetAttribute("type", "roughplastic");
            dBsdfProps.SetAttribute("name", "distribution");
            dBsdfProps.SetAttribute("value", "ggx");

            // BSDF - Rough Plastic - Alpha
            dBsdfRoughPlasticAlpha.SetAttribute("name", "alpha");
            dBsdfRoughPlasticAlpha.SetAttribute("value", "0.1");
            // BSDF - Rough Plastic - Int IoR
            dBsdfRoughPlasticIor.SetAttribute("name", "int_ior");
            dBsdfRoughPlasticIor.SetAttribute("value", "1.5");

            // BSDF - Rough Plastic - RGB
            dBsdfRoughPlasticRgb.SetAttribute("name", "diffuse_reflectance");
            dBsdfRoughPlasticRgb.SetAttribute("value", "0.75, 0.1, 0.1");

            dBsdf.InsertEndChild(dBsdfProps);
            dBsdf.InsertEndChild(dBsdfRoughPlasticAlpha);
            dBsdf.InsertEndChild(dBsdfRoughPlasticIor);
            dBsdf.InsertEndChild(dBsdfRoughPlasticRgb);
            break;

        // Gold
        case 2:
            dBsdf.SetAttribute("type", "conductor");

            dBsdfProps.SetAttribute("name", "material");
            dBsdfProps.SetAttribute("value", "Au");

            dBsdf.InsertEndChild(dBsdfProps);
            break;

        // Mirror
        case 3:
            dBsdf.SetAttribute("type", "conductor");

            dBsdfProps.SetAttribute("name", "material");
            dBsdfProps.SetAttribute("value", "none");

            dBsdf.InsertEndChild(dBsdfProps);
            break;
    }

    return dBsdf;

}




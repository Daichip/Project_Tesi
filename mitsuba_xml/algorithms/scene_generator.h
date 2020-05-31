#ifndef SCENE_GENERATOR_H
#define SCENE_GENERATOR_H

#include <ostream>
#include <iterator>
#include <map>

#include "mitsuba_xml/data_structures/xmlscene.h"
#include "ticpp.h"

namespace ms{

void generateScene();
void generateScene(ms::XMLScene& scene, std::string filename="scene.xml");
void generateScene(ms::XMLScene& scene, std::map<int, int>& map, std::string filename="scene.xml");

TiXmlElement generateShape(int meshIndex);
TiXmlElement generateBsdf(int matType);

} // end of namespace ms

#endif // SCENE_GENERATOR_H

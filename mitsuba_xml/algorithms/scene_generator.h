#ifndef SCENE_GENERATOR_H
#define SCENE_GENERATOR_H

#include <ostream>
#include <iterator>
#include <map>

#include "mitsuba_xml/data_structures/xmlscene.h"
#include "ticpp.h"

namespace ms{

enum Mats { PGreen, PRed, Gold, Mirror };

void generateScene(ms::XMLScene& scene, std::map<int, ms::Mats>& map);

TiXmlElement generateShape(int meshIndex, int matIndex);
TiXmlElement generateBsdf(int matType);

} // end of namespace ms

#endif // SCENE_GENERATOR_H

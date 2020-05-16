#ifndef SCENE_GENERATOR_H
#define SCENE_GENERATOR_H

#include "mitsuba_xml/data_structures/xmlscene.h"
#include "ticpp.h"

namespace ms{

void generateScene(ms::XMLScene scene, std::string filename="scene.xml");
void generateScene();

} // end of namespace ms

#endif // SCENE_GENERATOR_H

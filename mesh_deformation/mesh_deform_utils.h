#ifndef MESH_DEFORM_UTILS_H
#define MESH_DEFORM_UTILS_H

#include <vector>
#include <iostream>

#include <Eigen/Core>

#include <igl/ray_mesh_intersect.h>
#include <igl/barycentric_coordinates.h>

#include <nvl/math/point.h>
#include <nvl/math/normals.h>

#include <QMessageBox>



namespace mdf{

void findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                             std::vector<Eigen::Vector3d>& projectedVerts, Eigen::Vector3d rayOrig);





} // END OF NAMESPACE mdf



#endif // MESH_DEFORM_UTILS_H

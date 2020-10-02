#ifndef MESH_DEFORM_UTILS_H
#define MESH_DEFORM_UTILS_H

#include <vector>
#include <iostream>

#include <Eigen/Core>

#include <igl/AABB.h>
#include <igl/barycentric_coordinates.h>

#include <nvl/math/point.h>
#include <nvl/math/normals.h>
#include <nvl/models/meshes.h>
#include <nvl/models/mesh_eigen_convert.h>

#include <chrono>


#include <QMessageBox>



namespace mdf{

typedef nvl::PolygonMesh3d Mesh;

void findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                             std::vector<Eigen::Vector3d>& projectedVerts, Eigen::Vector3d rayOrig);


void findMirrorIntersections(Mesh& inputMesh, Mesh& mirrorMesh, Mesh& defMesh, Eigen::Vector3d rayOrig);





} // END OF NAMESPACE mdf



#endif // MESH_DEFORM_UTILS_H

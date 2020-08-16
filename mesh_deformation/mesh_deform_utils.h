#ifndef MESH_DEFORM_UTILS_H
#define MESH_DEFORM_UTILS_H

#include <vector>
#include <iostream>

#include <Eigen/Core>

#include <igl/ray_mesh_intersect.h>
#include <igl/barycentric_coordinates.h>

#include <nvl/math/point.h>
#include <nvl/math/normals.h>



namespace mdf{

// Finds all visible vertices in the mesh
void findIntersectionVertices(Eigen::MatrixXd& meshVerts, Eigen::MatrixXi& meshFaces, std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig);
void findIntersectionVertices(Eigen::MatrixXd& meshVerts, Eigen::MatrixXi& meshFaces, std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig, Eigen::Vector3d rayDest);

void findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                             std::vector<Eigen::Vector3d>& intersections, std::vector<double>& distances,
                             std::vector<Eigen::Vector3d>& rayDirs, std::vector<Eigen::Vector3d>& projectedVerts, Eigen::Vector3d rayOrig);

void findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXi& meshFaces,
                             Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                             std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig);




} // END OF NAMESPACE mdf



#endif // MESH_DEFORM_UTILS_H

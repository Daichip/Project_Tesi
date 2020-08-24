#include <mesh_deformation/mesh_deform_utils.h>

void mdf::findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                                  std::vector<Eigen::Vector3d>& intersections, std::vector<double>& distances,
                                  std::vector<Eigen::Vector3d>& rayDirs, std::vector<Eigen::Vector3d>& projectedVerts, Eigen::Vector3d rayOrig)
{
    for(int v = 0; v < meshVerts.rows(); v++)
    {
        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
        Eigen::Vector3d rayDir = (vert - rayOrig).normalized(); // Direction of the ray going from the camera to the vertex (same for the mirror)

        std::vector<igl::Hit> vertHits; // vector of vertices in the MESH that are visible from the camera
        std::vector<igl::Hit> mirrorHits; // For each visible vertex, find the corresponding point on the Mirror

        // If the ray hits something
        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, mirrorVerts, mirrorFaces, mirrorHits))
        {
            Eigen::Vector3d vmFound = rayOrig + mirrorHits[0].t * rayDir;
            double dist = sqrt( pow( (vmFound.x() - vert.x() ), 2) + pow( (vmFound.y() - vert.y()), 2) );

            // Get normals
            int faceIndex = mirrorHits[0].id;
            int faceVertexindex1 = mirrorFaces(faceIndex, 0);
            int faceVertexindex2 = mirrorFaces(faceIndex, 1);
            int faceVertexindex3 = mirrorFaces(faceIndex, 2);
            nvl::Point3d faceVertex1 = mirrorVerts.row(faceVertexindex1);
            nvl::Point3d faceVertex2 = mirrorVerts.row(faceVertexindex2);
            nvl::Point3d faceVertex3 = mirrorVerts.row(faceVertexindex3);


            std::vector<nvl::Point3d> faceVertices;
            faceVertices.push_back(faceVertex1);
            faceVertices.push_back(faceVertex2);
            faceVertices.push_back(faceVertex3);

            Eigen::Vector3d mirrorReflDir = nvl::getFaceNormalPlanar(faceVertices, true).normalized();

            Eigen::Vector3d projVert = vmFound + dist * mirrorReflDir;

            intersections.push_back(vmFound);
            rayDirs.push_back(mirrorReflDir);
            distances.push_back(dist);
            projectedVerts.push_back(projVert);
        }
    }
//    QMessageBox successMsg;
//    successMsg.setText("Deformation Saved!");
//    successMsg.exec();

}
// V.row(F(f,0))


















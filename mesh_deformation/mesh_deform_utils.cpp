#include <mesh_deformation/mesh_deform_utils.h>

void mdf::findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                                  std::vector<Eigen::Vector3d>& projectedVerts, Eigen::Vector3d rayOrig)
{
    for(int v = 0; v < meshVerts.rows(); v++)
    {
        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
        Eigen::Vector3d rayDir = (vert - rayOrig).normalized(); // Direction of the ray going from the camera to the vertex (same for the mirror)

        std::vector<igl::Hit> mirrorHits; // For each visible vertex, find the corresponding point on the Mirror

        // If the ray hits something
        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, mirrorVerts, mirrorFaces, mirrorHits))
        {
            Eigen::Vector3d vmFound = rayOrig + mirrorHits[0].t * rayDir;
            double dist = sqrt( pow( (vmFound.x() - vert.x()), 2) +
                                pow( (vmFound.y() - vert.y()), 2) +
                                pow( (vmFound.z() - vert.z()), 2) );

            // Get normals
            // Get the face id from the igl::Hit
            // Get the vertices of the face
            // Get the normal of said face
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

            Eigen::Vector3d mirrorReflDir = nvl::getFaceNormalPlanar(faceVertices, true);

            // Invert vertices order to compute the normal

            Eigen::Vector3d projVert = vmFound + dist * mirrorReflDir;

            projectedVerts.push_back(projVert);

            mirrorHits.clear();
        }
    }
//    QMessageBox successMsg;
//    successMsg.setText("Deformation Saved!");
//    successMsg.exec();

}






void mdf::findMirrorIntersections(Mesh& inputMesh, Mesh& mirrorMesh, Mesh& defMesh, Eigen::Vector3d rayOrig)
{

    Eigen::MatrixXd mirrorV;
    Eigen::MatrixXi mirrorF;
    nvl::convertMeshToEigenMesh(mirrorMesh, mirrorV, mirrorF);

    Eigen::MatrixXd meshV;
    Eigen::MatrixXi meshF;
    nvl::convertMeshToEigenMesh(inputMesh, meshV, meshF);

    std::vector<igl::Hit> hits;
    std::vector<Eigen::Vector3d> projectedVerts;


    for(int v = 0; v < meshV.rows(); v++)
    {
        Eigen::Vector3d vert = meshV.row(v);

        // Direction of the ray going from the camera to the vertex (same for the mirror)
        Eigen::Vector3d rayDir = (vert - rayOrig).normalized();

        std::vector<igl::Hit> mirrorHits; // Contains, for each vertex of the mesh, the corresponding point on the Mirror

        // If the ray hits something
        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, mirrorV, mirrorF, mirrorHits))
        {
            Eigen::Vector3d vmFound = rayOrig + mirrorHits[0].t * rayDir;
            double dist = sqrt( pow( (vmFound.x() - vert.x()), 2) +
                                pow( (vmFound.y() - vert.y()), 2) +
                                pow( (vmFound.z() - vert.z()), 2) );

            // Get normals
            // Get the face id from the igl::Hit
            // Get the vertices of the face
            // Get the normal of said face
            int faceIndex = mirrorHits[0].id;
            int faceVertexindex1 = mirrorF(faceIndex, 0);
            int faceVertexindex2 = mirrorF(faceIndex, 1);
            int faceVertexindex3 = mirrorF(faceIndex, 2);

            Eigen::Vector3d& v1Norm = mirrorMesh.vertexNormal(faceVertexindex1);
            Eigen::Vector3d& v2Norm = mirrorMesh.vertexNormal(faceVertexindex2);
            Eigen::Vector3d& v3Norm = mirrorMesh.vertexNormal(faceVertexindex3);

            Eigen::Vector3d mirrorReflDir = ( (1 - mirrorHits[0].u - mirrorHits[0].v) * v1Norm +
                                               mirrorHits[0].u * v2Norm +
                                               mirrorHits[0].v * v3Norm
                                            ).normalized();

            Eigen::Vector3d projVert = vmFound + dist * mirrorReflDir;

            projectedVerts.push_back(projVert);

            mirrorHits.clear();
        }
    }

    Eigen::MatrixXd defVertices(projectedVerts.size(), 3);
    for(int k = 0; k < projectedVerts.size(); k++)
        defVertices.row(k) = projectedVerts[k].transpose();

    for (int fId = 0; fId < meshF.rows(); fId++)
        std::swap(meshF(fId, 0), meshF(fId, 2));

    nvl::convertEigenMeshToMesh(defVertices, meshF, defMesh);
}











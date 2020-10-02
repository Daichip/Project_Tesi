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
    // Extract vertices and faces of the input mesh
    Eigen::MatrixXd meshV;
    Eigen::MatrixXi meshF;
    nvl::convertMeshToEigenMesh(inputMesh, meshV, meshF);

    // Extract vertices and faces of the mirror mesh
    Eigen::MatrixXd mirrorV;
    Eigen::MatrixXi mirrorF;
    nvl::convertMeshToEigenMesh(mirrorMesh, mirrorV, mirrorF);

    // Create the matrix containing the vertices of the deformation
    Eigen::MatrixXd defVertices(meshV.rows(), 3);

    // Test timer
    auto start = std::chrono::high_resolution_clock::now();

    igl::AABB<Eigen::MatrixXd, 3> tree;
    tree.init(mirrorV, mirrorF);

    // For each vertex of the input model
    for(int v = 0; v < meshV.rows(); v++)
    {
        Eigen::Vector3d vert = meshV.row(v);

        // Direction of the ray going from the camera to the vertex (same for the mirror)
        Eigen::Vector3d rayDir = (vert - rayOrig).normalized();

        // Will contain the information associated to the intersection between the ray and
        // the mirror'surface. We're interested in the face's ID and the barycentric coordinates
        igl::Hit hit;

//        auto pre_igl = std::chrono::high_resolution_clock::now();
//        std::cout << "Pre igl: " << std::chrono::duration_cast<std::chrono::seconds>(pre_igl - start).count() << std::endl;

        bool found = tree.intersect_ray(mirrorV, mirrorF, rayOrig, rayDir, hit);

        // Checks if the ray hits the surface on the mirror
        if(found)
        {
            // Compute the coordinates of the intersection
            Eigen::Vector3d vmFound = rayOrig + hit.t * rayDir;

            // Compute the distance between the vertex on the input model
            // and the intersection
            double dist = sqrt( pow( (vmFound.x() - vert.x()), 2) +
                                pow( (vmFound.y() - vert.y()), 2) +
                                pow( (vmFound.z() - vert.z()), 2) );

            // Get normals
            // Get the face id from the igl::Hit object
            // Get the vertices of the face
            // Get the vertex normals of the face
            int faceIndex = hit.id;
            int faceVertexindex1 = mirrorF(faceIndex, 0);
            int faceVertexindex2 = mirrorF(faceIndex, 1);
            int faceVertexindex3 = mirrorF(faceIndex, 2);

            Eigen::Vector3d& v1Norm = mirrorMesh.vertexNormal(faceVertexindex1);
            Eigen::Vector3d& v2Norm = mirrorMesh.vertexNormal(faceVertexindex2);
            Eigen::Vector3d& v3Norm = mirrorMesh.vertexNormal(faceVertexindex3);

            // Interpolate with the barycentric coordinates to obtain the direction of the reflection of the ray
            Eigen::Vector3d mirrorReflDir = ( (1 - hit.u - hit.v) * v1Norm +
                                               hit.u * v2Norm +
                                               hit.v * v3Norm
                                            ).normalized();

            // Compute the coordinates of the "reflected" vertex
            Eigen::Vector3d projVert = vmFound + dist * mirrorReflDir;

            // Add the new vertex to the deformation
            defVertices.row(v) = projVert.transpose();
        }

//        auto post_igl = std::chrono::high_resolution_clock::now();
//        std::cout << "Post igl: " << std::chrono::duration_cast<std::chrono::seconds>(post_igl - pre_igl).count() << " seconds\nTot: " << std::chrono::duration_cast<std::chrono::seconds>(post_igl - start).count() << " seconds" << std::endl;

    }

//    auto post_vert = std::chrono::high_resolution_clock::now();
//    std::cout << "Post Vertici: " << std::chrono::duration_cast<std::chrono::seconds>(post_vert - start).count() << " seconds" << std::endl;

    // Invert the order of the vertices of the face to
    // properly represent the reflection phenonmenon
    for (int fId = 0; fId < meshF.rows(); fId++)
        std::swap(meshF(fId, 0), meshF(fId, 2));

//    auto swap_facce = std::chrono::high_resolution_clock::now();
//    std::cout << "Swap facce: " << std::chrono::duration_cast<std::chrono::seconds>(swap_facce - post_vert).count() << " seconds\nTot: " << std::chrono::duration_cast<std::chrono::seconds>(swap_facce - start).count() << " seconds" << std::endl;

    // Create a Mesh object
    nvl::convertEigenMeshToMesh(defVertices, meshF, defMesh);

    auto mesh_convert = std::chrono::high_resolution_clock::now();
    std::cout << "Tot: " << std::chrono::duration_cast<std::chrono::seconds>(mesh_convert - start).count() << " seconds" << std::endl;
//    std::cout << "Mesh Convertita: " << std::chrono::duration_cast<std::chrono::seconds>(mesh_convert - swap_facce).count() << " seconds\nTot: " << std::chrono::duration_cast<std::chrono::seconds>(mesh_convert - start).count() << " seconds" << std::endl;
}








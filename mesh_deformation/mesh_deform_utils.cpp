#include <mesh_deformation/mesh_deform_utils.h>


void mdf::findIntersectionVertices(Eigen::MatrixXd& meshVerts,  Eigen::MatrixXi& meshFaces,
                                   std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig)
{
    // For each vertex check the number of intersections
    // If it's only 1, then it is visible, else it's behind something

    // To check the intersections we project a ray starting from rayOrig
    // towards the vertex
    // The ray's direction is obtained as: (dest - orig).normalized

//    std::cout << "\n\nMesh Def: " << std::endl;

    for(int v = 0; v < meshVerts.rows(); v++)
    {
        // Should be but can't be const
        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
//        std::cout << "\nVert: \n" << vert.x() << ", " << vert.y() << ", " << vert.z() <<  std::endl;

        std::vector<igl::Hit> hits;
        Eigen::Vector3d rayDir = (vert - rayOrig).normalized();
//        std::cout << "Ray Direction:\n" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << std::endl;

        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, meshVerts, meshFaces, hits))
        {
            Eigen::Vector3d vFound = rayOrig + hits[0].t * rayDir;
//            std::cout << "Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << hits[0].t << ", " << hits[0].id << ", " << hits[0].gid << std::endl;
            // Formula: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/definition-ray
//            std::cout << "Intersection = origin + direction * t: \n" << vFound.x() << ", " << vFound.y() << ", " << vFound.z() << std::endl;

            float scale = 0.000001; // 6 decimal digits
            float dx = vert.x() - vFound.x();
            dx = (int)(dx / scale) * scale;
            float dy = vert.y() - vFound.y();
            dy = (int)(dy / scale) * scale;
            float dz = vert.z() - vFound.z();
            dz = (int)(dz / scale) * scale;

            bool sameVertexFlag = (dx == 0) && (dy == 0) && (dz == 0);
//            std::cout << "Same vertex? -> " << sameVertexFlag << std::endl;
            if(sameVertexFlag)
            {
//                    std::cout << "Found same vertex" << std::endl;
                    toBeReturned.push_back(vert);
//                    return;
            }
        }
//        std::cout << "v: " << v <<  std::endl;
    }



    // Save each visible vertex in "visibleVerts"
}


void mdf::findIntersectionVertices(Eigen::MatrixXd& meshVerts,  Eigen::MatrixXi& meshFaces,
                                   std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig, Eigen::Vector3d rayDest)
{
    // For each vertex check the number of intersections
    // If it's only 1, then it is visible, else it's behind something

    // To check the intersections we project a ray starting from rayOrig
    // towards the vertex
    // The ray's direction is obtained as: (dest - orig).normalized

//    std::cout << "\n\nMesh Def: " << std::endl;

    for(int v = 0; v < meshVerts.rows(); v++)
    {



        // Should be but can't be const
        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
//        std::cout << "\nVert: \n" << vert.x() << ", " << vert.y() << ", " << vert.z() <<  std::endl;

//        std::cout << "Ray Dest: " << rayDest << std::endl;

        std::vector<igl::Hit> hits;
        Eigen::Vector3d rayDir = (rayDest - rayOrig).normalized();
//        std::cout << "Ray Direction:\n" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << std::endl;

        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, meshVerts, meshFaces, hits))
        {
            Eigen::Vector3d vFound = rayOrig + hits[0].t * rayDir;
//            std::cout << "Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << hits[0].t << ", " << hits[0].id << ", " << hits[0].gid << std::endl;
            // Formula: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/definition-ray
//            std::cout << "Intersection = origin + direction * t: \n" << vFound.x() << ", " << vFound.y() << ", " << vFound.z() << std::endl;

            float scale = 0.000001; // 6 decimal digits
            float dx = vert.x() - vFound.x();
            dx = (int)(dx / scale) * scale;
            float dy = vert.y() - vFound.y();
            dy = (int)(dy / scale) * scale;
            float dz = vert.z() - vFound.z();
            dz = (int)(dz / scale) * scale;

            bool sameVertexFlag = (dx == 0) && (dy == 0) && (dz == 0);
//            std::cout << "Same vertex? -> " << sameVertexFlag << std::endl;
            if(sameVertexFlag)
            {
//                    std::cout << "Found same vertex" << std::endl;
                    toBeReturned.push_back(vert);
//                    return;
            }
        }
//        std::cout << "v: " << v <<  std::endl;
    }



    // Save each visible vertex in "visibleVerts"
}



void mdf::findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXi& meshFaces,
                                  Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
                                  std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig)
{
//    // For each vertex in the mesh shoot a ray from the camera to the vertex itself
//    for(int v = 0; v < meshVerts.rows(); v++)
//    {
//        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
////        std::cout << "\n------------------------------------------------------------------\nMesh Vert: \n" << vert.x() << ", " << vert.y() << ", " << vert.z() <<  std::endl;

//        std::vector<igl::Hit> vertHits; // vector of vertices in the MESH that are visible from the camera
//        std::vector<igl::Hit> mirrorHits; // For each visible vertex, find the corresponding point on the Mirror

//        Eigen::Vector3d rayDir = (vert - rayOrig).normalized(); // Direction of the ray going from the camera to the vertex (same for the mirror)
////        std::cout << "Ray Direction:\n" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << std::endl;
/// }


//    // Using that very same ray, find the point where it intersects the mirror
//    // Compute the distance between each mesh vertex and the intersection point in the mirror
//    // From the point on the mirror's surface, use the normal to find the reflection direction
//    // Along said direction, use the distance computed above to find the projection of the vertex from the mirror






















    // For each vertex
    for(int v = 0; v < meshVerts.rows(); v++)
    {
        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
//        std::cout << "\n------------------------------------------------------------------\nMesh Vert: \n" << vert.x() << ", " << vert.y() << ", " << vert.z() <<  std::endl;

        Eigen::Vector3d rayDir = (vert - rayOrig).normalized(); // Direction of the ray going from the camera to the vertex (same for the mirror)
//        std::cout << "Ray Direction:\n" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << std::endl;

        std::vector<igl::Hit> vertHits; // vector of vertices in the MESH that are visible from the camera
        std::vector<igl::Hit> mirrorHits; // For each visible vertex, find the corresponding point on the Mirror

        // If the ray hits something
        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
        if(igl::ray_mesh_intersect(rayOrig, rayDir, meshVerts, meshFaces, vertHits))
        {
            // Check that the first hit is the vertex itself
            // Formula: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/definition-ray
            Eigen::Vector3d vFound = rayOrig + vertHits[0].t * rayDir;
//            std::cout << "Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << vertHits[0].t << ", " << vertHits[0].id << ", " << vertHits[0].gid << std::endl;
//            std::cout << "Intersection = origin + direction * t: \n" << vFound.x() << ", " << vFound.y() << ", " << vFound.z() << std::endl;

            // Formatting to avoid precision issues
            float dx = vert.x() - vFound.x();
            float dy = vert.y() - vFound.y();
            float dz = vert.z() - vFound.z();
            float scale = 0.000001; // 6 decimal digits
            // Round back to int later
            dx = (int)(dx / scale) * scale;
            dy = (int)(dy / scale) * scale;
            dz = (int)(dz / scale) * scale;

            bool sameVertexFlag = (dx == 0) && (dy == 0) && (dz == 0);
//            std::cout << "Same vertex? -> " << sameVertexFlag << std::endl;

            // If the hits corresponds to the vertex itself it means it is visible from the point of view
            // in this case we also check the intersection between the ray and the mirror
            // To do that we re-use the very same ray we just used, but we substitute the meshes
            if(sameVertexFlag)
            {
//                std::cout << "Found same vertex" << std::endl;

                for(int vm = 0; vm < mirrorVerts.rows(); vm++)
                {
                    Eigen::Vector3d mVert = meshVerts.row(vm).template cast<double>();

                    if(igl::ray_mesh_intersect(rayOrig, rayDir, mirrorVerts, mirrorFaces, mirrorHits))
                    {
                        Eigen::Vector3d vmFound = rayOrig + mirrorHits[0].t * rayDir;

                        // Formatting to avoid precision issues
                        float dx = mVert.x() - vmFound.x();
                        float dy = mVert.y() - vmFound.y();
                        float dz = mVert.z() - vmFound.z();
                        float scale = 0.000001; // 6 decimal digits
                        // Round back to int later
                        dx = (int)(dx / scale) * scale;
                        dy = (int)(dy / scale) * scale;
                        dz = (int)(dz / scale) * scale;

                        if((dx == 0) && (dy == 0) && (dz == 0))
                        {
//                            std::cout << "\nMirror Vert: \n" << mVert.x() << ", " << mVert.y() << ", " << mVert.z() <<  std::endl;
//                            std::cout << "Mirror Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << mirrorHits[0].t << ", " << mirrorHits[0].id << ", " << mirrorHits[0].gid << std::endl;
//                            std::cout << "Mirror Intersection = origin + direction * t: \n" << vmFound.x() << ", " << vmFound.y() << ", " << vmFound.z() << std::endl;
//                            std::cout << "Found Mirror Intersection" << std::endl;
                            toBeReturned.push_back(vFound);
                            std::cout << "ToBeReturned.size() = " << toBeReturned.size() << std::endl;
                            break;
                        }

                    }
                }
            }
        }
//        std::cout << "v: " << v <<  std::endl;
    }
}
























//void mdf::findMirrorIntersections(Eigen::MatrixXd& meshVerts, Eigen::MatrixXi& meshFaces,
//                                  Eigen::MatrixXd& mirrorVerts, Eigen::MatrixXi& mirrorFaces,
//                                  std::vector<Eigen::Vector3d>& toBeReturned, Eigen::Vector3d rayOrig)
//{
//    // For each vertex
//    for(int v = 0; v < meshVerts.rows(); v++)
//    {
//        Eigen::Vector3d vert = meshVerts.row(v).template cast<double>();
////        std::cout << "\n------------------------------------------------------------------\nMesh Vert: \n" << vert.x() << ", " << vert.y() << ", " << vert.z() <<  std::endl;

//        std::vector<igl::Hit> vertHits; // vector of vertices in the MESH that are visible from the camera
//        std::vector<igl::Hit> mirrorHits; // For each visible vertex, find the corresponding point on the Mirror

//        Eigen::Vector3d rayDir = (vert - rayOrig).normalized(); // Direction of the ray going from the camera to the vertex (same for the mirror)
////        std::cout << "Ray Direction:\n" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << std::endl;

//        // If the ray hits something
//        // igl::ray_mesh_intersect(rayOrig, rayDir, V, F, hits);
//        if(igl::ray_mesh_intersect(rayOrig, rayDir, meshVerts, meshFaces, vertHits))
//        {
//            // Check that the first hit is the vertex itself
//            // Formula: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/definition-ray
//            Eigen::Vector3d vFound = rayOrig + vertHits[0].t * rayDir;
////            std::cout << "Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << vertHits[0].t << ", " << vertHits[0].id << ", " << vertHits[0].gid << std::endl;
////            std::cout << "Intersection = origin + direction * t: \n" << vFound.x() << ", " << vFound.y() << ", " << vFound.z() << std::endl;

//            // Formatting to avoid precision issues
//            float scale = 0.000001; // 6 decimal digits
//            float dx = vert.x() - vFound.x();
//            dx = (int)(dx / scale) * scale;
//            float dy = vert.y() - vFound.y();
//            dy = (int)(dy / scale) * scale;
//            float dz = vert.z() - vFound.z();
//            dz = (int)(dz / scale) * scale;

//            bool sameVertexFlag = (dx == 0) && (dy == 0) && (dz == 0);
////            std::cout << "Same vertex? -> " << sameVertexFlag << std::endl;

//            // If the hits corresponds to the vertex itself it means it is visible from the point of view
//            // in this case we also check the intersection between the ray and the mirror
//            // To do that we re-use the very same ray we just used, but we substitute the meshes
//            if(sameVertexFlag)
//            {
////                std::cout << "Found same vertex" << std::endl;

//                for(int vm = 0; vm < mirrorVerts.rows(); vm++)
//                {
//                    Eigen::Vector3d mVert = meshVerts.row(vm).template cast<double>();

//                    if(igl::ray_mesh_intersect(rayOrig, rayDir, mirrorVerts, mirrorFaces, mirrorHits))
//                    {
//                        Eigen::Vector3d vmFound = rayOrig + mirrorHits[0].t * rayDir;

//                        // Formatting to avoid precision issues
//                        float scale = 0.000001; // 6 decimal digits
//                        float dx = mVert.x() - vmFound.x();
//                        dx = (int)(dx / scale) * scale;
//                        float dy = mVert.y() - vmFound.y();
//                        dy = (int)(dy / scale) * scale;
//                        float dz = mVert.z() - vmFound.z();
//                        dz = (int)(dz / scale) * scale;

//                        if((dx == 0) && (dy == 0) && (dz == 0))
//                        {
////                            std::cout << "\nMirror Vert: \n" << mVert.x() << ", " << mVert.y() << ", " << mVert.z() <<  std::endl;
////                            std::cout << "Mirror Hits[0] -> Distance from intersection, primitive ID, geometry ID: \n" << mirrorHits[0].t << ", " << mirrorHits[0].id << ", " << mirrorHits[0].gid << std::endl;
////                            std::cout << "Mirror Intersection = origin + direction * t: \n" << vmFound.x() << ", " << vmFound.y() << ", " << vmFound.z() << std::endl;
////                            std::cout << "Found Mirror Intersection" << std::endl;
//                            toBeReturned.push_back(vFound);
//                        }

//                    }
//                }
//            }
//        }
////        std::cout << "v: " << v <<  std::endl;
//    }
//}

#include "manager.h"
#include "ui_manager.h"

#include <nvl/utilities/timer.h>

#include <nvl/utilities/colorize.h>

#include <nvl/models/mesh_transformations.h>
#include <nvl/models/mesh_normals.h>

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

Manager::Manager(
        nvl::Canvas* canvas,
        nvl::DrawableListWidget* drawableListWidget,
        nvl::ModelLoaderWidget* modelLoaderWidget,
        QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Manager),
    vCanvas(canvas),
    vDrawableListWidget(drawableListWidget),
    vModelLoaderWidget(modelLoaderWidget)
{
    ui->setupUi(this);

    initialize();
    connectSignals();
}

Manager::~Manager()
{
    delete ui;
}

void Manager::slot_canvasPicking(const std::vector<PickingData>& data) {
    bool shiftPressed = QApplication::keyboardModifiers() & Qt::ShiftModifier;

    if (data.size() > 0) {
        size_t drawableId = data[0].value1;

        std::unordered_set<Index> selectedDrawables = vDrawableListWidget->selectedDrawables();

        if (selectedDrawables.size() != 1 || *selectedDrawables.begin() != drawableId) {
            if (shiftPressed) {
                if (selectedDrawables.find(drawableId) == selectedDrawables.end()) {
                    selectedDrawables.insert(drawableId);
                }
                else {
                    selectedDrawables.erase(drawableId);
                }
            }
            else {
                selectedDrawables.clear();
                selectedDrawables.insert(drawableId);
            }

            vDrawableListWidget->setSelectedDrawables(selectedDrawables);
        }
    }
}

void Manager::slot_drawableSelectionChanged(const std::unordered_set<nvl::Skeleton3d::JointId>& selectedDrawables)
{
    NVL_SUPPRESS_UNUSEDVARIABLE(selectedDrawables);

    updateView();

    vCanvas->setMovableFrame(nvl::Affine3d::Identity());

    vCanvas->updateGL();
}

void Manager::slot_movableFrameChanged()
{
    nvl::Affine3d transform = vCanvas->movableFrame();

    nvl::Affine3d::LinearMatrixType scaMatrix;
    transform.computeScalingRotation(&scaMatrix, static_cast<nvl::Affine3d::LinearMatrixType*>(0));
    nvl::Scaling3d sca(scaMatrix.diagonal());

    nvl::Quaterniond rot(transform.rotation());

    nvl::Translation3d tra(transform.translation());

    for (Index id : vDrawableListWidget->selectedDrawables()) {
        if (vCanvas->isFrameable(id)) {
            nvl::Frameable* frameable = vCanvas->frameable(id);
            nvl::Drawable* drawable = vCanvas->drawable(id);

            const nvl::Affine3d& frame = frameable->frame();

            nvl::Translation3d lastTra(frame.translation());
            nvl::Quaterniond lastRot(frame.rotation());

            nvl::Point3d center = drawable->sceneCenter();
            nvl::Translation3d originTra(-center);

            nvl::Affine3d newFrame = frame;

            //Go to center
            newFrame = originTra * newFrame;

            //Scale
            newFrame = sca * newFrame;

            //Rotation
            newFrame = rot * newFrame;

            //Back to initial position
            newFrame = originTra.inverse() * newFrame;

            //Translation
            newFrame = tra * newFrame;

            frameable->setFrame(newFrame);
        }
    }

    vCanvas->setMovableFrame(nvl::Affine3d::Identity());
    vCanvas->updateGL();
}

void Manager::slot_drawableAdded(const Manager::Index& id, nvl::Drawable* drawable)
{
    if (vCanvas->isPickable(id)) {
        MeshDrawer* meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
        if (meshDrawer != nullptr) {
            meshDrawer->setFaceColorMode(MeshDrawer::FaceColorMode::FACE_COLOR_PER_FACE);
        }
    }
}

Manager::MeshDrawer *Manager::getSelectedMeshDrawer()
{
    MeshDrawer* selectedModelDrawer = nullptr;

    const std::unordered_set<Index>& selectedDrawables = vDrawableListWidget->selectedDrawables();
    if (selectedDrawables.size() == 1) {
        Index firstItem = *selectedDrawables.begin();
        nvl::Drawable* drawable = vCanvas->drawable(firstItem);

        MeshDrawer* meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
        if (meshDrawer != nullptr) {
            meshDrawer->setTrasparencyEnabled(true); /** To Be Deleted **/
            selectedModelDrawer = meshDrawer;
        }
    }

    return selectedModelDrawer;
}

void Manager::updateView()
{
    MeshDrawer* selectedMeshDrawer = getSelectedMeshDrawer();

    bool drawableSelected = selectedMeshDrawer != nullptr;

//    ui->materialWoodRadio->setEnabled(drawableSelected);
//    ui->materialStoneRadio->setEnabled(drawableSelected);
    ui->materialGoldRadio->setEnabled(drawableSelected);
    ui->materialMirrorRadio->setEnabled(drawableSelected);
    ui->materialPlasticRedRadio->setEnabled(drawableSelected);
    ui->materialPlasticGreenRadio->setEnabled(drawableSelected);
}

void Manager::initialize()
{
    updateView();
}

void Manager::connectSignals()
{
    if (vCanvas != nullptr) {
        //Connect signals to the viewer
        connect(vDrawableListWidget, &nvl::DrawableListWidget::signal_drawableSelectionChanged, this, &Manager::slot_drawableSelectionChanged);
        connect(vCanvas, &nvl::Canvas::signal_movableFrameChanged, this, &Manager::slot_movableFrameChanged);
        connect(vCanvas, &nvl::Canvas::signal_canvasPicking, this, &Manager::slot_canvasPicking);
        connect(vCanvas, &nvl::Canvas::signal_drawableAdded, this, &Manager::slot_drawableAdded);
        connect(ui->materialGoldRadio, SIGNAL(clicked()), this, SLOT(on_materialGoldRadio_clicked()));
        connect(ui->materialPlasticGreenRadio, SIGNAL(clicked()), this, SLOT(on_materialPlasticGreenRadio_clicked()));
        connect(ui->materialPlasticRedRadio, SIGNAL(clicked()), this, SLOT(on_materialPlasticRedRadio_clicked()));
        connect(ui->materialMirrorRadio, SIGNAL(clicked()), this, SLOT(on_materialMirrorRadio_clicked()));
    }
}

void Manager::on_saveSceneButton_clicked()
{
    // The "true" boolean is used in the setupAndGenererateScene
    // to define if we need a full render (film size = canvas size) or just a preview (480x270)
    // In this case the user pressed the "Render" button, therefore it is a full render
    setupRender();
    executeRender(true);
}

void Manager::on_previewButton_clicked()
{
    // The "true" boolean is used in the setupAndGenererateScene
    // to define if we need a full render (film size = canvas size) or just a preview (480x270)
    // In this case the user pressed the "Preview" button, therefore it is a low-quality render
    setupRender();
    executeRender(false);
}

void Manager::on_materialGoldRadio_clicked()
{
    std::cout << "Clicked GOLD button" << std::endl;
    addToMap(ms::Gold, findDrawableIndex());
}

void Manager::on_materialPlasticGreenRadio_clicked()
{
    std::cout << "Clicked PLASTIC GREEN button" << std::endl;
//    matToMeshMap.insert({selectedIndex, Manager::Mats::PGreen});
    addToMap(ms::PGreen, findDrawableIndex());
}

void Manager::on_materialPlasticRedRadio_clicked()
{
    std::cout << "Clicked PLASTIC RED button" << std::endl;
//    matToMeshMap.insert({selectedIndex, Manager::Mats::PRed});
    addToMap(ms::PRed, findDrawableIndex());
}

void Manager::on_materialMirrorRadio_clicked()
{
    std::cout << "Clicked MIRROR button" << std::endl;
//    matToMeshMap.insert({selectedIndex, Manager::Mats::Mirror});
    addToMap(ms::Mirror, findDrawableIndex());
}


void Manager::setupAndGenerateScene(ms::XMLScene& scene, nvl::Canvas* vCanvas, bool renderFlag)
{
    scene.setNumberOfShapesPresent(vCanvas->drawableNumber());
    if(renderFlag)
    {
        scene.getSensor().setFilmWidth(vCanvas->screenWidth());
        scene.getSensor().setFilmHeight(vCanvas->screenHeight());
    }
    else
    {
        scene.getSensor().setFilmWidth(480);
        scene.getSensor().setFilmHeight(270);
    }

    //ModelView Matrix
    nvl::Matrix44d modelViewMatrix = vCanvas->cameraModelViewMatrix();
    nvl::Matrix44d inverseModelViewMatrix = modelViewMatrix.inverse();

    // Since we're applying the transformation to the camera, we need to invert it
    // in order to set it in the right position
    // [Note: Mitsuba has the camera looking towards +z instead of -z. This is solved via the Lookat XML element]
    std::string inverseModelViewMatrixString = "";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i > 0 || j > 0) {
                inverseModelViewMatrixString += ", ";
            }

            inverseModelViewMatrixString += std::to_string(inverseModelViewMatrix(j,i)); //Mitsuba uses column-major matrices
        }
    }

    scene.getSensor().setTransformationMatrix(inverseModelViewMatrixString);

    ms::generateScene(scene, matToMeshMap);
}

void Manager::addToMap(ms::Mats mat, int index)
{

    // Look up if the mesh is present in the map [index]
    // If it is, then check if the mat is the same as the inserted one
    //  If it is, leave
    //  If it isn't update
    // If the mesh is not present in the map, add it
    if(matToMeshMap.find(index) != matToMeshMap.end())
    {
        if(matToMeshMap[index] != mat)
        {
            matToMeshMap[index] = mat;
            std::cout << "Manager::addToMap - Updated: {" << index << ", " << mat << "}" << std::endl;
        }
    }
    else
    {
        // Element is not yet present
        std::cout << "Manager::addToMap - Added: {" << index << ", " << mat << "}" << std::endl;
        matToMeshMap.insert({index, mat});
    }
}

int Manager::findDrawableIndex()
{
    int selectedIndex = -1;

    for(Index i = 0; i < vCanvas->drawableNumber(); i++)
    {
        if(vDrawableListWidget->isDrawableSelected(i))
        {
            selectedIndex = i;
            std::cout << "Manager::findDrawableIndex - SIndex: " << selectedIndex << std::endl;
            break;
        }
    }

    return selectedIndex;
}



void Manager::executeCommand(std::string command)
{
    try {
        std::system(command.c_str());
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }
}


void Manager::setupRender()
{
    try {
        std::system("mkdir Results");
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }

    for (Index i = 0; i < vCanvas->drawableNumber(); ++i) {
        Drawable* drawable = vCanvas->drawable(i);

        MeshDrawer* meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
        if (meshDrawer != nullptr) {
            Mesh meshCopy = *meshDrawer->mesh();
            nvl::meshApplyTransformation(meshCopy, meshDrawer->frame());
            nvl::meshUpdateVertexNormals(meshCopy);
            nvl::meshSaveToFile("Results/" + std::to_string(i) + ".obj", meshCopy);

            // Automatically associates a material (Green Plastic) to a mesh if not set already
            auto findIT = matToMeshMap.find(i); // separated in order to avoid n checks
            if(findIT == matToMeshMap.end())
                addToMap(ms::Mats::PGreen, i);
        }
    }

}


void Manager::executeRender(bool renderFlag)
{

    setupRender();


    ms::XMLScene scene;

    setupAndGenerateScene(scene, vCanvas, renderFlag);
//    QMessageBox successMsg;
//    successMsg.setText("Scene Saved!\nPlease press \"OK\" and wait for the render to finish");
//    successMsg.exec();


    std::string cmd_render = "\"" + std::string(TOSTRING(MITSUBA_PATH)) + "\" \"" + std::string(TOSTRING(RESULTS_FOLDER)) + "/Scene.xml\"";
    executeCommand(cmd_render);


    // Convert .EXR to .PNG
    std::string cmd_convert = "convert \"" + std::string(TOSTRING(RESULTS_FOLDER)) + "/Scene.exr\" -colorspace RGB -colorspace sRGB \"" + std::string(TOSTRING(RESULTS_FOLDER)) + "/Scene.png\"";
    executeCommand(cmd_convert);


    // Set image in window
    const QImage renderImage = QImage("Results/Scene.png").scaledToWidth(300);
    ui->imageLabelViewer->setPixmap(QPixmap::fromImage(renderImage));
    std::cout << "Image set" << std::endl;
}


void Manager::on_computeDeformationButton_clicked()
{
    /**
        ray_mesh_intersect
        ray_mesh_intersect(source: array, dir: array, v: array, f: array) -> List[Tuple[int, int, float, float, float]]

        Shoot a ray against a mesh (V,F) and collect the first hit.

        Parameters
            source 3-vector origin of ray
            dir 3-vector direction of ray
            V #V by 3 list of mesh vertex positions
            F #F by 3 list of mesh face indices into V
        Returns
            hits sorted list of hits: id, gid, u, v, t

      **/

    setupRender();

    if(vCanvas->drawables().size() > 0)
    {
        int mirrorIndex;
        std::vector<int> meshIndices;
        auto matMeshIt = matToMeshMap.begin();

        while(matMeshIt != matToMeshMap.end())
        {
            if(matMeshIt->second == ms::Mirror)
                mirrorIndex = matMeshIt->first;
            else
                meshIndices.push_back(matMeshIt->first);

            matMeshIt++;
        }

        if(mirrorIndex >= 0 && mirrorIndex < vCanvas->drawables().size())
        {
            Drawable* drawable = vCanvas->drawable(mirrorIndex);
            MeshDrawer* meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
            Mesh mirrorMesh = *meshDrawer->mesh();
            nvl::meshApplyTransformation(mirrorMesh, meshDrawer->frame());
            nvl::meshUpdateVertexNormals(mirrorMesh);

            drawable = vCanvas->drawable(meshIndices[0]);
            meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
            Mesh inputMesh = *meshDrawer->mesh();
            nvl::meshApplyTransformation(inputMesh, meshDrawer->frame());
            nvl::meshUpdateVertexNormals(inputMesh);

            Mesh defMesh;

            mdf::findMirrorIntersections(inputMesh, mirrorMesh, defMesh, vCanvas->cameraPosition());

            nvl::meshSaveToFile("Results/deformedMesh.obj", defMesh);


        } // End IF [mirrorIndex >= 0 && mirrorIndex < vCanvas->drawables().size()]


        std::cout << "\n\nDeformation Saved" << std::endl;

    } // End IF [vCanvas->drawables().size() > 0]

}

void Manager::on_positionResetPushButton_clicked()
{
    // When the "Reset Position" button is clicked
    // both the mirror and the model to be deformed are found
    // the mirror is then scaled to a bounding box of the
    // same size as the value stated in the interface.
    // The model is then scaled to a slightly smaller BB
    // in order for it to fit inside the mirror
    // Both models are then translated to the center of the scene.

    if(vCanvas->drawables().size() > 0)
    {
        int mirrorIndex;
        std::vector<int> meshIndices;
        auto matMeshIt = matToMeshMap.begin();

        while(matMeshIt != matToMeshMap.end())
        {
            if(matMeshIt->second == ms::Mirror)
                mirrorIndex = matMeshIt->first;
            else
                meshIndices.push_back(matMeshIt->first);

            matMeshIt++;
        }

        if(mirrorIndex >= 0 && mirrorIndex < vCanvas->drawables().size())
        {

            // If there is a mirror in the scene
            // Scale it and translate it

            float mirrorScaleFactor = ui->mirrorScaleFactorLineEdit->text().toFloat();
            double maxX, maxY, maxZ, minX, minY, minZ;

            // To scale the BB properly: scaleFactor/maxCoord
            // So if they are (0.4, 0.9, 0.2) it will be (1/0.9, 1/ 0.9, 1/0.9)

            // F1: Vertici e facce
            // F2: Dati i vertici trova il massimo in ogni coordinata
            // F3: Dato il centro del BB, trova il fattore di traslazione per il centro degli assi



            Drawable* drawable = vCanvas->drawable(mirrorIndex);
            MeshDrawer* meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
            Mesh mirrorMesh = *meshDrawer->mesh();

            // Extract vertices and faces of the mirror mesh
            Eigen::MatrixXd mirrorV;
            Eigen::MatrixXi mirrorF;
            nvl::convertMeshToEigenMesh(mirrorMesh, mirrorV, mirrorF);


            minX = maxX = mirrorV.row(0).x();
            minY = maxY = mirrorV.row(0).y();
            minZ = maxZ = mirrorV.row(0).z();


            for(int v = 0; v < mirrorV.rows(); v++)
            {
                Eigen::Vector3d vert = mirrorV.row(v);

                // X Coord
                if(vert.x() < minX)
                    minX = vert.x();

                if(vert.x() > maxX)
                    maxX = vert.x();

                // Y Coord
                if(vert.y() < minY)
                    minY = vert.y();

                if(vert.y() > maxY)
                    maxY = vert.y();

                // Z Coord
                if(vert.z() < minZ)
                    minZ = vert.z();

                if(vert.z() > maxZ)
                    maxZ = vert.z();
            }

            double maxCoord = std::max(maxX, std::max(maxY, maxZ));

//            Eigen::Vector3d scaleFactor(mirrorScaleFactor / maxCoord, mirrorScaleFactor / maxCoord, mirrorScaleFactor / maxCoord);

            Eigen::Vector3d center = meshDrawer->boundingBox().center();

//            Eigen::Scaling(mirrorScaleFactor/maxCoord);
//            Eigen::Translation<double, 3>(center.x(), center.y(), center.z());

            nvl::meshApplyTransformation(mirrorMesh, Eigen::Scaling(mirrorScaleFactor/maxCoord));
            nvl::meshApplyTransformation(mirrorMesh,  Eigen::Translation<double, 3>(-center.x(), -center.y(), -center.z()));

            meshDrawer->setMesh(&mirrorMesh);




            // -----------------------------------------------------------

//            drawable = vCanvas->drawable(meshIndices[0]);
//            meshDrawer = dynamic_cast<MeshDrawer*>(drawable);
//            Mesh inputMesh = *meshDrawer->mesh();
//            nvl::meshApplyTransformation(inputMesh, meshDrawer->frame());
//            nvl::meshUpdateVertexNormals(inputMesh);

//            // Extract vertices and faces of the input mesh
//            Eigen::MatrixXd meshV;
//            Eigen::MatrixXi meshF;
//            nvl::convertMeshToEigenMesh(inputMesh, meshV, meshF);













        } // End IF [mirrorIndex >= 0 && mirrorIndex < vCanvas->drawables().size()]
    } // End IF [vCanvas->drawables().size() > 0]


    vCanvas->update();
    updateView();


}

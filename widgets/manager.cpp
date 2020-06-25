#include "manager.h"
#include "ui_manager.h"

#include <nvl/utilities/timer.h>

#include <nvl/utilities/colorize.h>

#include <nvl/models/mesh_transformations.h>

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

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
            nvl::meshSaveToFile("Results/" + std::to_string(i) + ".obj", meshCopy);

            //************************************************************************************************************************************************
            std::cout << "MeshDrawer Frame: \n" << meshDrawer->frame().matrix() << std::endl;

            std::cout << "Working with Mesh: " << meshDrawer->mesh() << "\n\n" << std::endl;
            //************************************************************************************************************************************************
        }
    }




    ms::XMLScene scene;

    setupAndGenerateScene(scene, vCanvas);
//    QMessageBox successMsg;
//    successMsg.setText("Scene Saved!\nPlease press \"OK\" and wait for the render to finish");
//    successMsg.exec();


    //* SYSTEM CALLS + Set Image
#ifdef RESULTS_FOLDER
#ifdef MITSUBA_PATH
    try {
        // Dynamic Scene
        std::string cmd_render = (std::string)MITSUBA_PATH + " " + RESULTS_FOLDER + "/Scene.xml";
        std::system(cmd_render.c_str());
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }
#endif


    // Convert .EXR to .PNG
    try {
//        std::system("$HOME/exrtools-0.4/src/exrtopng $HOME/Results/Scene.exr $HOME/Results/Scene.png");
        std::string cmd_convert = (std::string)"convert " + RESULTS_FOLDER + "/Scene.exr -colorspace RGB -colorspace sRGB " + RESULTS_FOLDER + "/Scene.png";
        std::system(cmd_convert.c_str());
    } catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " << e.code()
                  << " meaning " << e.what() << '\n';
    }


      // Test to adjust picture dimention while retaining scale
//    int w_coeff = vCanvas->width() / 480;
//    int h_coeff = vCanvas->height() / 270;
//    std::cout << "Width: " << vCanvas->width() << "\tHeight: " << vCanvas->height() << "\nW_C: " << w_coeff << "\tH_C: " << h_coeff << std::endl;
//    const QImage renderImage = QImage("Results/Scene.png").scaled(vCanvas->width() / w_coeff, vCanvas->height() / h_coeff);
    const QImage renderImage = QImage("Results/Scene.png").scaled(480, 270);
    ui->imageLabelViewer->setPixmap(QPixmap::fromImage(renderImage));
    std::cout << "Image set" << std::endl;

#endif
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


void Manager::setupAndGenerateScene(ms::XMLScene& scene, nvl::Canvas* vCanvas)
{
    scene.setNumberOfShapesPresent(vCanvas->drawableNumber());
    // Used in the test mentioned above to retain image scale
//    scene.getSensor().setFilmWidth(vCanvas->width());
//    scene.getSensor().setFilmHeight(vCanvas->height());

    // Camera Origin
    float cx = vCanvas->cameraPosition().x();
    float cy = vCanvas->cameraPosition().y();
    float cz = vCanvas->cameraPosition().z();
    scene.getSensor().setTransformOrigin({cx, cy, cz});

    // Camera Target
    Eigen::Vector3d target = vCanvas->cameraPosition() + (vCanvas->cameraViewDirection());

    float tx = target.x();
    float ty = target.y();
    float tz = target.z();
    scene.getSensor().setTransformTarget({tx, ty, tz});

    // ModelView Matrix
    nvl::Matrix44d modelViewMatrix = vCanvas->cameraModelViewMatrix();
    GLdouble* matrix = modelViewMatrix.data();

    std::string mvm = "";


    nvl::Matrix44d viewProjectionMatrix = vCanvas->cameraModelViewProjectionMatrix();
    GLdouble* viewProjMatrix = viewProjectionMatrix.data();


    nvl::Matrix44d projectionMatrix = vCanvas->cameraProjectionMatrix();
    GLdouble* projMatrix = projectionMatrix.data();


    std::cout << "Camera model view matrix: ";
    for (int i = 0; i < 15; i++) {
           std::cout << matrix[i] << " ";
           mvm += std::to_string(matrix[i]) + ", ";
       }
    mvm += std::to_string(matrix[15]);

    // Set the MVM to be used in the XML file
    scene.getSensor().setModelViewMatrix(mvm);

    std::cout << "\n\nCamera model View Projection matrix: ";
    for (int i = 0; i < 16; i++) {
           std::cout << viewProjMatrix[i] << " ";
       }
    std::cout << std::endl;

    std::cout << "\n\nCamera Projection matrix: ";
    for (int i = 0; i < 16; i++) {
           std::cout << projMatrix[i] << " ";
       }
    std::cout << std::endl;


    ms::generateScene(scene, matToMeshMap);

}

void Manager::addToMap(ms::Mats mat, int index)
{

    // Look up if the mesh is present in the map [index]
    // If it is, then check if the mat is the same as the inserted one
    // If it is, leave
    // If it isn't update
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

    for(int i = 0; i < vCanvas->drawableNumber(); i++)
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




























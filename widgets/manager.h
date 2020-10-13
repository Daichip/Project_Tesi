#ifndef MANAGER_H
#define MANAGER_H

#include <QFrame>
#include <QWidget>
#include <QMessageBox>
#include <QImageReader>
#include <QDebug>

#include <cstdlib>

#include <nvl/viewer/widgets/canvas.h>
#include <nvl/viewer/widgets/drawable_list_widget.h>
#include <nvl/viewer/widgets/skeletonjoint_list_widget.h>
#include <nvl/viewer/widgets/model_loader_widget.h>
#include <nvl/models/mesh_transformations.h>
#include <nvl/models/mesh_eigen_convert.h>

#include <nvl/models/model.h>
#include <nvl/models/meshes.h>

#include <mitsuba_xml/algorithms/scene_generator.h>
#include <mitsuba_xml/data_structures/xmlscene.h>
#include <mitsuba_xml/data_structures/xmlintegrator.h>
#include <mitsuba_xml/data_structures/xmlsensor.h>
#include <mitsuba_xml/data_structures/xmlshape.h>

#include <mesh_deformation/mesh_deform_utils.h>

#include <igl/ray_mesh_intersect.h>


namespace Ui {
class Manager;
}

class Manager : public QFrame
{
    Q_OBJECT

    typedef nvl::Index Index;
    typedef nvl::PolygonMesh3d Mesh;
    typedef nvl::SurfaceMeshDrawer<Mesh> MeshDrawer;
    typedef nvl::Drawable Drawable;

    typedef nvl::Canvas::PickingData PickingData;

public:

    explicit Manager(
            nvl::Canvas* canvas,
            nvl::DrawableListWidget* drawableListWidget,
            nvl::ModelLoaderWidget* modelLoaderWidget,
            QWidget *parent = nullptr);
    ~Manager();


public Q_SLOTS:

    void slot_canvasPicking(const std::vector<PickingData>& data);
    void slot_drawableSelectionChanged(const std::unordered_set<Index>& selectDrawables);
    void slot_movableFrameChanged();    
    void slot_drawableAdded(const Index& id, nvl::Drawable* drawable);


private slots:


    void on_saveSceneButton_clicked();

    void on_materialGoldRadio_clicked();

    void on_materialPlasticGreenRadio_clicked();

    void on_materialPlasticRedRadio_clicked();

    void on_materialMirrorRadio_clicked();



    void on_previewButton_clicked();

    void on_computeDeformationButton_clicked();

    void on_positionResetPushButton_clicked();

private:

    MeshDrawer* getSelectedMeshDrawer();

    void updateView();

    void initialize();
    void connectSignals();

    // XML Methods
    void addToMap(ms::Mats mat, int index);
    int findDrawableIndex();
    void setupAndGenerateScene(ms::XMLScene& scene, nvl::Canvas* vCanvas, bool renderFlag);
    void executeCommand(std::string command);
    void setupRender();
    void executeRender(bool renderFlag);

    // Drawer manipulation Methods
    void scaleAndTranslate(int drawerIndex);


    //Interface fields
    Ui::Manager *ui;

    nvl::Canvas* vCanvas;
    nvl::DrawableListWidget* vDrawableListWidget;
    nvl::ModelLoaderWidget* vModelLoaderWidget;

    // XML
    std::map<int, ms::Mats> matToMeshMap;

};

#endif // MANAGER_H

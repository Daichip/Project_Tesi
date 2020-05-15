#ifndef MANAGER_H
#define MANAGER_H

#include <QFrame>
#include <QWidget>
#include <QMessageBox>

#include <nvl/viewer/widgets/canvas.h>
#include <nvl/viewer/widgets/drawable_list_widget.h>
#include <nvl/viewer/widgets/skeletonjoint_list_widget.h>
#include <nvl/viewer/widgets/model_loader_widget.h>

#include <nvl/models/model.h>
#include <nvl/models/meshes.h>

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

private:

    MeshDrawer* getSelectedMeshDrawer();

    void updateView();

    void initialize();
    void connectSignals();

    //Interface fields
    Ui::Manager *ui;

    nvl::Canvas* vCanvas;
    nvl::DrawableListWidget* vDrawableListWidget;
    nvl::ModelLoaderWidget* vModelLoaderWidget;

};

#endif // MANAGER_H

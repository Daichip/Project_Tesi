#include <QApplication>

#include <nvl/viewer/viewerwindow.h>
#include <nvl/viewer/widgets/drawable_list_widget.h>
#include <nvl/viewer/widgets/drawable_widget.h>
#include <nvl/viewer/widgets/model_loader_widget.h>
#include <nvl/viewer/widgets/model_drawer_widget.h>
#include <nvl/viewer/widgets/qglviewer_canvas.h>

#include "widgets/manager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //Viewer
    nvl::ViewerWindow viewer;
    viewer.setWindowTitle("SkinMixer");

    //Show docks
    viewer.showLeftDock();
    viewer.showRightDock();

    //Add canvas
    nvl::QGLViewerCanvas canvas(&viewer);
    viewer.addCanvas(&canvas);

    //Right dock
    nvl::DrawableListWidget drawableListWidget(&canvas);
    viewer.addToRightDock(&drawableListWidget);
    nvl::DrawableWidget drawableWidget(&canvas, &drawableListWidget);
    viewer.addToRightDock(&drawableWidget);
    nvl::ModelDrawerWidget meshDrawerWidget(&canvas, &drawableListWidget);
    viewer.addToRightDock(&meshDrawerWidget);

    //Left dock
    nvl::ModelLoaderWidget modelLoaderWidget(&canvas, &drawableListWidget);
    viewer.addToLeftDock(&modelLoaderWidget);
    Manager manager(&canvas, &drawableListWidget, &modelLoaderWidget);
    viewer.addToLeftDock(&manager);

    canvas.fitScene();

    viewer.showMaximized();

    return app.exec();
}


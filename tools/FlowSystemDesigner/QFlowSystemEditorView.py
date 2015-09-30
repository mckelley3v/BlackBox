from __future__ import print_function
from PyQt4 import QtCore, QtGui
from QFlowComponentInstance import QFlowComponentInstance

class QFlowSystemEditorScene(QtGui.QGraphicsScene):
    def __init__(self, parent = None):
        super(QFlowSystemEditorScene, self).__init__(parent)

    def dragEnterEvent(self, event):
        event.accept()

    def dragMoveEvent(self, event):
        event.accept()

    def dragLeaveEvent(self, event):
        event.accept()

    def dropEvent(self, event):
        # get this data from MIME
        compDefinition = {
            "Name": "DefinitionName",
            "InputPorts": [
                {
                    "PortName": "In0",
                    "TypeName": "T"
                },
                {
                    "PortName": "In1",
                    "TypeName": "T"
                }
            ],
            "OutputPorts": [
                {
                    "PortName": "Out0",
                    "TypeName": "T"
                }
            ]
        }

        componentInstanceWidget = QFlowComponentInstance.fromDefinition(None, compDefinition)
        componentInstanceWidget.adjustSize()

        componentInstanceSceneItem = self.addWidget(componentInstanceWidget)
        componentInstanceSceneItem.setPos(event.scenePos())

        event.accept()

class QFlowSystemEditorView(QtGui.QGraphicsView):
    class State:
        idle = 0

    def __init__(self, parent = None):
        super(QFlowSystemEditorView, self).__init__(parent)
        self.state = QFlowSystemEditorView.State.idle
        self.scene = QFlowSystemEditorScene(self)
        self.setScene(self.scene)

    def resizeEvent(self, event):
        super(QFlowSystemEditorView, self).resizeEvent(event)

        # calculate how much of the scene the view now covers
        size = self.size()
        viewSize = self.mapToScene(size.width(), size.height())
        viewRect = self.sceneRect()
        viewRectMin = QtCore.QRectF(viewRect.x(),
                                    viewRect.y(),
                                    viewSize.x(),
                                    viewSize.y())
        sceneRectMin = viewRect.united(viewRectMin)

        # the scene should be at least as big as the current view of it
        sceneRect = self.scene.itemsBoundingRect()
        sceneRect = sceneRect.united(sceneRectMin)
        self.setSceneRect(sceneRect)

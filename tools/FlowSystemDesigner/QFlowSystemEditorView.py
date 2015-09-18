from __future__ import print_function
from PyQt4 import QtCore, QtGui

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
        text = QtGui.QGraphicsTextItem(unicode("drop"))
        text.setPos(event.scenePos())
        self.addItem(text)
        event.accept()

class QFlowSystemEditorView(QtGui.QGraphicsView):
    class State:
        idle = 0

    def __init__(self, parent = None):
        super(QFlowSystemEditorView, self).__init__(parent)
        self.state = QFlowSystemEditorView.State.idle
        self.scene = QFlowSystemEditorScene(self)
        self.setScene(self.scene)

    #def resizeEvent(self, event):
    #    super(QFlowSystemEditorView, self).resizeEvent(event)
    #    size = self.size()
    #    self.setSceneRect(0, 0, size.width(), size.height())

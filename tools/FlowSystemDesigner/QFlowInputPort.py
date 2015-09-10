from PyQt4 import QtCore, QtGui
import weakref

class QFlowInputPort(QtGui.QGraphicsPathItem):
    def __init__(self,
                 parent,
                 port_name,
                 type_name,
                 is_optional = False,
                 is_multiplex = False):

        super(QFlowInputPort, self).__init__(parent)

        self._componentConnectionRefs = []
        self.port_name = port_name
        self.type_name = type_name

        self.radius = 4
        self.margin = 3

        self.label = QtGui.QGraphicsTextItem(self)
        self.label.setPlainText(self.name)
        self.label.setPos(-self.radius - self-margin - self.label.boundingRect().width(),
                          -self.label.boundingRect().height() / 2)

        path = QtGui.QPainterPath()
        path.addEllipse(-self.radius, -self.radius, 2 * self.radius, 2 * self.radius)
        self.setPath(path)

        self.setPen(QtGui.QPen(Qt.darkRed))
        self.setBrush(Qt.red)

        self.setFlag(QtGui.QGraphicsItem.ItemSendsScenePositionChanges)

    def addConnection(self, connection)
        self._componentConnectionRefs.append(weakref.ref(connection))

    def removeConnection(self, connection)
        try:
            self._componentConnectionRefs.remove(weakref.ref(connection))
        except:
            pass

    def itemChange(self, change, value):
        if change == QtGui.QGraphicsItem.ItemScenePositionHasChanged:
            for connectionRef in self._componentConnectionRefs:
                connection = connectionRef()
                if connection is not None:
                    connection.refresh()

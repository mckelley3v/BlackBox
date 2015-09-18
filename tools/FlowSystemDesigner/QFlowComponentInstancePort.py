from PyQt4 import QtCore, QtGui
from Ui_QFlowComponentInstancePort import Ui_QFlowComponentInstancePort

def build_ellipse(bounding_rect):
        path = QtGui.QPainterPath()
        path.addEllipse(bounding_rect)
        return path

# probably needs to be derived from QGraphicsItem (not a widget)
# which would force getting rid of the auto-layout stuff, are there any other options?
class QFlowComponentInstancePort(QtGui.QWidget):
    class PortType:
        Input = 0
        Output = 0

    def __init__(self, parent = None):
        super(QFlowComponentInstancePort, self).__init__(parent)
        self._portName = ""
        self._typeName = ""
        self.portGraphics = None
        self.ui = Ui_QFlowComponentInstancePort()
        self.ui.setupUi(self)

    @classmethod
    def fromDict(cls, parent, portDict, portType):
        # required
        portName = portDict["PortName"]
        typeName = portDict["TypeName"]

        # not yet using these values
        isOptional = None
        isMultiplex = None
        if portType == PortType.Input:
            isOptional = portDict.get("IsOptional", False)
            isMultiplex = portDict.get("IsMultiplex", False)

        self = QFlowComponentInstancePort(parent)
        self._portName = portName
        self._typeName = typeName

        self.ui.label.setPlainText("%s : %s" % (self._portName, self._typeName))
        self.portGraphics = QtGui.QGraphicsPathItem(self.ui.port)
        self.portGraphics.setPath(build_ellipse(self.ui.port.boundingRect()))
        self.portGraphics.setPen(QtGui.QPen(QtCore.Qt.darkRed))
        self.portGraphics.setBrush(QtCore.Qt.red)
        self.portGraphics.adjustSize()

from PyQt4 import QtCore, QtGui
from Ui_QFlowComponentInstance import Ui_QFlowComponentInstance

# probably needs to be derived from QGraphicsItem (not a widget)
# which would force getting rid of the auto-layout stuff, are there any other options?
class QFlowComponentInstance(QtGui.QWidget):
    def __init__(self, parent = None):
        super(QFlowComponentInstance, self).__init__(parent)
        self.ui = Ui_QFlowComponentInstance()
        self.ui.setupUi(self)

    @classmethod
    def fromDefinition(cls, parent, definitionDict):
        self = QFlowComponentInstance(parent)
        inputPortDicts = definitionDict.get("InputPorts", [])
        outputPortDicts = definitionDict.Get("OutputPorts", [])

        for inputPortDict in inputPortDicts:
            self._addInputPort(inputPortDict)

        for outputPortDict in outputPortDicts:
            self._addOutputPort(outputPortDict)

        self.adjustSize()

    def _addInputPort(inputPortDict):
        port = QFlowComponentInstancePort.fromDict(self.ui.inputPortFrame,
                                                   inputPortDict,
                                                   QFlowComponentInstancePort.PortType.Input)
        return port

    def _addOutputPort(outputPortDict):
        port = QFlowComponentInstancePort.fromDict(self.ui.outputPortFrame,
                                                   outputPortDict,
                                                   QFlowComponentInstancePort.PortType.Output)
        return port

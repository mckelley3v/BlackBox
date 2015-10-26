from PyQt4 import QtCore, QtGui
from QFlowComponentInstancePort import QFlowComponentInstancePort
from Ui_QFlowComponentInstance import Ui_QFlowComponentInstance

def make_component_instance_title(instanceName, definitionName):
    return "%s : %s" % (instanceName, definitionName) if instanceName else definitionName

# probably needs to be derived from QGraphicsItem (not a widget)
# which would force getting rid of the auto-layout stuff, are there any other options?
class QFlowComponentInstance(QtGui.QWidget):
    def __init__(self, parent = None):
        super(QFlowComponentInstance, self).__init__(parent)
        self.ui = Ui_QFlowComponentInstance()
        self.ui.setupUi(self)

    @classmethod
    def fromDefinition(cls, parent, definitionDict, instanceName = None):
        self = QFlowComponentInstance(parent)
        self.setDict(definitionDict, instanceName)
        return self

    def clear(self):
        # implement this
        pass

    def setDict(self, definitionDict, instanceName = None):
        self.clear()

        title = make_component_instance_title(instanceName, definitionDict.get("Name"))
        self.ui.instanceGroup.setTitle(title)
        inputPortDicts = definitionDict.get("InputPorts", [])
        outputPortDicts = definitionDict.get("OutputPorts", [])

        for inputPortDict in inputPortDicts:
            self._addInputPort(inputPortDict)

        for outputPortDict in outputPortDicts:
            self._addOutputPort(outputPortDict)

        return self

    def _addInputPort(self, inputPortDict):
        port = QFlowComponentInstancePort.fromDict(self.ui.inputPortFrame,
                                                   inputPortDict,
                                                   QFlowComponentInstancePort.PortType.Input)
        self.ui.inputPortFrameLayout.addWidget(port)
        return port

    def _addOutputPort(self, outputPortDict):
        port = QFlowComponentInstancePort.fromDict(self.ui.outputPortFrame,
                                                   outputPortDict,
                                                   QFlowComponentInstancePort.PortType.Output)
        self.ui.outputPortFrameLayout.addWidget(port)
        return port

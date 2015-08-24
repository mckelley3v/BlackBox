from PyQt4 import QtCore, QtGui
from Ui_FlowComponentInstance import Ui_FlowComponentInstance

class FlowComponentInstance(QtGui.QWidget):
    def __init__(self, parent = None):
        super(FlowComponentInstance, self).__init__(parent)
        self.ui = Ui_FlowComponentInstance()
        self.ui.setupUi(self)
        self.m_flowComponentDefinitionName = ""

    def get_flowComponentDefinitionName(self):
        return self.m_flowComponentDefinitionName

    def set_flowComponentDefinitionName(self, value):
        self.m_flowComponentDefinitionName = value

    flowComponentDefinitionName = QtCore.pyqtProperty(str, get_flowComponentDefinitionName, set_flowComponentDefinitionName)
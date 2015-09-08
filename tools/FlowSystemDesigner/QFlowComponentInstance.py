from PyQt4 import QtCore, QtGui
from Ui_QFlowComponentInstance import Ui_QFlowComponentInstance

class QFlowComponentInstance(QtGui.QWidget):
    def __init__(self, parent = None):
        super(QFlowComponentInstance, self).__init__(parent)
        self.ui = Ui_QFlowComponentInstance()
        self.ui.setupUi(self)
        self.m_flowComponentDefinitionName = ""

    def get_flowComponentDefinitionName(self):
        return self.m_flowComponentDefinitionName

    def set_flowComponentDefinitionName(self, value):
        self.m_flowComponentDefinitionName = value

    flowComponentDefinitionName = QtCore.pyqtProperty(str, get_flowComponentDefinitionName, set_flowComponentDefinitionName)
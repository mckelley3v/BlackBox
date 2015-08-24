from PyQt4 import QtCore, QtGui
from Ui_FlowSystemDesigner import Ui_FlowSystemDesigner

class FlowSystemDesigner(QtGui.QMainWindow):
    def __init__(self, parent = None):
        super(FlowSystemDesigner, self).__init__(parent)
        self.ui = Ui_FlowSystemDesigner()
        self.ui.setupUi(self)

    def newProject(self):
        print "newProject"

    def openProject(self):
        print "openProject"

    def saveProject(self):
        print "saveProject"

    def saveProjectAs(self):
        print "saveProjectAs"

    def helpAbout(self):
        print "helpAbout"

    def addComponentDefinition(self):
        print "addComponentDefinition"

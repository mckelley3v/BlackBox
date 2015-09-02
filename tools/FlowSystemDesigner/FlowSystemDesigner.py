import Flow
import os.path
import traceback
from PyQt4 import QtCore, QtGui
from Ui_FlowSystemDesigner import Ui_FlowSystemDesigner

class FlowSystemDesigner(QtGui.QMainWindow):
    def __init__(self, parent = None):
        super(FlowSystemDesigner, self).__init__(parent)
        self.ui = Ui_FlowSystemDesigner()
        self.ui.setupUi(self)
        self.activeProject = None

    def newProject(self):
        filePath = QtGui.QFileDialog.getSaveFileName(self, caption = "Flow System", filter = "*.json")
        if filePath is not None:
            try:
                filePathStr = str(filePath)
                projectName = os.path.splitext(os.path.basename(filePathStr))[0]
                self.activeProject = Flow.SystemDefinitionBuilder.from_new(projectName)
                with open(filePathStr, "w") as fout:
                    self.activeProject.save(fout)
            except:
                traceback.print_exc()

    def openProject(self):
        print "openProject"

    def saveProject(self):
        print "saveProject"

    def saveProjectAs(self):
        print "saveProjectAs"

    def helpAbout(self):
        print "helpAbout"

    def addComponentDefinition(self):
        if self.activeProject is None:
            return

        filePath = QtGui.QFileDialog.getOpenFileName(self, caption = "Flow Component Definition", filter = "*.json")

        if filePath is not None:
            try:
                componentDefinition = self.activeProject.load_component_definition(str(filePath))
                if componentDefinition is not None:
                    self.ui.componentDefinitionList.addItem(QtCore.QString(componentDefinition.name))
            except:
                traceback.print_exc()

    def showComponentDefinition(self, componentDefinitionName):
        if self.activeProject is None:
            return

        componentDefinition = self.activeProject.component_definitions.get(str(componentDefinitionName))
        if componentDefinition is not None:
            self.ui.flowComponentDefinitionEditor.setFlowComponentDefinition(componentDefinition)

import Flow
import os.path
import traceback
from PyQt4 import QtCore, QtGui
from Ui_FlowSystemDesigner import Ui_FlowSystemDesigner

class FlowSystemDesigner(QtGui.QMainWindow):
    activeProjectChanged = QtCore.pyqtSignal(name = "activeProjectChanged")

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

            self.activeProjectChanged.emit()

    def openProject(self):
        filePath = QtGui.QFileDialog.getOpenFileName(self, caption = "Flow Component Definition", filter = "*.json")
        if filePath is not None:
            filePathStr = str(filePath)
            try:
                with open(filePathStr, "r") as fin:
                    self.activeProject = Flow.SystemDefinitionBuilder.from_file(fin)
            except:
                traceback.print_exc()

            self.activeProjectChanged.emit()

    def saveProject(self):
        if self.activeProject is None:
            return

        try:
            with open(self.activeProject.path, "w") as fout:
                self.activeProject.save(fout)
        except:
            traceback.print_exc()

    def saveProjectAs(self):
        if self.activeProject is None:
            return

        filePath = QtGui.QFileDialog.getSaveFileName(self, caption = "Flow System", filter = "*.json")
        if filePath is not None:
            filePathStr = str(filePath)
            projectName = os.path.splitext(os.path.basename(filePathStr))[0]
            self.activeProject.name = projectName
            try:
                with open(filePathStr, "w") as fout:
                    self.activeProject.save(fout)
            except:
                traceback.print_exc()

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

                self.activeProjectChanged.emit()
            except:
                traceback.print_exc()

    def showComponentDefinition(self, componentDefinitionName):
        if self.activeProject is None:
            return

        componentDefinition = self.activeProject.component_definitions.get(str(componentDefinitionName))
        if componentDefinition is not None:
            self.ui.flowComponentDefinitionEditor.setFlowComponentDefinition(componentDefinition)

    def refreshProject(self):
        self.ui.componentDefinitionList.clear()

        if self.activeProject is not None:
            try:
                for componentDefinitionName in self.activeProject.component_definitions.iterkeys():
                    self.ui.componentDefinitionList.addItem(QtCore.QString(componentDefinitionName))

            except:
                traceback.print_exc()

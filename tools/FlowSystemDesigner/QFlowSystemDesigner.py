import Flow
import os.path
import traceback
from PyQt4 import QtCore, QtGui
from Ui_QFlowSystemDesigner import Ui_QFlowSystemDesigner

class QFlowSystemDesigner(QtGui.QMainWindow):
    activeProjectChanged = QtCore.pyqtSignal(name = "activeProjectChanged")

    def __init__(self, parent = None):
        super(QFlowSystemDesigner, self).__init__(parent)
        self.ui = Ui_QFlowSystemDesigner()
        self.ui.setupUi(self)
        self.activeProject = None
        self.refreshProject()

    def newProject(self):
        filePath = QtGui.QFileDialog.getSaveFileName(self, caption = "Flow System", filter = "*.json")
        if filePath:
            try:
                filePathStr = str(filePath)
                projectName = os.path.splitext(os.path.basename(filePathStr))[0]
                self.activeProject = Flow.SystemDefinitionBuilder.from_new(projectName)
                with open(filePathStr, "w") as fout:
                    self.activeProject.save(fout)
            except:
                self.showException()

            self.activeProjectChanged.emit()

    def openProject(self):
        filePath = QtGui.QFileDialog.getOpenFileName(self, caption = "Flow Component Definition", filter = "*.json")
        if filePath:
            filePathStr = str(filePath)
            try:
                with open(filePathStr, "r") as fin:
                    self.activeProject = Flow.SystemDefinitionBuilder.from_file(fin)
            except:
                self.showException()

            self.activeProjectChanged.emit()

    def saveProject(self):
        if self.activeProject is None:
            return

        try:
            with open(self.activeProject.path, "w") as fout:
                self.activeProject.save(fout)
        except:
            self.showException()

    def saveProjectAs(self):
        if self.activeProject is None:
            return

        filePath = QtGui.QFileDialog.getSaveFileName(self, caption = "Flow System", filter = "*.json")
        if filePath:
            filePathStr = str(filePath)
            projectName = os.path.splitext(os.path.basename(filePathStr))[0]
            self.activeProject.name = projectName
            try:
                with open(filePathStr, "w") as fout:
                    self.activeProject.save(fout)
            except:
                self.showException()

    def helpAbout(self):
        QtGui.QMessageBox.information(self, self.windowTitle(), self.ui.actionHelpAbout.text())

    def addComponentDefinition(self):
        if self.activeProject is None:
            return

        filePath = QtGui.QFileDialog.getOpenFileName(self, caption = "Flow Component Definition", filter = "*.json")

        if filePath:
            try:
                componentDefinition = self.activeProject.load_component_definition(str(filePath))
                if componentDefinition is not None:
                    self.activeProjectChanged.emit()
            except:
                self.showException()

    def showComponentDefinition(self, componentDefinitionName):
        try:
            if self.activeProject is None:
                return

            componentDefinition = self.activeProject.component_definitions.get(str(componentDefinitionName))
            if componentDefinition is not None:
                componentDefinitionDict = componentDefinition.as_dict()
                self.ui.propertiesDictViewer.setDict(componentDefinitionDict)
                self.ui.componentDefinitionViewer.setDict(componentDefinitionDict)

        except:
            self.showException()

    def refreshProject(self):
        try:
            hasProject = self.activeProject is not None

            # consider how to not erase any active selections on these widgets
            self.ui.componentDefinitionList.clear()
            self.ui.propertiesDictViewer.clear()
            self.ui.componentDefinitionViewer.clear()
            self.ui.actionFileSave.setEnabled(hasProject)
            self.ui.actionFileSaveAs.setEnabled(hasProject)
            self.ui.menuProject.setEnabled(hasProject)

            if hasProject:
                for componentDefinitionName in self.activeProject.component_definitions.iterkeys():
                    self.ui.componentDefinitionList.addItem(unicode(componentDefinitionName))
        except:
            self.showException()

    def showException(self):
        QtGui.QMessageBox.critical(self, self.windowTitle(), unicode(traceback.format_exc()))


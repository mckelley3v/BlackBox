from PyQt4 import QtGui, QtDesigner
from QFlowComponentDefinitionEditor import QFlowComponentDefinitionEditor

class QFlowComponentDefinitionEditorPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QFlowComponentDefinitionEditorPlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return QFlowComponentDefinitionEditor(parent)

    def name(self):
        return "QFlowComponentDefinitionEditor"

    def group(self):
        return "Flow"

    def icon(self):
        return QtGui.QIcon()

    def toolTip(self):
        return ""

    def whatsThis(self):
        return ""

    def isContainer(self):
        return False

    def domXml(self):
        return """<ui><widget class="QFlowComponentDefinitionEditor" name="componentDefinition"/></ui>"""
 
    def includeFile(self):
        return "QFlowComponentDefinitionEditor"

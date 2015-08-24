from PyQt4 import QtGui, QtDesigner
from FlowComponentDefinitionEditor import FlowComponentDefinitionEditor

class FlowComponentDefinitionEditorPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(FlowComponentDefinitionEditorPlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return FlowComponentDefinitionEditor(parent)

    def name(self):
        return 'FlowComponentDefinitionEditor'

    def group(self):
        return 'Flow'

    def icon(self):
        return QtGui.QIcon()

    def toolTip(self):
        return ""

    def whatsThis(self):
        return ""

    def isContainer(self):
        return False

    def domXml(self):
        return '<widget class="FlowComponentDefinitionEditor" name="flowComponentDefinitionEditor"/>\n'
 
    def includeFile(self):
        return 'FlowComponentDefinitionEditor'

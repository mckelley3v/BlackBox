from PyQt4 import QtGui, QtDesigner
from QFlowComponentInstancePort import QFlowComponentInstancePort

class QFlowComponentInstancePortPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QFlowComponentInstancePortPlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return QFlowComponentInstancePort(parent)

    def name(self):
        return "QFlowComponentInstancePort"

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
        return """<ui><widget class="QFlowComponentInstancePort" name="componentPort"/></ui>"""

    def includeFile(self):
        return "QFlowComponentInstancePort"

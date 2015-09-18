from PyQt4 import QtGui, QtDesigner
from QFlowComponentInstance import QFlowComponentInstance

class QFlowComponentInstancePlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QFlowComponentInstancePlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return QFlowComponentInstance(parent)

    def name(self):
        return "QFlowComponentInstance"

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
        return """<ui><widget class="QFlowComponentInstance" name="componentInstance"/></ui>"""
 
    def includeFile(self):
        return "QFlowComponentInstance"

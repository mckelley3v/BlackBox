from PyQt4 import QtGui, QtDesigner
from FlowComponentInstance import FlowComponentInstance

class FlowComponentInstancePlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(FlowComponentInstancePlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return FlowComponentInstance(parent)

    def name(self):
        return 'FlowComponentInstance'

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
        return '<widget class="FlowComponentInstance" name="flowComponentInstance"/>\n'
 
    def includeFile(self):
        return 'FlowComponentInstance'

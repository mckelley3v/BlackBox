from PyQt4 import QtGui, QtDesigner
from QFlowSystemEditorView import QFlowSystemEditorView

class QFlowSystemEditorViewPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QFlowSystemEditorViewPlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return QFlowSystemEditorView(parent)

    def name(self):
        return "QFlowSystemEditorView"

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
        return """
<ui>
    <widget class="QFlowSystemEditorView" name="systemView"/>
    <customwidgets>
        <customwidget>
            <class>QFlowSystemEditorView</class>
            <extends>QGraphicsView</extends>
            <header>QFlowSystemEditorView.h</header>
        </customwidget>
    </customwidgets>
</ui>
"""
 
    def includeFile(self):
        return "QFlowSystemEditorView"

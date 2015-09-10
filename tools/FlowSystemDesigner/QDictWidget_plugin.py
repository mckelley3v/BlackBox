from PyQt4 import QtGui, QtDesigner
from QDictWidget import QDictWidget

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
        return QDictWidget(parent)

    def name(self):
        return "Dictionary Widget"

    def group(self):
        return "Item Widgets (Item-Based)"

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
    <widget class="QDictWidget" name="dictWidget"/>
    <customwidgets>
        <customwidget>
            <class>QDictWidget</class>
            <extends>QTreeWidget</extends>
            <header>QDictWidget.h</header>
        </customwidget>
    </customwidgets>
</ui>
"""
 
    def includeFile(self):
        return "QDictWidget"

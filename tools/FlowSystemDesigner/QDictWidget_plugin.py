﻿from PyQt4 import QtGui, QtDesigner
from QDictWidget import QDictWidget

class QDictWidgetPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QDictWidgetPlugin, self).__init__(parent)
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
        return "QDictWidget"

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
    <widget class="QDictWidget" name="dict"/>
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

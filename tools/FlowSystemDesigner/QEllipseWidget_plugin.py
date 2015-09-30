from PyQt4 import QtGui, QtDesigner
from QEllipseWidget import QEllipseWidget

class QEllipseWidgetPlugin(QtDesigner.QPyDesignerCustomWidgetPlugin):
    def __init__(self, parent = None):
        super(QEllipseWidgetPlugin, self).__init__(parent)
        self.initialized = False

    def initialize(self, core):
        if self.initialized:
            return
        self.initialized = True

    def isInitialized(self):
        return self.initialized

    def createWidget(self, parent):
        return QEllipseWidget(parent)

    def name(self):
        return "QEllipseWidget"

    def group(self):
        return "Containers"

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
    <widget class="QEllipseWidget" name="ellipse"/>
    <customwidgets>
        <customwidget>
            <class>QEllipseWidget</class>
            <extends>QWidget</extends>
            <header>QEllipseWidget.h</header>
        </customwidget>
    </customwidgets>
</ui>
"""
 
    def includeFile(self):
        return "QEllipseWidget"

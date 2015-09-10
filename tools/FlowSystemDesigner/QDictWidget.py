from PyQt4 import QtCore, QtGui
#from Ui_QDictWidget import Ui_QDictWidget
from collections import OrderedDict

class QDictWidget(QtGui.QTreeWidget):
    def __init__(self,
                 parent = None,
                 initDict = {}):
        super(QDictWidget, self).__init__(parent)
        #self.ui = Ui_QDictWidget()
        #self.ui.setupUi(self)
        QDictWidget.fill_item(self.invisibleRootItem(), initDict)

    @staticmethod
    def fill_item(item, value):
        item.setExpanded(True)
        if (isinstance(value, dict) or
            isinstance(value, OrderedDict)):
            for key, val in value.iteritems():
                child = QtGui.QTreeWidgetItem()
                child.setText(0, QtCore.QString(key))
                item.addChild(child)
                QDictWidget.fill_item(child, val)
        elif isinstance(value, list):
            for val in value:
                child = QtGui.QTreeWidgetItem()
                item.addChild(child)

                if (isinstance(val, dict) or
                    isinstance(val, OrderedDict)):
                    child.setText(0, '[dict]')
                    QDictWidget.fill_item(child, val)
                elif isinstance(val, list):
                    child.setText(0, '[list]')
                    QDictWidget.fill_item(child, val)
                else:
                    child.setText(0, unicode(val))
                child.setExpanded(True)
        else:
            child = QtGui.QTreeWidgetItem()
            child.setText(0, unicode(value))
            item.addChild(child)

    def setDict(self, valueDict):
      self.clear()
      QDictWidget.fill_item(self.invisibleRootItem(), valueDict)

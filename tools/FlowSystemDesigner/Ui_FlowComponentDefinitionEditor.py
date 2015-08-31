# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\Mike\Code\BlackBox\tools\FlowSystemDesigner\Ui_FlowComponentDefinitionEditor.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_FlowComponentDefinitionEditor(object):
    def setupUi(self, FlowComponentDefinitionEditor):
        FlowComponentDefinitionEditor.setObjectName(_fromUtf8("FlowComponentDefinitionEditor"))
        FlowComponentDefinitionEditor.resize(482, 357)
        FlowComponentDefinitionEditor.setProperty("flowComponentDefinitionFile", _fromUtf8(""))
        self.verticalLayout = QtGui.QVBoxLayout(FlowComponentDefinitionEditor)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.flowComponentDefinitionGroup = QtGui.QGroupBox(FlowComponentDefinitionEditor)
        self.flowComponentDefinitionGroup.setObjectName(_fromUtf8("flowComponentDefinitionGroup"))
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.flowComponentDefinitionGroup)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, -1)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.interfaceGroups = QtGui.QToolBox(self.flowComponentDefinitionGroup)
        self.interfaceGroups.setObjectName(_fromUtf8("interfaceGroups"))
        self.inputPortsGroup = QtGui.QWidget()
        self.inputPortsGroup.setGeometry(QtCore.QRect(0, 0, 480, 252))
        self.inputPortsGroup.setObjectName(_fromUtf8("inputPortsGroup"))
        self.gridLayout_8 = QtGui.QGridLayout(self.inputPortsGroup)
        self.gridLayout_8.setMargin(0)
        self.gridLayout_8.setObjectName(_fromUtf8("gridLayout_8"))
        self.inputPortsTable = QtGui.QTableWidget(self.inputPortsGroup)
        self.inputPortsTable.setVerticalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.inputPortsTable.setHorizontalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.inputPortsTable.setRowCount(0)
        self.inputPortsTable.setColumnCount(4)
        self.inputPortsTable.setObjectName(_fromUtf8("inputPortsTable"))
        item = QtGui.QTableWidgetItem()
        self.inputPortsTable.setHorizontalHeaderItem(0, item)
        item = QtGui.QTableWidgetItem()
        self.inputPortsTable.setHorizontalHeaderItem(1, item)
        item = QtGui.QTableWidgetItem()
        self.inputPortsTable.setHorizontalHeaderItem(2, item)
        item = QtGui.QTableWidgetItem()
        self.inputPortsTable.setHorizontalHeaderItem(3, item)
        self.inputPortsTable.verticalHeader().setVisible(False)
        self.inputPortsTable.verticalHeader().setDefaultSectionSize(19)
        self.gridLayout_8.addWidget(self.inputPortsTable, 0, 0, 1, 1)
        self.interfaceGroups.addItem(self.inputPortsGroup, _fromUtf8(""))
        self.outputGroup = QtGui.QWidget()
        self.outputGroup.setGeometry(QtCore.QRect(0, 0, 98, 71))
        self.outputGroup.setObjectName(_fromUtf8("outputGroup"))
        self.gridLayout_9 = QtGui.QGridLayout(self.outputGroup)
        self.gridLayout_9.setMargin(0)
        self.gridLayout_9.setObjectName(_fromUtf8("gridLayout_9"))
        self.outputPortsTable = QtGui.QTableWidget(self.outputGroup)
        self.outputPortsTable.setVerticalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.outputPortsTable.setHorizontalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.outputPortsTable.setRowCount(0)
        self.outputPortsTable.setColumnCount(2)
        self.outputPortsTable.setObjectName(_fromUtf8("outputPortsTable"))
        item = QtGui.QTableWidgetItem()
        self.outputPortsTable.setHorizontalHeaderItem(0, item)
        item = QtGui.QTableWidgetItem()
        self.outputPortsTable.setHorizontalHeaderItem(1, item)
        self.outputPortsTable.verticalHeader().setVisible(False)
        self.outputPortsTable.verticalHeader().setDefaultSectionSize(19)
        self.gridLayout_9.addWidget(self.outputPortsTable, 0, 0, 1, 1)
        self.interfaceGroups.addItem(self.outputGroup, _fromUtf8(""))
        self.annotationGroup = QtGui.QWidget()
        self.annotationGroup.setGeometry(QtCore.QRect(0, 0, 480, 252))
        self.annotationGroup.setObjectName(_fromUtf8("annotationGroup"))
        self.gridLayout_10 = QtGui.QGridLayout(self.annotationGroup)
        self.gridLayout_10.setMargin(0)
        self.gridLayout_10.setObjectName(_fromUtf8("gridLayout_10"))
        self.annotationsTable = QtGui.QTableWidget(self.annotationGroup)
        self.annotationsTable.setVerticalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.annotationsTable.setHorizontalScrollMode(QtGui.QAbstractItemView.ScrollPerPixel)
        self.annotationsTable.setObjectName(_fromUtf8("annotationsTable"))
        self.annotationsTable.setColumnCount(1)
        self.annotationsTable.setRowCount(0)
        item = QtGui.QTableWidgetItem()
        self.annotationsTable.setHorizontalHeaderItem(0, item)
        self.annotationsTable.verticalHeader().setVisible(False)
        self.annotationsTable.verticalHeader().setDefaultSectionSize(19)
        self.gridLayout_10.addWidget(self.annotationsTable, 0, 0, 1, 1)
        self.interfaceGroups.addItem(self.annotationGroup, _fromUtf8(""))
        self.verticalLayout_2.addWidget(self.interfaceGroups)
        self.verticalLayout.addWidget(self.flowComponentDefinitionGroup)

        self.retranslateUi(FlowComponentDefinitionEditor)
        self.interfaceGroups.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(FlowComponentDefinitionEditor)

    def retranslateUi(self, FlowComponentDefinitionEditor):
        FlowComponentDefinitionEditor.setWindowTitle(_translate("FlowComponentDefinitionEditor", "Flow Component Definition Editor", None))
        self.flowComponentDefinitionGroup.setTitle(_translate("FlowComponentDefinitionEditor", "<FlowComponentDefinitionName>", None))
        item = self.inputPortsTable.horizontalHeaderItem(0)
        item.setText(_translate("FlowComponentDefinitionEditor", "PortName", None))
        item = self.inputPortsTable.horizontalHeaderItem(1)
        item.setText(_translate("FlowComponentDefinitionEditor", "TypeName", None))
        item = self.inputPortsTable.horizontalHeaderItem(2)
        item.setText(_translate("FlowComponentDefinitionEditor", "IsOptional", None))
        item = self.inputPortsTable.horizontalHeaderItem(3)
        item.setText(_translate("FlowComponentDefinitionEditor", "IsMultiplex", None))
        self.interfaceGroups.setItemText(self.interfaceGroups.indexOf(self.inputPortsGroup), _translate("FlowComponentDefinitionEditor", "Input Ports", None))
        item = self.outputPortsTable.horizontalHeaderItem(0)
        item.setText(_translate("FlowComponentDefinitionEditor", "PortName", None))
        item = self.outputPortsTable.horizontalHeaderItem(1)
        item.setText(_translate("FlowComponentDefinitionEditor", "TypeName", None))
        self.interfaceGroups.setItemText(self.interfaceGroups.indexOf(self.outputGroup), _translate("FlowComponentDefinitionEditor", "Output Ports", None))
        item = self.annotationsTable.horizontalHeaderItem(0)
        item.setText(_translate("FlowComponentDefinitionEditor", "Process", None))
        self.interfaceGroups.setItemText(self.interfaceGroups.indexOf(self.annotationGroup), _translate("FlowComponentDefinitionEditor", "Annotations", None))


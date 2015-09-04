# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\Mike\Code\BlackBox\tools\FlowSystemDesigner\Ui_FlowComponentInstance.ui'
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

class Ui_FlowComponentInstance(object):
    def setupUi(self, FlowComponentInstance):
        FlowComponentInstance.setObjectName(_fromUtf8("FlowComponentInstance"))
        FlowComponentInstance.resize(266, 209)
        FlowComponentInstance.setProperty("flowComponentDefinitionName", _fromUtf8(""))
        self.verticalLayout = QtGui.QVBoxLayout(FlowComponentInstance)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.name = QtGui.QGroupBox(FlowComponentInstance)
        self.name.setObjectName(_fromUtf8("name"))
        self.verticalLayout.addWidget(self.name)

        self.retranslateUi(FlowComponentInstance)
        QtCore.QMetaObject.connectSlotsByName(FlowComponentInstance)

    def retranslateUi(self, FlowComponentInstance):
        FlowComponentInstance.setWindowTitle(_translate("FlowComponentInstance", "FlowComponentInstance", None))
        self.name.setTitle(_translate("FlowComponentInstance", "(name)", None))


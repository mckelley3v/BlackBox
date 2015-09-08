# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\Mike\Code\BlackBox\tools\FlowSystemDesigner\Ui_QFlowComponentInstance.ui'
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

class Ui_QFlowComponentInstance(object):
    def setupUi(self, QFlowComponentInstance):
        QFlowComponentInstance.setObjectName(_fromUtf8("QFlowComponentInstance"))
        QFlowComponentInstance.resize(266, 209)
        QFlowComponentInstance.setProperty("flowComponentDefinitionName", _fromUtf8(""))
        self.verticalLayout = QtGui.QVBoxLayout(QFlowComponentInstance)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.name = QtGui.QGroupBox(QFlowComponentInstance)
        self.name.setObjectName(_fromUtf8("name"))
        self.verticalLayout.addWidget(self.name)

        self.retranslateUi(QFlowComponentInstance)
        QtCore.QMetaObject.connectSlotsByName(QFlowComponentInstance)

    def retranslateUi(self, QFlowComponentInstance):
        QFlowComponentInstance.setWindowTitle(_translate("QFlowComponentInstance", "QFlowComponentInstance", None))
        self.name.setTitle(_translate("QFlowComponentInstance", "(name)", None))


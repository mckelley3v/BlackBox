# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\mkelley\Personal\Code\BlackBox\tools\FlowSystemDesigner\Ui_QFlowComponentInstance.ui'
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
        QFlowComponentInstance.resize(194, 108)
        self.verticalLayout = QtGui.QVBoxLayout(QFlowComponentInstance)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.portFrame = QtGui.QFrame(QFlowComponentInstance)
        self.portFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.portFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.portFrame.setObjectName(_fromUtf8("portFrame"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.portFrame)
        self.horizontalLayout.setMargin(0)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.inputPortFrame = QtGui.QFrame(self.portFrame)
        self.inputPortFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.inputPortFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.inputPortFrame.setObjectName(_fromUtf8("inputPortFrame"))
        self.verticalLayout_1 = QtGui.QVBoxLayout(self.inputPortFrame)
        self.verticalLayout_1.setMargin(0)
        self.verticalLayout_1.setObjectName(_fromUtf8("verticalLayout_1"))
        self.horizontalLayout.addWidget(self.inputPortFrame)
        self.outputPortFrame = QtGui.QFrame(self.portFrame)
        self.outputPortFrame.setLayoutDirection(QtCore.Qt.RightToLeft)
        self.outputPortFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.outputPortFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.outputPortFrame.setObjectName(_fromUtf8("outputPortFrame"))
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.outputPortFrame)
        self.verticalLayout_2.setMargin(0)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.horizontalLayout.addWidget(self.outputPortFrame)
        self.verticalLayout.addWidget(self.portFrame)
        spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem)

        self.retranslateUi(QFlowComponentInstance)
        QtCore.QMetaObject.connectSlotsByName(QFlowComponentInstance)

    def retranslateUi(self, QFlowComponentInstance):
        pass


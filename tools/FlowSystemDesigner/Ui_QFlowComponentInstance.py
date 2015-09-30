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
        self.instanceGroup = QtGui.QGroupBox(QFlowComponentInstance)
        self.instanceGroup.setObjectName(_fromUtf8("instanceGroup"))
        self.instanceGroupLayout = QtGui.QVBoxLayout(self.instanceGroup)
        self.instanceGroupLayout.setMargin(0)
        self.instanceGroupLayout.setObjectName(_fromUtf8("instanceGroupLayout"))
        self.portFrame = QtGui.QFrame(self.instanceGroup)
        self.portFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.portFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.portFrame.setObjectName(_fromUtf8("portFrame"))
        self.portFrameLayout = QtGui.QHBoxLayout(self.portFrame)
        self.portFrameLayout.setMargin(0)
        self.portFrameLayout.setObjectName(_fromUtf8("portFrameLayout"))
        self.inputPortFrame = QtGui.QFrame(self.portFrame)
        self.inputPortFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.inputPortFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.inputPortFrame.setObjectName(_fromUtf8("inputPortFrame"))
        self.inputPortFrameLayout = QtGui.QVBoxLayout(self.inputPortFrame)
        self.inputPortFrameLayout.setMargin(0)
        self.inputPortFrameLayout.setObjectName(_fromUtf8("inputPortFrameLayout"))
        self.portFrameLayout.addWidget(self.inputPortFrame)
        self.outputPortFrame = QtGui.QFrame(self.portFrame)
        self.outputPortFrame.setLayoutDirection(QtCore.Qt.RightToLeft)
        self.outputPortFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.outputPortFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.outputPortFrame.setObjectName(_fromUtf8("outputPortFrame"))
        self.outputPortFrameLayout = QtGui.QVBoxLayout(self.outputPortFrame)
        self.outputPortFrameLayout.setMargin(0)
        self.outputPortFrameLayout.setObjectName(_fromUtf8("outputPortFrameLayout"))
        self.portFrameLayout.addWidget(self.outputPortFrame)
        self.instanceGroupLayout.addWidget(self.portFrame)
        spacerItem = QtGui.QSpacerItem(20, 93, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.instanceGroupLayout.addItem(spacerItem)
        self.verticalLayout.addWidget(self.instanceGroup)

        self.retranslateUi(QFlowComponentInstance)
        QtCore.QMetaObject.connectSlotsByName(QFlowComponentInstance)

    def retranslateUi(self, QFlowComponentInstance):
        pass


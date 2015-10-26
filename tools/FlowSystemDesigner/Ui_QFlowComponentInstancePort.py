# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\mkelley\Personal\Code\BlackBox\tools\FlowSystemDesigner\Ui_QFlowComponentInstancePort.ui'
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

class Ui_QFlowComponentInstancePort(object):
    def setupUi(self, QFlowComponentInstancePort):
        QFlowComponentInstancePort.setObjectName(_fromUtf8("QFlowComponentInstancePort"))
        QFlowComponentInstancePort.resize(94, 16)
        self.horizontalLayout = QtGui.QHBoxLayout(QFlowComponentInstancePort)
        self.horizontalLayout.setMargin(0)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.port = QEllipseWidget(QFlowComponentInstancePort)
        self.port.setObjectName(_fromUtf8("port"))
        self.horizontalLayout.addWidget(self.port)
        self.label = QtGui.QLabel(QFlowComponentInstancePort)
        self.label.setObjectName(_fromUtf8("label"))
        self.horizontalLayout.addWidget(self.label)

        self.retranslateUi(QFlowComponentInstancePort)
        QtCore.QMetaObject.connectSlotsByName(QFlowComponentInstancePort)

    def retranslateUi(self, QFlowComponentInstancePort):
        pass

from QEllipseWidget import QEllipseWidget

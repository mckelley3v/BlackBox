# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\mkelley\Personal\Code\BlackBox\tools\FlowSystemDesigner\Ui_QFlowSystemDesigner.ui'
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

class Ui_QFlowSystemDesigner(object):
    def setupUi(self, QFlowSystemDesigner):
        QFlowSystemDesigner.setObjectName(_fromUtf8("QFlowSystemDesigner"))
        QFlowSystemDesigner.resize(1024, 768)
        self.systemDesignerContents = QtGui.QWidget(QFlowSystemDesigner)
        self.systemDesignerContents.setObjectName(_fromUtf8("systemDesignerContents"))
        self.gridLayout = QtGui.QGridLayout(self.systemDesignerContents)
        self.gridLayout.setMargin(1)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.systemView = QFlowSystemEditorView(self.systemDesignerContents)
        self.systemView.setAcceptDrops(True)
        self.systemView.setObjectName(_fromUtf8("systemView"))
        self.gridLayout.addWidget(self.systemView, 0, 0, 1, 1)
        QFlowSystemDesigner.setCentralWidget(self.systemDesignerContents)
        self.menubar = QtGui.QMenuBar(QFlowSystemDesigner)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1024, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        self.menuView = QtGui.QMenu(self.menubar)
        self.menuView.setObjectName(_fromUtf8("menuView"))
        self.menuHelp = QtGui.QMenu(self.menubar)
        self.menuHelp.setObjectName(_fromUtf8("menuHelp"))
        self.menuProject = QtGui.QMenu(self.menubar)
        self.menuProject.setObjectName(_fromUtf8("menuProject"))
        self.menuEdit = QtGui.QMenu(self.menubar)
        self.menuEdit.setEnabled(False)
        self.menuEdit.setObjectName(_fromUtf8("menuEdit"))
        QFlowSystemDesigner.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(QFlowSystemDesigner)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        QFlowSystemDesigner.setStatusBar(self.statusbar)
        self.componentDefinitionListDock = QtGui.QDockWidget(QFlowSystemDesigner)
        self.componentDefinitionListDock.setObjectName(_fromUtf8("componentDefinitionListDock"))
        self.componentDefinitionListDockContents = QtGui.QWidget()
        self.componentDefinitionListDockContents.setObjectName(_fromUtf8("componentDefinitionListDockContents"))
        self.gridLayout_3 = QtGui.QGridLayout(self.componentDefinitionListDockContents)
        self.gridLayout_3.setMargin(0)
        self.gridLayout_3.setObjectName(_fromUtf8("gridLayout_3"))
        self.componentDefinitionList = QtGui.QListWidget(self.componentDefinitionListDockContents)
        self.componentDefinitionList.setDragEnabled(True)
        self.componentDefinitionList.setDragDropMode(QtGui.QAbstractItemView.DragOnly)
        self.componentDefinitionList.setObjectName(_fromUtf8("componentDefinitionList"))
        self.gridLayout_3.addWidget(self.componentDefinitionList, 0, 1, 1, 1)
        self.componentDefinitionListDock.setWidget(self.componentDefinitionListDockContents)
        QFlowSystemDesigner.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.componentDefinitionListDock)
        self.propertiesViewerDock = QtGui.QDockWidget(QFlowSystemDesigner)
        self.propertiesViewerDock.setObjectName(_fromUtf8("propertiesViewerDock"))
        self.propertiesViewerDockContents = QtGui.QWidget()
        self.propertiesViewerDockContents.setObjectName(_fromUtf8("propertiesViewerDockContents"))
        self.gridLayout_4 = QtGui.QGridLayout(self.propertiesViewerDockContents)
        self.gridLayout_4.setMargin(0)
        self.gridLayout_4.setObjectName(_fromUtf8("gridLayout_4"))
        self.propertiesDictViewer = QDictWidget(self.propertiesViewerDockContents)
        self.propertiesDictViewer.setObjectName(_fromUtf8("propertiesDictViewer"))
        self.propertiesDictViewer.headerItem().setText(0, _fromUtf8("1"))
        self.propertiesDictViewer.header().setVisible(False)
        self.gridLayout_4.addWidget(self.propertiesDictViewer, 0, 1, 1, 1)
        self.propertiesViewerDock.setWidget(self.propertiesViewerDockContents)
        QFlowSystemDesigner.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.propertiesViewerDock)
        self.componentDefinitionViewerDock = QtGui.QDockWidget(QFlowSystemDesigner)
        self.componentDefinitionViewerDock.setObjectName(_fromUtf8("componentDefinitionViewerDock"))
        self.componentDefinitionViewerDockContents = QtGui.QWidget()
        self.componentDefinitionViewerDockContents.setObjectName(_fromUtf8("componentDefinitionViewerDockContents"))
        self.gridLayout_2 = QtGui.QGridLayout(self.componentDefinitionViewerDockContents)
        self.gridLayout_2.setMargin(0)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.componentDefinitionViewer = QFlowComponentInstance(self.componentDefinitionViewerDockContents)
        self.componentDefinitionViewer.setObjectName(_fromUtf8("componentDefinitionViewer"))
        self.gridLayout_2.addWidget(self.componentDefinitionViewer, 0, 0, 1, 1)
        self.componentDefinitionViewerDock.setWidget(self.componentDefinitionViewerDockContents)
        QFlowSystemDesigner.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.componentDefinitionViewerDock)
        self.actionFileOpen = QtGui.QAction(QFlowSystemDesigner)
        self.actionFileOpen.setObjectName(_fromUtf8("actionFileOpen"))
        self.actionFileSave = QtGui.QAction(QFlowSystemDesigner)
        self.actionFileSave.setObjectName(_fromUtf8("actionFileSave"))
        self.actionFileSaveAs = QtGui.QAction(QFlowSystemDesigner)
        self.actionFileSaveAs.setObjectName(_fromUtf8("actionFileSaveAs"))
        self.actionFileExit = QtGui.QAction(QFlowSystemDesigner)
        self.actionFileExit.setObjectName(_fromUtf8("actionFileExit"))
        self.actionHelpAbout = QtGui.QAction(QFlowSystemDesigner)
        self.actionHelpAbout.setObjectName(_fromUtf8("actionHelpAbout"))
        self.actionViewComponentDefinitionList = QtGui.QAction(QFlowSystemDesigner)
        self.actionViewComponentDefinitionList.setCheckable(True)
        self.actionViewComponentDefinitionList.setObjectName(_fromUtf8("actionViewComponentDefinitionList"))
        self.actionViewComponentActiveDefinition = QtGui.QAction(QFlowSystemDesigner)
        self.actionViewComponentActiveDefinition.setCheckable(True)
        self.actionViewComponentActiveDefinition.setObjectName(_fromUtf8("actionViewComponentActiveDefinition"))
        self.actionFileNew = QtGui.QAction(QFlowSystemDesigner)
        self.actionFileNew.setObjectName(_fromUtf8("actionFileNew"))
        self.actionProjectAddComponentDefinition = QtGui.QAction(QFlowSystemDesigner)
        self.actionProjectAddComponentDefinition.setObjectName(_fromUtf8("actionProjectAddComponentDefinition"))
        self.actionUndo = QtGui.QAction(QFlowSystemDesigner)
        self.actionUndo.setObjectName(_fromUtf8("actionUndo"))
        self.actionRedo = QtGui.QAction(QFlowSystemDesigner)
        self.actionRedo.setObjectName(_fromUtf8("actionRedo"))
        self.actionCut = QtGui.QAction(QFlowSystemDesigner)
        self.actionCut.setObjectName(_fromUtf8("actionCut"))
        self.actionCopy = QtGui.QAction(QFlowSystemDesigner)
        self.actionCopy.setObjectName(_fromUtf8("actionCopy"))
        self.actionPaste = QtGui.QAction(QFlowSystemDesigner)
        self.actionPaste.setObjectName(_fromUtf8("actionPaste"))
        self.menuFile.addAction(self.actionFileNew)
        self.menuFile.addAction(self.actionFileOpen)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionFileSave)
        self.menuFile.addAction(self.actionFileSaveAs)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionFileExit)
        self.menuView.addAction(self.actionViewComponentDefinitionList)
        self.menuView.addAction(self.actionViewComponentActiveDefinition)
        self.menuHelp.addAction(self.actionHelpAbout)
        self.menuProject.addAction(self.actionProjectAddComponentDefinition)
        self.menuEdit.addAction(self.actionUndo)
        self.menuEdit.addAction(self.actionRedo)
        self.menuEdit.addSeparator()
        self.menuEdit.addAction(self.actionCut)
        self.menuEdit.addAction(self.actionCopy)
        self.menuEdit.addAction(self.actionPaste)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuEdit.menuAction())
        self.menubar.addAction(self.menuView.menuAction())
        self.menubar.addAction(self.menuProject.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(QFlowSystemDesigner)
        QtCore.QObject.connect(self.actionFileExit, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.close)
        QtCore.QObject.connect(self.actionHelpAbout, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.helpAbout)
        QtCore.QObject.connect(self.actionFileNew, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.newProject)
        QtCore.QObject.connect(self.actionFileOpen, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.openProject)
        QtCore.QObject.connect(self.actionFileSave, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.saveProject)
        QtCore.QObject.connect(self.actionFileSaveAs, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.saveProjectAs)
        QtCore.QObject.connect(self.actionViewComponentDefinitionList, QtCore.SIGNAL(_fromUtf8("toggled(bool)")), self.componentDefinitionListDock.setVisible)
        QtCore.QObject.connect(self.actionViewComponentActiveDefinition, QtCore.SIGNAL(_fromUtf8("toggled(bool)")), self.propertiesViewerDock.setVisible)
        QtCore.QObject.connect(self.componentDefinitionListDock, QtCore.SIGNAL(_fromUtf8("visibilityChanged(bool)")), self.actionViewComponentDefinitionList.setChecked)
        QtCore.QObject.connect(self.propertiesViewerDock, QtCore.SIGNAL(_fromUtf8("visibilityChanged(bool)")), self.actionViewComponentActiveDefinition.setChecked)
        QtCore.QObject.connect(self.actionProjectAddComponentDefinition, QtCore.SIGNAL(_fromUtf8("triggered()")), QFlowSystemDesigner.addComponentDefinition)
        QtCore.QObject.connect(self.componentDefinitionList, QtCore.SIGNAL(_fromUtf8("currentTextChanged(QString)")), QFlowSystemDesigner.showComponentDefinition)
        QtCore.QObject.connect(QFlowSystemDesigner, QtCore.SIGNAL(_fromUtf8("activeProjectChanged()")), QFlowSystemDesigner.refreshProject)
        QtCore.QMetaObject.connectSlotsByName(QFlowSystemDesigner)

    def retranslateUi(self, QFlowSystemDesigner):
        QFlowSystemDesigner.setWindowTitle(_translate("QFlowSystemDesigner", "Flow System Designer", None))
        self.menuFile.setTitle(_translate("QFlowSystemDesigner", "File", None))
        self.menuView.setTitle(_translate("QFlowSystemDesigner", "View", None))
        self.menuHelp.setTitle(_translate("QFlowSystemDesigner", "Help", None))
        self.menuProject.setTitle(_translate("QFlowSystemDesigner", "Project", None))
        self.menuEdit.setTitle(_translate("QFlowSystemDesigner", "Edit", None))
        self.componentDefinitionListDock.setWindowTitle(_translate("QFlowSystemDesigner", "Component Definition List", None))
        self.propertiesViewerDock.setWindowTitle(_translate("QFlowSystemDesigner", "Properties", None))
        self.componentDefinitionViewerDock.setWindowTitle(_translate("QFlowSystemDesigner", "Component Definition", None))
        self.actionFileOpen.setText(_translate("QFlowSystemDesigner", "Open...", None))
        self.actionFileOpen.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+O", None))
        self.actionFileSave.setText(_translate("QFlowSystemDesigner", "Save", None))
        self.actionFileSave.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+S", None))
        self.actionFileSaveAs.setText(_translate("QFlowSystemDesigner", "Save As", None))
        self.actionFileExit.setText(_translate("QFlowSystemDesigner", "Exit", None))
        self.actionHelpAbout.setText(_translate("QFlowSystemDesigner", "About", None))
        self.actionViewComponentDefinitionList.setText(_translate("QFlowSystemDesigner", "Component Definition List", None))
        self.actionViewComponentActiveDefinition.setText(_translate("QFlowSystemDesigner", "Component Definition", None))
        self.actionFileNew.setText(_translate("QFlowSystemDesigner", "New", None))
        self.actionFileNew.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+N", None))
        self.actionProjectAddComponentDefinition.setText(_translate("QFlowSystemDesigner", "Add Component Definition...", None))
        self.actionUndo.setText(_translate("QFlowSystemDesigner", "Undo", None))
        self.actionUndo.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+Z", None))
        self.actionRedo.setText(_translate("QFlowSystemDesigner", "Redo", None))
        self.actionRedo.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+Y", None))
        self.actionCut.setText(_translate("QFlowSystemDesigner", "Cut", None))
        self.actionCut.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+X", None))
        self.actionCopy.setText(_translate("QFlowSystemDesigner", "Copy", None))
        self.actionCopy.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+C", None))
        self.actionPaste.setText(_translate("QFlowSystemDesigner", "Paste", None))
        self.actionPaste.setShortcut(_translate("QFlowSystemDesigner", "Ctrl+V", None))

from QDictWidget import QDictWidget
from QFlowComponentInstance import QFlowComponentInstance
from QFlowSystemEditorView import QFlowSystemEditorView

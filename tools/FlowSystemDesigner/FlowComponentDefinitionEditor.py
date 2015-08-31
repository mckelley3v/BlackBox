import sys
import json
from PyQt4 import QtCore, QtGui
from Ui_FlowComponentDefinitionEditor import Ui_FlowComponentDefinitionEditor

def clear_table_widget(tableWidget):
    tableWidget.setRowCount(0)
    tableWidget.resizeColumnsToContents()
    return

def assign_dict_list_to_table(dictList, tableWidget):
    tableWidget.setRowCount(len(dictList))
    for rowIndex, dictEntry in enumerate(dictList):
        for colIndex in xrange(tableWidget.columnCount()):
            colName = str(tableWidget.horizontalHeaderItem(colIndex).text())
            colItem = QtGui.QTableWidgetItem(QtCore.QString(dictEntry.get(colName, "")))
            tableWidget.setItem(rowIndex, colIndex, colItem)
    tableWidget.resizeColumnsToContents()

class FlowComponentDefinitionEditor(QtGui.QWidget):
    def __init__(self, parent = None):
        super(FlowComponentDefinitionEditor, self).__init__(parent)
        self.ui = Ui_FlowComponentDefinitionEditor()
        self.ui.setupUi(self)
        self._clearTableWidgets()
        self.m_flowComponentDefinitionFile = ""

    def _get_flowComponentDefinitionFile(self):
        return self.m_flowComponentDefinitionFile

    def _set_flowComponentDefinitionFile(self, value):
        self.m_flowComponentDefinitionFile = value

    flowComponentDefinitionFile = QtCore.pyqtProperty(str, _get_flowComponentDefinitionFile, _set_flowComponentDefinitionFile)

    def setFlowComponentDefinitionFile(self, value):
        self._clearTableWidgets()

        if not value:
            return

        try:
            flowDefinition = ""
            with open(value, "r") as flowDefinitionFile:
                flowDefinition = flowDefinitionFile.read()
            flowDefinitionDict = json.loads(flowDefinition)
            print(flowDefinitionDict)
            name = flowDefinitionDict.get("Name", None)
            if not name is None:
                assign_dict_list_to_table(flowDefinitionDict.get("InputPorts", {}), self.ui.inputPortsTable)
                assign_dict_list_to_table(flowDefinitionDict.get("OutputPorts", {}), self.ui.outputPortsTable)
                assign_dict_list_to_table(flowDefinitionDict.get("Annotations", {}), self.ui.annotationsTable)

                self.m_flowComponentDefinitionFile = value
        except:
            e = sys.exc_info()[0]
            print(e)

    def _clearTableWidgets(self):
        clear_table_widget(self.ui.inputPortsTable)
        clear_table_widget(self.ui.outputPortsTable)
        clear_table_widget(self.ui.annotationsTable)


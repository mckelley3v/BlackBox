import Flow
import traceback
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
        self.FlowComponentDefinitionFile = ""

    def _get_flowComponentDefinitionFile(self):
        return self.FlowComponentDefinitionFile

    def _set_flowComponentDefinitionFile(self, value):
        self.FlowComponentDefinitionFile = value

    flowComponentDefinitionFile = QtCore.pyqtProperty(str, _get_flowComponentDefinitionFile, _set_flowComponentDefinitionFile)

    def setFlowComponentDefinitionFile(self, value):
        self._clearTableWidgets()

        if not value:
            return

        try:
            componentDefinition = None
            with open(value, "r") as flowDefinitionFile:
                componentDefinition = Flow.ComponentDefinition.fromFile(flowDefinitionFile)

            if not componentDefinition is None:
                self.ui.flowComponentDefinitionGroup.setTitle(QtCore.QString(componentDefinition.Name))
                assign_dict_list_to_table([portEntry.__dict__ for portEntry in componentDefinition.InputPorts], self.ui.inputPortsTable)
                assign_dict_list_to_table([portEntry.__dict__ for portEntry in componentDefinition.OutputPorts], self.ui.outputPortsTable)
                assign_dict_list_to_table([componentDefinition.Annotations], self.ui.annotationsTable)

                self.FlowComponentDefinitionFile = value
        except:
            traceback.print_exc()

    def _clearTableWidgets(self):
        clear_table_widget(self.ui.inputPortsTable)
        clear_table_widget(self.ui.outputPortsTable)
        clear_table_widget(self.ui.annotationsTable)


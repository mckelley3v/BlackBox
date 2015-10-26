import Flow
import traceback
from PyQt4 import QtCore, QtGui
from Ui_QFlowComponentDefinitionEditor import Ui_QFlowComponentDefinitionEditor

def clear_table_widget(tableWidget):
    tableWidget.setRowCount(0)
    tableWidget.resizeColumnsToContents()
    return

def assign_dict_list_to_table(dictList, tableWidget):
    tableWidget.setRowCount(len(dictList))
    for rowIndex, dictEntry in enumerate(dictList):
        for colIndex in xrange(tableWidget.columnCount()):
            colName = str(tableWidget.horizontalHeaderItem(colIndex).text())
            colItem = QtGui.QTableWidgetItem(unicode(dictEntry.get(colName, "")))
            tableWidget.setItem(rowIndex, colIndex, colItem)
    tableWidget.resizeColumnsToContents()

class QFlowComponentDefinitionEditor(QtGui.QWidget):
    def __init__(self, parent = None):
        super(QFlowComponentDefinitionEditor, self).__init__(parent)
        self.ui = Ui_QFlowComponentDefinitionEditor()
        self.ui.setupUi(self)
        self.componentDefinition = None
        self.clear()

    def setComponentDefinition(self, componentDefinition):
        try:
            self.clear()

            if not componentDefinition:
                return

            if componentDefinition is not None:
                self.ui.componentDefinitionGroup.setTitle(unicode(componentDefinition.name))
                assign_dict_list_to_table([portEntry.as_dict() for portEntry in componentDefinition.input_ports], self.ui.inputPortsTable)
                assign_dict_list_to_table([portEntry.as_dict() for portEntry in componentDefinition.output_ports], self.ui.outputPortsTable)
                assign_dict_list_to_table([componentDefinition.annotations], self.ui.annotationsTable)
                self.componentDefinition = componentDefinition

        except:
            self.clear()
            traceback.print_exc()

    def clear(self):
        self.componentDefinition = None
        clear_table_widget(self.ui.inputPortsTable)
        clear_table_widget(self.ui.outputPortsTable)
        clear_table_widget(self.ui.annotationsTable)


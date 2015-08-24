import json
from PyQt4 import QtCore, QtGui
from Ui_FlowComponentDefinitionEditor import Ui_FlowComponentDefinitionEditor

def assign_dict_list_to_table(dictList, tableWidget):
    tableWidget.setRowCount(len(dictList))
    for rowIndex, dictEntry in enumerate(dictList):
        for colIndex in xrange(tableWidget.getColCount()):
            colName = tableWidget.horizontalHeaderItem(colIndex).text()
            tableWidget.item(rowIndex, colIndex).setText(dictEntry.get(colName, ""))

class FlowComponentDefinitionEditor(QtGui.QWidget):
    def __init__(self, parent = None):
        super(FlowComponentDefinitionEditor, self).__init__(parent)
        self.ui = Ui_FlowComponentDefinitionEditor()
        self.ui.setupUi(self)
        self.m_flowComponentDefinitionFile = ""

    def get_flowComponentDefinitionFile(self):
        return self.m_flowComponentDefinitionFile

    def set_flowComponentDefinitionFile(self, value):
        try:
            flowDefinition = ""
            with open(value, "r") as flowDefinitionFile:
                flowDefinition = flowDefinitionFile.read()
            flowDefinitionDict = json.loads(flowDefinition)
            name = flowDefinitionDict.get("Name", None)
            if not name is None:
                assign_dict_list_to_table(flowDefinitionDict.get("InputPorts", {}), self.ui.inputPortsTable)
                assign_dict_list_to_table(flowDefinitionDict.get("OutputPorts", {}), self.ui.outputPortsTable)
                assign_dict_list_to_table(flowDefinitionDict.get("Annotations", {}), self.ui.annotationList)

                self.m_flowComponentDefinitionFile = value
        except:
            pass

    flowComponentDefinitionFile = QtCore.pyqtProperty(str, get_flowComponentDefinitionFile, set_flowComponentDefinitionFile)

import sys
from PyQt4 import QtGui
from QFlowSystemDesigner import QFlowSystemDesigner

def main(argv):
    app = QtGui.QApplication(argv)
    window = QFlowSystemDesigner()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main(sys.argv)
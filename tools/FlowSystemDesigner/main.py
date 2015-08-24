import sys
from PyQt4 import QtGui
from FlowSystemDesigner import FlowSystemDesigner

def main(argv):
    app = QtGui.QApplication(argv)
    window = FlowSystemDesigner()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main(sys.argv)
from PyQt4 import QtCore, QtGui

class QEllipseWidget(QtGui.QWidget):
    def __init__(self,
                 parent = None,
                 pen = QtGui.QPen(QtCore.Qt.darkRed),
                 brush = QtCore.Qt.red):
        super(QEllipseWidget, self).__init__(parent)
        self.pen = pen
        self.brush = brush

    def paintEvent(self, event):
        painter = QtGui.QPainter()
        painter.begin(self)
        painter.setPen(self.pen)
        painter.setBrush(self.brush)
        painter.drawEllipse(self.pos().x(),
                            self.pos().y(),
                            self.size().width(),
                            self.size().height())
        painter.end()
# #!/usr/bin/python3
# # -*- coding: utf-8 -*-
import sys
import json
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit
from PyQt5.QtGui import QIcon

class App(QWidget):

    def __init__(self):
        super().__init__()
        self.title = 'PyQt5 input dialogs - pythonspot.com'
        self.left = 10
        self.top = 10
        self.width = 640
        self.height = 480
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        #my numbers
        self.number_int=0
        self.text=""
        self.number_double=0
        self.favourite_color=""

        self.getInteger()
        self.getText()
        self.getDouble()
        self.getChoice()
        self.json_output_file()

        self.show()

    def getInteger(self):
        i, okPressed = QInputDialog.getInt(self, "Get integer","Percentage:", 28, 0, 100, 1)
        if okPressed:
            self.number_int=i

    def getDouble(self):
        d, okPressed = QInputDialog.getDouble(self, "Get double","Value:", 10.50, 0, 100, 10)
        if okPressed:
            self.number_double=d

    def getChoice(self):
        items = ("Red","Blue","Green")
        item, okPressed = QInputDialog.getItem(self, "Get item","Color:", items, 0, False)
        if okPressed and item:
            self.favourite_color=item

    def getText(self):
        text, okPressed = QInputDialog.getText(self, "Get text","Your name:", QLineEdit.Normal, "")
        if okPressed and text != '':
            self.text=text

    def json_output_file(self):
        data = {
            'name' : self.text,
            'int' : self.number_int,
            'double' : self.number_double,
            'favourite_color' : self.favourite_color
        }
        json_str = json.dumps(data)
        data = json.loads(json_str)
        # Writing JSON data
        with open('data.txt', 'w') as f:
            json.dump(data, f)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())


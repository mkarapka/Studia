import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QVBoxLayout, QStackedWidget

class Scene1(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.button = QPushButton("Przejdź do sceny 2", self)
        layout.addWidget(self.button)
        self.setLayout(layout)

class Scene2(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.button = QPushButton("Przejdź do sceny 1", self)
        layout.addWidget(self.button)
        self.setLayout(layout)

class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Zmiana scen")
        self.setGeometry(100, 100, 400, 200)

        self.stacked_widget = QStackedWidget(self)
        self.setCentralWidget(self.stacked_widget)

        # Dodaj dwie sceny do QStackedWidget
        self.scene1 = Scene1()
        self.scene2 = Scene2()
        self.stacked_widget.addWidget(self.scene1)
        self.stacked_widget.addWidget(self.scene2)

        self.scene1.button.clicked.connect(self.switch_to_scene2)
        self.scene2.button.clicked.connect(self.switch_to_scene1)

    def switch_to_scene1(self):
        self.stacked_widget.setCurrentWidget(self.scene1)

    def switch_to_scene2(self):
        self.stacked_widget.setCurrentWidget(self.scene2)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec())

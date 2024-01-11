from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QFrame,
    QGridLayout,
    QLabel,
    QLineEdit,
    QPushButton,
    QVBoxLayout,
    QWidget,
)


class ArrowButtonsWidget(QWidget):
    def __init__(self, change_callback=None):
        super().__init__()
        self.change_callback = change_callback

        self.k_index = 0
        self.tmp_x = []
        self.tmp_y = []
        self.tmp_u_num = 1000
        self.initUI()

    def initUI(self):
        main_layout = QVBoxLayout()
        main_frame = QFrame()
        main_frame.setFixedSize(140, 300)

        self.grid = QGridLayout(main_frame)

        # Setting buttons
        self.set_U_Buttons()
        self.setMoveButtons()
        self.save_points = QPushButton("Zapisz punkty")
        # Setting labels
        self.setLabels()

        # Adding all widgets to grid
        self.addWidgets()

        main_layout.addWidget(main_frame)
        self.setLayout(main_layout)

    def movePoint(self, direction):
        if self.tmp_x != [] and self.tmp_y != []:
            if direction == "UP":
                self.tmp_y[self.k_index] -= 1
            elif direction == "DOWN":
                self.tmp_y[self.k_index] += 1
            elif direction == "LEFT":
                self.tmp_x[self.k_index] -= 1
            elif direction == "RIGHT":
                self.tmp_x[self.k_index] += 1
            else:
                print("Wrong direction")

            # Setting to functions x y
            if self.change_callback:
                self.change_callback(self.tmp_x, self.tmp_y, self.tmp_u_num)

    def setPoint(self):
        try:
            number = int(self.line.text())
            if number >= 0 and number < len(self.tmp_x):
                self.k_index = number
            else:
                print("Wrong index")
        except:
            print("Inpust must be integer")

    def changeU(self, inp):
        if inp > 1:
            self.tmp_u_num = inp
        else:
            if abs(inp) == 1:
                self.tmp_u_num += inp

        # Setting to function u
        if self.change_callback:
            self.change_callback(self.tmp_x, self.tmp_y, self.tmp_u_num)

    def savePoints(self):
        pass

    def setMoveButtons(self):
        self.line = QLineEdit("0")

        # UP, DOWN, LEFT, RIGHT
        self.btnUp = QPushButton("↥")
        self.btnDown = QPushButton("↧")
        self.btnLeft = QPushButton("↤")
        self.btnRight = QPushButton("↦")
        self.ok = QPushButton("OK")

        # Actions for buttons
        self.ok.clicked.connect(self.setPoint)
        self.btnUp.clicked.connect(lambda: self.movePoint("UP"))
        self.btnDown.clicked.connect(lambda: self.movePoint("DOWN"))
        self.btnLeft.clicked.connect(lambda: self.movePoint("LEFT"))
        self.btnRight.clicked.connect(lambda: self.movePoint("RIGHT"))

    def set_U_Buttons(self):
        self.u_line = QLineEdit("0")
        self.add = QPushButton("+1")
        self.sub = QPushButton("-1")
        self.okay = QPushButton("OK")

        # Actions for buttons
        self.okay.clicked.connect(lambda: self.changeU(int(self.u_line.text())))
        self.add.clicked.connect(lambda: self.changeU(1))
        self.sub.clicked.connect(lambda: self.changeU(-1))

    # Fuctions for buttons
    def addWidgets(self):
        # u buttons and line
        self.grid.addWidget(self.label_2, 0, 0, 1, 3)
        self.grid.addWidget(self.u_line, 1, 0, 1, 3)
        self.grid.addWidget(self.add, 2, 2)
        self.grid.addWidget(self.okay, 2, 1)
        self.grid.addWidget(self.sub, 2, 0)

        # move buttons and line
        self.grid.addWidget(self.label, 3, 0, 1, 3)
        self.grid.addWidget(self.line, 4, 0, 1, 3)

        self.grid.addWidget(self.btnUp, 5, 1)
        self.grid.addWidget(self.btnDown, 7, 1)
        self.grid.addWidget(self.btnLeft, 6, 0)
        self.grid.addWidget(self.btnRight, 6, 2)
        self.grid.addWidget(self.ok, 6, 1)

        # save points button
        self.grid.addWidget(self.save_points, 8, 0, 1, 3)

    def setLabels(self):
        self.label_2 = QLabel("Rozmiar u")
        self.label_2.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.label = QLabel("Przesuń punkt")
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)

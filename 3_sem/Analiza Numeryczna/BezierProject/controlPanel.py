from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QFrame,
    QGridLayout,
    QLabel,
    QLineEdit,
    QPushButton,
    QVBoxLayout,
    QWidget,
    QMenu,
)
from PyQt6.QtGui import QAction


class ArrowButtonsWidget(QWidget):
    def __init__(self, change_callback=None):
        super().__init__()
        self.change_callback = change_callback

        self.k_index = 0
        self.tmp_x = []
        self.tmp_y = []
        self.tmp_u_num = 100
        
        self.all_splines = []
        self.spline_index = 0
        self.chosen_spline = 0
        self.initUI()

    def initUI(self):
        main_layout = QVBoxLayout()
        main_frame = QFrame()
        # main_frame.setFixedSize(140, 300)

        self.grid = QGridLayout(main_frame)

        # Setting buttons
        self.setButtons()

        # # Setting labels
        # self.setLabels()

        # Adding all widgets to grid
        self.addWidgets()

        main_layout.addWidget(main_frame)
        self.setLayout(main_layout)

    def removeSpline(self, index):
        spline = self.spline_menu.actions()[index]
        self.spline_menu.removeAction(spline)
        self.change_callback([index], 4)
        
        
    def choseSpline(self, spline_name):
        self.chosen_spline = self.all_splines.index(spline_name)
        print(self.chosen_spline)
        self.change_callback([],3)
            
    def addSpline(self):
        
            
        spline_name = f"Krzywa {self.spline_index}"
        spline_action = QAction(spline_name, self)  # Tworzenie QAction dla krzywej
        spline_action.triggered.connect(lambda: self.choseSpline(spline_name))  # Połączenie sygnału triggered
        
        self.spline_menu.addAction(spline_action)  # Dodanie QAction do QMenu
        self.all_splines.append(spline_name)
        self.spline_index += 1
        
            
    def movePoint(self, direction):
        if self.tmp_x != [] and self.tmp_y != []:
            if direction == "UP":
                self.tmp_y[self.k_index] += 1
            elif direction == "DOWN":
                self.tmp_y[self.k_index] -= 1
            elif direction == "LEFT":
                self.tmp_x[self.k_index] -= 1
            elif direction == "RIGHT":
                self.tmp_x[self.k_index] += 1
            else:
                print("Wrong direction")

            # Setting to functions x y
            if self.change_callback:
                self.change_callback([self.tmp_x, self.tmp_y, self.tmp_u_num], 0)

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
            self.change_callback([self.tmp_x, self.tmp_y, self.tmp_u_num], 0)


    def setButtons(self):
        def setMoveButtons():
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

        def set_U_Buttons():
            self.u_line = QLineEdit(f"{self.tmp_u_num}")
            self.add = QPushButton("+1")
            self.sub = QPushButton("-1")
            self.okay = QPushButton("OK")

            # Actions for buttons
            self.okay.clicked.connect(lambda: self.changeU(int(self.u_line.text())))
            self.add.clicked.connect(lambda: self.changeU(1))
            self.sub.clicked.connect(lambda: self.changeU(-1))

        def setOtherButtons():
            # save button
            self.save_points = QPushButton("Zapisz punkty")
            self.save_points.clicked.connect(lambda: self.change_callback([], 1) )

            # choose file button
            self.choose_file = QPushButton("Wybierz plik")
            self.choose_file.clicked.connect(lambda: self.change_callback([], 2))
            
            # Spline buttons
            #new spline
            self.new_spline = QPushButton("Nowa krzywa")
            self.new_spline.clicked.connect(self.addSpline)
            
            #chose spline
            self.choose_spline = QPushButton("Wybierz krzywą")
            self.spline_menu = QMenu(self)
            self.addSpline()
            self.choose_spline.setMenu(self.spline_menu)
            
            #remove spline
            self.rm_spline = QPushButton("Usuń krzywą")
            self.rm_spline.clicked.connect(lambda: self.change_callback([self.chosen_spline], 4))
        setMoveButtons()
        set_U_Buttons()
        setOtherButtons()

    # Fuctions for buttons

    def addWidgets(self):
        def setLabels():
            self.label_2 = QLabel("Rozmiar u")
            self.label_2.setAlignment(Qt.AlignmentFlag.AlignCenter)

            self.label = QLabel("Przesuń punkt")
            self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        ind = 1
        # Setting labels
        setLabels()
        # choose file button
        self.grid.addWidget(self.choose_file, ind - 1, 0, 1, 3)
        # u buttons and line
        self.grid.addWidget(self.label_2, ind, 0, 1, 3)
        self.grid.addWidget(self.u_line, ind + 1, 0, 1, 3)
        self.grid.addWidget(self.add, ind + 2, 2)
        self.grid.addWidget(self.okay, ind + 2, 1)
        self.grid.addWidget(self.sub, ind + 2, 0)

        # move buttons and line
        self.grid.addWidget(self.label, ind + 3, 0, 1, 3)
        self.grid.addWidget(self.line, ind + 4, 0, 1, 3)

        self.grid.addWidget(self.btnUp, ind + 5, 1)
        self.grid.addWidget(self.btnDown, ind + 7, 1)
        self.grid.addWidget(self.btnLeft, ind + 6, 0)
        self.grid.addWidget(self.btnRight, ind + 6, 2)
        self.grid.addWidget(self.ok, ind + 6, 1)

        # save points button
        self.grid.addWidget(self.new_spline, ind + 8, 0, 1, 3)
        self.grid.addWidget(self.choose_spline, ind + 9, 0, 1, 3)
        self.grid.addWidget(self.rm_spline, ind + 10, 0, 1, 3)
        self.grid.addWidget(self.save_points, ind + 11, 0, 1, 3)

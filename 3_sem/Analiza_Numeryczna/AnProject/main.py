import sys

import matplotlib.image as mpimg
import numpy as np
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qtagg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

import splines.nifs as spline
from controlPanel import ArrowButtonsWidget


class MatplotlibWidget(QWidget):
    def __init__(self, img_arg=None):
        super().__init__()
        self.img_arg = img_arg
        self.dots = []

        # Points
        self.right_bar = ArrowButtonsWidget(self.changePlot)
        self.x_points, self.y_points = [], []
        self.u_num = self.right_bar.tmp_u_num

        self.setFixedHeight(600)
        self.initUI()

    def changePlot(self, x, y, u_num):
        self.x_points = x
        self.y_points = y
        self.u_num = u_num
        self.plot(self.u_num)

    def plot(self, u):
        if len(self.x_points) > 1:
            if self.line:
                for l in self.line:
                    l.remove()
                self.line.clear()

            points = self.return_spline_points(self.x_points, self.y_points, u)
            # Drawing new line
            new_line = self.ax.plot(*points, "b-")

            # Adding new line to list
            self.line.extend(new_line)

        if self.dots:
            for l in self.dots:
                l.remove()
            self.dots.clear()
        dot = self.ax.plot(self.x_points, self.y_points, "ro")
        self.dots.extend(dot)

        self.canvas.draw()

    def initUI(self, img_arg=None):

        # Matplotlib varibles
        self.ctrl_pressed = False
        self.line = []

        # Layouts
        self.main = QHBoxLayout(self)
        self.layout = QVBoxLayout()
        self.main.addLayout(self.layout)

        # Creating canvas
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)

        self.ax = self.figure.add_subplot()
        if self.img_arg:
            img = mpimg.imread(self.img_arg)
            self.ax.imshow(img)

        # Toolbar
        self.toolbar = NavigationToolbar(self.canvas, self)

        # Setting Canvas
        self.canvas.mpl_connect("button_press_event", self.onclick)
        self.addWidgets()

    def addWidgets(self):
        self.layout.addWidget(self.toolbar)

        # Adding canvas to layout
        self.layout.addWidget(self.canvas)

        self.button = QPushButton("Wypisz punkty")
        self.save_button = QPushButton("Zapisz punkty")
        self.button.clicked.connect(self.printVectors)

        self.main.addWidget(self.right_bar)
        self.layout.addWidget(self.button)
        self.layout.addWidget(self.save_button)

    def printVectors(self):
        t = np.linspace(0, 1, len(self.x_points))
        u = np.linspace(0, 1, self.u_num + 1)

        arr_t = [k for k in t]
        arr_u = [k for k in u]

        print(f"x: {self.x_points}")
        print(f"y: {self.y_points}")

        print(f"t: {arr_t}")
        print(f"u: {arr_u}")

    # Matplotlib events
    def onclick(self, event):
        # Adding points after clicking on canvas
        if self.ctrl_pressed:
            self.x_points.append(event.xdata)
            self.y_points.append(event.ydata)

            self.right_bar.tmp_x = self.x_points
            self.right_bar.tmp_y = self.y_points
            self.canvas.draw()
            self.plot(self.u_num)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key.Key_Control:
            self.ctrl_pressed = True

    def keyReleaseEvent(self, event):
        if event.key() == Qt.Key.Key_Control:
            self.ctrl_pressed = False

    def return_spline_points(self, x_points, y_points, u_len):
        t = np.linspace(0, 1, len(x_points))
        u = np.linspace(0, 1, u_len + 1)

        sx = spline.NIFS3(t, x_points).result()
        sy = spline.NIFS3(t, y_points).result()

        return [sx(uk) for uk in u], [sy(uk) for uk in u]


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # Setting central widget on MatplotlibWidget
        self.setCentralWidget(MatplotlibWidget("napis.png"))
        self.setWindowTitle("Matplotlib z PyQt6")


# Executing app
app = QApplication(sys.argv)
main = MainWindow()
main.show()
sys.exit(app.exec())

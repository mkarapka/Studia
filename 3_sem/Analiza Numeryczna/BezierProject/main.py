import sys
import os
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
    QFileDialog,
    
)

from controlPanel import ArrowButtonsWidget
from de_casteljau import de_casteljau


class MatplotlibWidget(QWidget):
    def __init__(self, xlimit=800, ylimit=800, img_arg=None):
        super().__init__()
        self.current_spline = 0
        self.dots = []
        self.lst_dots = {}
        self.line = []
        self.lst_line = []
        self.xlimit = xlimit
        self.ylimit = ylimit

        self.lines = []
        self.lst_points = {}
        
        # Points
        self.right_bar = ArrowButtonsWidget(self.manageCallbacks)
        self.x_points, self.y_points = [], []
        self.u_num = self.right_bar.tmp_u_num

        self.setFixedHeight(600)
        self.initUI()

    def absPath(self, file_name):
        dir_path = os.path.dirname(os.path.realpath(__file__))
        ab_path = os.path.join(dir_path, file_name)
        return ab_path

    def manageCallbacks(self, lst_args, callback):
        self.current_spline = self.right_bar.chosen_spline
        
        def saveCurve(filename="splines/curve_data7.txt"):
            # Czytanie i wypisywanie zawartości pliku
            index = 0
            self.lst_points[len(self.lst_points)] = [self.x_points, self.y_points, self.u_num]
            t = np.linspace(0, 1, self.u_num)

            arr_t = [k for k in t]
            for key in self.lst_points:
                try:
                    with open(filename, "r") as file:
                        for line in file:
                            if line.startswith("#"):
                                index = int(line[1:])
                        index += 1
                except FileNotFoundError:
                    print("Plik nie istnieje, zostanie utworzony.")

                # Dopisywanie do pliku
                with open(filename, "a") as file:
                    file.write(f"#{index}\n")
                    file.write(f"x: {self.x_points}\n")
                    file.write(f"y: {self.y_points}\n")
                    file.write(f"t: {arr_t}\n")
                    print("Zapisano 'numerki' do pliku")

        def openFileDialog():    
            fileName, _ = QFileDialog.getOpenFileName(self, "Wybierz plik obrazu", "",
                                                "Pliki obrazów (*.jpg *.jpeg *.png *.bmp *.gif)")
            if fileName:
                print(f"Wybrano plik: {fileName}")
                
                path  = self.absPath(fileName)
                img = mpimg.imread(path)
                img_width, img_height = img.shape[1], img.shape[0]
                c_x = (self.xlimit - img_width) / 2
                c_y = (self.ylimit - img_height) / 2
                self.ax.imshow(img, extent=[c_x, c_x + img_width, c_y, c_y + img_height])
                self.canvas.draw()
                
     

        def clearLastSpline(self):
            if self.lst_points:
                last_key = list(self.lst_points.keys())[-1]
                self.lst_points.pop(last_key)

                self.ax.clear()

                for spline_id, (x, y, u_num) in self.lst_points.items():
                    if len(x) > 1:
                        points = self.return_bezier_spline(x, y, u_num)
                        self.ax.plot(*points, "b-")

                self.canvas.draw()

        
        def addSpline():
            
            self.lst_points[len(self.lst_points)] = [self.x_points, self.y_points, self.u_num]
            self.lst_line.append(self.line)
            
            tmp_x = self.x_points[-1]
            tmp_y = self.y_points[-1]
            
            self.x_points = [tmp_x]
            self.y_points = [tmp_y]
            self.plot(self.u_num)
            self.canvas.draw()

        if callback == 0:
            self.changePlot(lst_args[0], lst_args[1], lst_args[2])
        
        elif callback == 1:
            saveCurve() 

        elif callback == 2:
            openFileDialog()
            
        elif callback == 3:
            addSpline()
            
        elif callback == 4:
            clearLastSpline(lst_args[0])
            

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

            for key in self.lst_points:
                
                x_points = self.lst_points[key][0]
                y_points = self.lst_points[key][1]
                u_num = self.lst_points[key][2]
                points = self.return_bezier_spline(x_points, y_points, u_num)
                # Drawing new line
                new_line = self.ax.plot(*points, "b-")

                # Adding new line to list
                self.line.extend(new_line)
                
            points = self.return_bezier_spline(self.x_points, self.y_points, self.u_num)
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
        

        # Layouts
        self.main = QHBoxLayout(self)
        self.layout = QVBoxLayout()
        self.main.addLayout(self.layout)

        # Creating canvas
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)

        self.ax = self.figure.add_subplot()
        self.ax.set_xlim(0, self.xlimit)
        self.ax.set_ylim(0, self.ylimit)
        
            
        # Toolbar
        self.toolbar = NavigationToolbar(self.canvas)
        self.layout.addWidget(self.toolbar)

        # Setting Canvas
        self.canvas.mpl_connect("button_press_event", self.onclick)
        self.addWidgets()

    def addWidgets(self):

        # Adding canvas to layout
        self.layout.addWidget(self.canvas)

        self.button = QPushButton("Wypisz punkty")
        self.button.clicked.connect(self.printVectors)

        self.main.addWidget(self.right_bar)

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


    def return_bezier_spline(self, x, y, u_len):
        t_values = np.linspace(0, 1, num=u_len)
        w = [1 for _ in range(len(x))]
        bezier_points = [de_casteljau(x, y, w, t) for t in t_values]

        x_values = [point[0] for point in bezier_points]
        y_values = [point[1] for point in bezier_points]

        return x_values, y_values


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # Setting central widget on MatplotlibWidget
        self.setCentralWidget(MatplotlibWidget(800, 800))
        self.setWindowTitle("Matplotlib z PyQt6")


# Executing app
app = QApplication(sys.argv)
main = MainWindow()
main.show()
sys.exit(app.exec())

import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QFileDialog, QHBoxLayout, QVBoxLayout
from PyQt6.QtGui import QAction, QIcon, QPainter, QColor
from PyQt6.QtCore import Qt, QPoint

class MojaAplikacja(QMainWindow):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.globalVariables()
        
        
        
        self.show()
    
    def globalVariables(self):
        # Ellipse varaibles
        self.kola = []
        self.przesuwanie_kola = None  
        
        # Layout
        layout = QHBoxLayout(self)
        left_bar = QVBoxLayout()
        right_bar = QVBoxLayout()
        
        
    def initUI(self):
        self.setGeometry(100, 100, 800, 600)
        self.setWindowTitle('Edytor krzywych')
        
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('Plik')

        openFile = QAction('Otwórz', self)
        openFile.triggered.connect(self.showDialog)
        fileMenu.addAction(openFile)

        
        
    # Opening a file #
    def showDialog(self):
        fileName, _ = QFileDialog.getOpenFileName(self, 'Otwórz plik', '', 'Text Files (*.txt);;All Files (*)')

        if fileName:
            with open(fileName, 'r') as file:
                text = file.read()
                self.textEdit.setPlainText(text)
      
    # Drawnig ellipse #          
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setPen(QColor(255, 0, 0))  # Ustawienie koloru na czerwony (RGB: 255, 0, 0)

        for pozycja_kola, promien_kola in self.kola:
            painter.drawEllipse(pozycja_kola, promien_kola, promien_kola)


    # Mouse events #
    def mousePressEvent(self, event):
        pozycja_myszy = event.pos()

        # Sprawdź, czy kliknięto wewnątrz istniejącego koła
        for i, (pozycja_kola, promien_kola) in enumerate(self.kola):
            if (QPoint(pozycja_kola) - QPoint(pozycja_myszy)).manhattanLength() < promien_kola:
                self.przesuwanie_kola = i
                break
        else:
            # Jeżeli nie kliknięto wewnątrz istniejącego koła, stwórz nowe koło
            self.kola.append((pozycja_myszy, 20))  # Domyślny promień to 20

        self.update()

    def mouseMoveEvent(self, event):
        if self.przesuwanie_kola is not None:
            pozycja_myszy = event.pos()
            self.kola[self.przesuwanie_kola] = (pozycja_myszy, self.kola[self.przesuwanie_kola][1])
            self.update()

    def mouseReleaseEvent(self, event):
        self.przesuwanie_kola = None
        
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MojaAplikacja()
    sys.exit(app.exec())

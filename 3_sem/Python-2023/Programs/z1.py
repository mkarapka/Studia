import sys
from PyQt6.QtWidgets import QApplication, QWidget
from PyQt6.QtGui import QPainter, QColor
from PyQt6.QtCore import Qt, QPoint

class MojaAplikacja(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('Tworzenie kół i przesuwanie')
        self.setGeometry(100, 100, 400, 300)

          # Lista przechowująca dane o kołach
        self.przesuwanie_kola = None  # Indeks koła, które jest przesuwane

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setPen(QColor(255, 0, 0))  # Ustawienie koloru na czerwony (RGB: 255, 0, 0)

        for pozycja_kola, promien_kola in self.kola:
            painter.drawEllipse(pozycja_kola, promien_kola, promien_kola)

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
 # Domyślny promień to 20

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
    window.show()
    sys.exit(app.exec())
# from domain.entities.entities import *
# from domain.repositories import *
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from private import PASSWORD, server_name, user_name, database


connection_string = f"mssql+pyodbc://{user_name}:{PASSWORD}@{server_name}/{database}?driver=ODBC+Driver+18+for+SQL+Server"
engine = create_engine(connection_string, echo=True)

connection = engine.connect()
# Deklaracja bazy
Base = declarative_base()


# Definicja tabeli Jednostka
class Jednostka(Base):
    __tablename__ = "Jednostka"
    ID = Column(Integer, primary_key=True, autoincrement=True)
    Nazwa = Column(String(20))

    def __repr__(self):
        return f"<Jednostka(Nazwa='{self.Nazwa}')>"


# Definicja tabeli Osoba
class Osoba(Base):
    __tablename__ = "Osoba"
    ID = Column(Integer, primary_key=True, autoincrement=True)
    ID_Jednostka = Column(Integer, ForeignKey("Jednostka.ID"))
    Imie = Column(String(30))
    Nazwisko = Column(String(50))
    Pensja = Column(Integer)
    jednostka = relationship("Jednostka")

    def __repr__(self):
        return f"<Osoba(Imie='{self.Imie}', Nazwisko='{self.Nazwisko}', Pensja={self.Pensja})>"


# Tworzenie tabel
Base.metadata.create_all(engine)

# Tworzenie sesji
Session = sessionmaker(bind=engine)
session = Session()

# Dodawanie danych do tabeli Jednostka
jednostki = [
    Jednostka(Nazwa="Wrocław"),
    Jednostka(Nazwa="Poznań"),
    Jednostka(Nazwa="Kraków"),
    Jednostka(Nazwa="Warszawa"),
]
session.add_all(jednostki)
session.commit()

# Dodawanie danych do tabeli Osoba
osoby = [
    Osoba(ID_Jednostka=1, Imie="Jan", Nazwisko="Kowalski", Pensja=1000),
    Osoba(ID_Jednostka=3, Imie="Ewa", Nazwisko="Solska", Pensja=1200),
    Osoba(ID_Jednostka=2, Imie="Bożydar", Nazwisko="Nowak", Pensja=1500),
    Osoba(ID_Jednostka=4, Imie="Adam", Nazwisko="Adamski", Pensja=1700),
    Osoba(ID_Jednostka=4, Imie="Zygmunt", Nazwisko="Riposta", Pensja=1240),
    Osoba(ID_Jednostka=2, Imie="Alicja", Nazwisko="Gleba", Pensja=1600),
    Osoba(ID_Jednostka=1, Imie="Tania", Nazwisko="Borówka", Pensja=1560),
    Osoba(ID_Jednostka=1, Imie="Natasza", Nazwisko="Lizacka", Pensja=2500),
    Osoba(ID_Jednostka=3, Imie="Stan", Nazwisko="Taczkowski", Pensja=1900),
]
session.add_all(osoby)
session.commit()

# Dodawanie nowej jednostki
j1 = Jednostka(Nazwa="Londyn")
session.add(j1)
session.commit()

# Wykonywanie zapytania
result = session.query(Jednostka).order_by(Jednostka.Nazwa).all()
print(f"Znaleziono {len(result)} jednostek")
for j in result:
    print(j)

# Zamknięcie sesji
session.close()

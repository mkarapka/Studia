from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.orm import sessionmaker, declarative_base, relationship
from private import PASSWORD, server_name, user_name, database

# Ustawienie connection string
connection_string = f"mssql+pyodbc://{user_name}:{PASSWORD}@{server_name}/{database}?driver=ODBC+Driver+18+for+SQL+Server"
engine = create_engine(connection_string, echo=True)

# Deklaracja bazy
Base = declarative_base()


# Definicja tabeli Osoba
class Osoba(Base):
    __tablename__ = "Osoba"
    ID = Column(Integer, primary_key=True, autoincrement=True)
    Imie = Column(String(30), nullable=False)
    Nazwisko = Column(String(50), nullable=False)
    UlicaDom = Column(String(100))
    MiastoDom = Column(String(100))
    UlicaPraca = Column(String(100))
    MiastoPraca = Column(String(100))


# Tworzenie tabeli
Base.metadata.create_all(engine)

# Tworzenie fabryki sesji
Session = sessionmaker(bind=engine)


def main():
    session1 = Session()
    session2 = Session()

    domowy_adres = {"UlicaDom": "Grabiszyńska", "MiastoDom": "Wrocław"}
    sluzbowy_adres = {"UlicaPraca": "Szczytnicka", "MiastoPraca": "Wrocław"}
    osoba = Osoba(Imie="Jan", Nazwisko="Kowalski", **domowy_adres, **sluzbowy_adres)

    try:
        tx1 = session1.begin()
        session1.add(osoba)
        tx1.commit()
    except Exception as e:
        print(e)
    finally:
        session1.close()

    try:
        tx2 = session2.begin()
        query = session2.query(Osoba).order_by(Osoba.Nazwisko.asc())
        results = query.all()
        print(f"Znaleziono: {len(results)}")
        for os in results:
            print(
                f"ID: {os.ID}\t Imie: {os.Imie}\t Nazwisko: {os.Nazwisko}\t Ulica dom: {os.UlicaDom}\t Ulica praca: {os.UlicaPraca}"
            )
        tx2.commit()
    except Exception as e:
        print(e)
    finally:
        session2.close()


if __name__ == "__main__":
    main()

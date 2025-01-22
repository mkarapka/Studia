from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.orm import sessionmaker, declarative_base
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


# Tworzenie tabeli
Base.metadata.create_all(engine)

# Tworzenie fabryki sesji
Session = sessionmaker(bind=engine)


def main():
    session1 = Session()
    session2 = Session()
    session3 = Session()

    os = Osoba(Imie="Jan", Nazwisko="Kowalski")

    try:
        tx1 = session1.begin()
        session1.add(os)
        tx1.commit()
    except Exception as e:
        print(e)
    finally:
        session1.close()

    p1 = None
    p2 = None
    p3 = None
    try:
        p1 = session2.query(Osoba).get(1)
        p2 = session2.query(Osoba).get(1)

        if p1 is p2:
            print("P1, P2 SA ROWNE")
        else:
            print("P1, P2 NIE SA ROWNE")

        p1.Imie = "John"
        print("P2.Imie: " + p2.Imie)

        p3 = session3.query(Osoba).get(1)

        if p1 is p3:
            print("P1, P3 SA ROWNE")
        else:
            print("P1, P3 NIE SA ROWNE")
    except Exception as e:
        print(e)
    finally:
        session2.close()
        session3.close()


if __name__ == "__main__":
    main()

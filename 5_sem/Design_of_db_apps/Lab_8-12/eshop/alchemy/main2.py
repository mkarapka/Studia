from sqlalchemy import create_engine, Column, Integer, String, Enum
from sqlalchemy.orm import sessionmaker, declarative_base
from private import PASSWORD, server_name, user_name, database
import enum

# Ustawienie connection string
connection_string = f"mssql+pyodbc://{user_name}:{PASSWORD}@{server_name}/{database}?driver=ODBC+Driver+18+for+SQL+Server"
engine = create_engine(connection_string, echo=True)

# Deklaracja bazy
Base = declarative_base()


# Definicja enumeracji dla statusu zamówienia
class OrderStatus(enum.Enum):
    InTravel = "InTravel"
    Delivered = "Delivered"
    Cancelled = "Cancelled"


# Definicja tabeli Order
class Order(Base):
    __tablename__ = "Order"
    ID = Column(Integer, primary_key=True, autoincrement=True)
    Customer = Column(String(100))
    Address = Column(String(150))
    Status = Column(Enum(OrderStatus))


# Tworzenie tabeli
Base.metadata.create_all(engine)

# Tworzenie fabryki sesji
Session = sessionmaker(bind=engine)


def main():
    # Dodawanie zamówienia
    with Session() as session:
        o = Order(Customer="IBM", Address="USA", Status=OrderStatus.InTravel)
        session.add(o)
        session.commit()

    # Pobieranie i wyświetlanie zamówień
    with Session() as session:
        orders = session.query(Order).all()
        for o in orders:
            print(f"{o.Customer} {o.Address} {o.Status.value}")


if __name__ == "__main__":
    main()

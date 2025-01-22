import time
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from private import PASSWORD, server_name, user_name, database


# Ustawienie connection string
connection_string = f"mssql+pyodbc://{user_name}:{PASSWORD}@{server_name}/{database}?driver=ODBC+Driver+17+for+SQL+Server"
engine = create_engine(connection_string, echo=True)

# Tworzenie fabryki sesji
Session = sessionmaker(bind=engine)


def open_session():
    return Session()


def create_factory():
    return sessionmaker(bind=engine)


def main():
    N = 500
    input("Enter aby rozpocząć")
    print("Wiele fabryk")
    t1 = time.time()
    for i in range(N):
        print(".", end="")
        s = open_session()
        # s.close()
    t2 = time.time()
    print("\n\nEnter aby kontynuować")
    input()
    print("Jedna fabryka")
    t3 = time.time()
    factory = create_factory()
    for i in range(N):
        print(".", end="")
        s = factory()
        # s.close()
    t4 = time.time()
    print()
    print(f"{(t2 - t1) * 1000:.0f} ms")
    print(f"{(t4 - t3) * 1000:.0f} ms")
    input()


if __name__ == "__main__":
    main()

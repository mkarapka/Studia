from neo4j import GraphDatabase
from config import PASSWORD
from prettytable import PrettyTable

URI = "neo4j+s://846de4f7.databases.neo4j.io"
AUTH = ("neo4j", PASSWORD)


def print_persons(tx):
    result = tx.run("MATCH (p: Person) RETURN p.name AS name")
    table = PrettyTable(["Name"])
    for record in result:
        table.add_row([record["name"]])
    print(table)


with GraphDatabase.driver(URI, auth=AUTH) as driver:
    driver.verify_connectivity()
    with driver.session() as session:
        session.read_transaction(print_persons)

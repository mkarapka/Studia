import pymongo

client = pymongo.MongoClient("mongodb://localhost:27017/")

databases = client.list_database_names()
print("Databases:", databases)

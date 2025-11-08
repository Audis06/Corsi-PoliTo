import pymysql

def connect_to_db():
    return pymysql.connect(
        host="localhost",
        user="root",
        password="",
        database="BIBLIOTECA",
        charset="utf8mb4"
    )



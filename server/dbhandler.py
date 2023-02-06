import sqlite3


def getInfo(msg):
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    if (msg == "!CLIENTS"):
        c.execute("SELECT first,second,PID,Client_type,bill FROM Clients;")
    elif (msg == "!ROOMS"):
        c.execute("SELECT * FROM Rooms;")
    elif (msg == "!RESERVATIONS"):
        c.execute("SELECT first,second,PID,Client_type,bill FROM Clients;")
    info = c.fetchall()
    conn.close()
    delimeter = '#'
    joined = ''



    for part in info:

        joined += delimeter.join([str(value) for value in part])
        joined += '\n'
    joined = joined.strip()
    return joined


def getPIDpasswd(pid):
    try:
        int(pid)
    except:
        return None
    print(pid)
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    c.execute(f"SELECT passwd FROM Clients WHERE PID = {pid};")
    passwd = c.fetchall()
    conn.close()
    if len(passwd) == 0:
        return None
    return passwd[0][0]

def save(msg):
    splitted = msg.split("#")
    where = ""
    if len(splitted) == 5:
        where = "Clients"
    elif len(splitted) == 4:
        where = "Rooms"
    elif len(splitted) == 6:
        where = "Reservations"

    return saveInfo(splitted,where)


def saveInfo(msg,where):
    tup = tuple(msg)

    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()

    try:
        c.execute(f'''INSERT INTO {where} 
              VALUES(?,?,?,?,?,0);''',tup)
    except:
        conn.close()
        return False

    conn.commit()
    conn.close()
    return True




import sqlite3


def getInfo(msg):
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    if (msg == "!CLIENTS"):
        c.execute("SELECT first,second,PID,Client_type,bill FROM Clients;")
    elif (msg == "!ROOMS"):
        c.execute("SELECT * FROM Rooms;")
    elif (msg == "!RESERVATIONS"):
        c.execute("SELECT  * FROM Reservations;")
    print(msg)
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
    print("Logging in user " + pid)
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    c.execute(f"SELECT passwd FROM Clients WHERE PID = {pid};")
    passwd = c.fetchall()
    conn.close()
    if len(passwd) == 0:
        print("Logging unsuccessful")
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
    str = ""
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    if where == "Clients":
        str = "(?,?,?,?,?,0)"
    elif where == "Rooms":
        str = "(?,?,?,?)"
    elif where == "Reservations":
        str = "(?,?,?,?,?,?)"
    try:
        c.execute(f'''INSERT INTO {where} 
              VALUES{str};''',tup)
    except:
        conn.close()
        return False

    conn.commit()
    conn.close()
    return True

def updateClient(msg):
    splitted = msg.split("#")
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    try :
        c.execute(f'''UPDATE CLIENTS SET {splitted[2]} = {splitted[1]} 
                     WHERE PID = {splitted[0]};''')
    except:
        conn.close()
        return False

    conn.commit()
    conn.close()

    return True

def deleteRes(msg):
    splitted = msg.split("#")
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    try :

        c.execute(f'''DELETE FROM Reservations WHERE PID = '{splitted[0]}' AND NR = '{splitted[1]}'
                     AND date = '{splitted[2]}';''')
    except:
        conn.close()
        return False

    conn.commit()
    conn.close()

    return True

def updateRes(msg):
    splitted = msg.split("#")
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    try:
        c.execute(f'''UPDATE Reservations SET type_of_res = {splitted[3]} 
                         WHERE PID = '{splitted[0]}' AND NR = '{splitted[1]}'
                        AND date = '{splitted[2]}';''')
    except:
        conn.close()
        return False

    conn.commit()
    conn.close()

    return True

# print(updateClient("999#0#Client_type"))
# print(updateClient("999#0#bill"))

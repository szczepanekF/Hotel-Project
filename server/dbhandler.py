import sqlite3



def getClients():
    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    c.execute("SELECT first,second,PID,Client_type FROM Clients")
    clients = c.fetchall()
    conn.close()
    delimeter = ','
    joined=''
    for client in clients:
        joined += delimeter.join([str(value) for value in client])
        joined +='\n'
    joined = joined.strip()
    return joined


def getPIDpasswd(pid):
    try:
        int(pid)
    except:
        return None

    conn = sqlite3.connect('dbs/users.db')
    c = conn.cursor()
    c.execute(f"SELECT passwd FROM Clients WHERE PID = {pid}")
    passwd = c.fetchall()
    conn.close()
    if len(passwd) == 0:
        return None
    return passwd[0][0]


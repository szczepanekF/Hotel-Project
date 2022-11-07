import socket
import threading
import dbhandler as db


class CPPcon:
    def __init__(self):
        self.DISCONNECT_MESSAGE = "!DISCONNECT"
        self.GET_CLIENT_MESSAGE = "!CLIENTS"
        self.GET_PASSWORD = "!PASSWD"
        self.NO_CLIENT = "!NO_CLIENT"
        self.HEADER=64
        self.PORT = 5050
        self.SERVER ="192.168.0.53"
        self.ADDR = (self.SERVER,self.PORT)
        self.FORMAT = 'utf-8'
        self.server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.server.bind(self.ADDR)



    def get_message(self,conn):
        msg_length = conn.recv(self.HEADER).decode(self.FORMAT)
        if msg_length:
            msg_length = int(msg_length)
            conn.send("LEN_RECIEVED".encode(self.FORMAT))
            msg = conn.recv(msg_length).decode(self.FORMAT)
        else:
            return False
        return msg

    def handle_client(self,conn,addr):
        ispasswd=0
        print(f"[NEW CONNECTION] {addr} connected.")
        connected = True

        while connected:
            msg = self.get_message(conn)
            
            if msg == self.DISCONNECT_MESSAGE:
                connected = False
            elif msg == self.GET_CLIENT_MESSAGE:
                conn.send(db.getClients().encode(self.FORMAT))
                continue
            #PASSWORD HANDLING
            elif msg == self.GET_PASSWORD:
                ispasswd=1
            elif ispasswd:
                ispasswd=0

                passwd = db.getPIDpasswd(msg.strip())

                if passwd == None:
                    conn.send(self.NO_CLIENT.encode(self.FORMAT))
                else:
                    conn.send(passwd.encode(self.FORMAT))
                continue
            print(f"[{addr}] {msg}")
            conn.send("Msg recieved".encode(self.FORMAT))


        print(f'[CLOSING CONN] [{addr}]')
        conn.close()



    def start(self):
        self.server.listen()
        print(f"[LISTENING] Server is listening on {self.SERVER}")
        while True:
            conn, addr = self.server.accept()
            thread = threading.Thread(target=self.handle_client,args=(conn,addr))
            thread.start()
            print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")



print("[STARTING] server is starting ..")
a = CPPcon()

a.start()


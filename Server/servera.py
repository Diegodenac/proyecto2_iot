import socket
import threading

ranges = "25.50.75.100"
SERVER_IP = "192.168.220.60"
PORT = 5000

clients = {}

def handle_sensor_client(client_socket):
    global clients
    client_socket.send((ranges + "\n").encode())
    while True:
        try:
            state = client_socket.recv(1024).decode()
            if not state:
                break
            print(f"[SENSOR-DISTANCE] State received: {state}")
            if 'actuator-leds' in clients:
                try:
                    clients['actuator-leds'].send(state.encode())
                    print(f"[SERVIDOR] State send to actuator-leds: {state}")
                except Exception as e:
                    print(f"[ERROR] Can't send to actuator-leds: {e}")
        except Exception as e:
            print(f"[ERROR] Error conecting sensor-distance: {e}")
            break
    client_socket.close()
    del clients['sensor-distance']
    print("[SERVIDOR] Server sensor-distance conection closed")


def handle_actuator_client(client_socket):
    global clients
    try:
        while True:
            message = client_socket.recv(1024).decode()
            if not message:
                break
            print("[ACTUATOR-LEDS] Message Received")
    except Exception as e:
        print(f"[ERROR] Error conecting actuator-leds: {e}")
    client_socket.close()
    del clients['actuator-leds']
    print("[SERVIDOR] Server actuator-leds conection closed")


def client_handler(client_socket, client_address):
    global clients
    try:
        client_socket.send("IDENTIFICATE\n".encode())  
        client_type = client_socket.recv(1024).decode().strip() 
        print(f"[SERVIDOR] Client connect: {client_address} as {client_type}")
        if client_type == "sensor-distance":
            clients['sensor-distance'] = client_socket
            handle_sensor_client(client_socket)
        elif client_type == "actuator-leds":
            clients['actuator-leds'] = client_socket
            handle_actuator_client(client_socket)
        else:
            print(f"[SERVIDOR] Tipe of cliente unrecognized: {client_type}")
            client_socket.close()
    except Exception as e:
        print(f"[ERROR] Error handle client: {e}")
        client_socket.close()


def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((SERVER_IP, PORT))
    server.listen(2)
    print(f"[SERVIDOR] Server start in {SERVER_IP}:{PORT}")
    while True:
        client_socket, client_address = server.accept()
        print(f"[CONEXIÓN] New conection {client_address}")
        client_thread = threading.Thread(target=client_handler, args=(client_socket, client_address))
        client_thread.start()


if __name__ == "__main__":
    start_server()
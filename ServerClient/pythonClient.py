import socket
import time

def receive_keyboard_data():
    host = '127.0.0.1'
    port = 12345

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    while True:
        keyboard_data = client_socket.recv(1024).decode()
        print('Received keyboard data:', keyboard_data)
        time.sleep(1)  # Intervalo de 1 segundo entre as solicitações

    client_socket.close()

if __name__ == '__main__':
    receive_keyboard_data()


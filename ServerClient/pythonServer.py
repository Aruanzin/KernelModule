import socket
import time

def read_keyboard_file():
    with open('/proc/meu_arquivo', 'r') as file:
        return file.read()

def start_server():
    host = '127.0.0.1'
    port = 12345

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print('Server listening on {}:{}'.format(host, port))

    while True:
        client_socket, addr = server_socket.accept()
        print('Connected to client:', addr)

        while True:
            keyboard_data = read_keyboard_file()

            client_socket.sendall(keyboard_data.encode())

            time.sleep(1)  # Intervalo de 1 segundo entre as atualizações

    client_socket.close()

if __name__ == '__main__':
    start_server()


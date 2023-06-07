# *********************
# Apexia Platforms
# Valora KVS
# Alternative Clients Examples
# main.py
# *********************

import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

query = "SEThello;world"

socket.send_string(query)

message = socket.recv_string()
print("SET Received response: ", message)

query = "GEThello"

socket.send_string(query)

message = socket.recv_string()
print("GET Received response: ", message)

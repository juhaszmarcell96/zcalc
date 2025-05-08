import websocket

ws = websocket.create_connection("ws://localhost:1111")
print("connected to WebSocket server at ws://localhost:1111")

try:
    while True:
        message = input("enter message (type 'close' to exit): ")
        if message == "close":
            print("closing connection...")
            ws.close()
            break
        ws.send(message)
        response = ws.recv()
        print("received:", response)
except KeyboardInterrupt:
    print("\ninterrupted -> closing connection...")
    ws.close()

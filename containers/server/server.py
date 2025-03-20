import asyncio
import websockets
import json

message_counter = 0

async def handler(websocket):
    global message_counter
    async for message in websocket:
        data = json.loads(message)
        print(f"Received: {data}")

        response = {
            "index": message_counter,
            "message": "Echo: " + data["message"]
        }
        message_counter += 1
        await websocket.send(json.dumps(response))

async def main():
    server = await websockets.serve(handler, "0.0.0.0", 4444)
    print("WebSocket server started on port 4444")
    await server.wait_closed()

if __name__ == "__main__":
    asyncio.run(main())

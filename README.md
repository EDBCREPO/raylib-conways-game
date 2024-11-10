# Conways Game Of Life
Conways Game Of Life using C++, Nodepp and Raylib

## Dependencies
```bash
📌Nodepp: https://github.com/NodeppOficial/nodepp-wasm
📌Raylib: https://www.raylib.com/
```

## Preview
[preview](https://github.com/user-attachments/assets/39532eca-f0e7-465a-9ea1-89193f3c6251)

## Build & Use
```bash
em++ -o www/index.js main.cpp                      \
     -I./include -L./lib -lraylib -lwebsocket.js   \
     -s WEBSOCKET_SUBPROTOCOL=1 -s WEBSOCKET_URL=1 \
     -s ASYNCIFY=1 -s FETCH=1 -s WASM=1            \
     -s USE_GLFW=3 -s USE_PTHREADS=1               \
     -s ERROR_ON_UNDEFINED_SYMBOLS=0               \
```

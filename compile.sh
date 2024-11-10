if [ ! -f "www" ] ; then
    mkdir www
fi

em++ -o www/index.js main.cpp                      \
     -I./include -L./lib -lraylib -lwebsocket.js   \
     -s WEBSOCKET_SUBPROTOCOL=1 -s WEBSOCKET_URL=1 \
     -s ASYNCIFY=1 -s FETCH=1 -s WASM=1            \
     -s USE_GLFW=3 -s USE_PTHREADS=1               \
     -s ERROR_ON_UNDEFINED_SYMBOLS=0               \

g++ -o server server.cpp -lssl -lcrypto ; ./server
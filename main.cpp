#include <nodepp/nodepp.h>

using namespace nodepp;

#include "assets/script/game.cpp"
#include "assets/scenes/scene_0.cpp"

void onMain() {

    rl::Init( { 800, 600 }, 60, "Conway's Game of Life" );

    rl::AppendScene( rl::scene::scene_0 );

    rl::onClose([](){
        console::log("Closed");
        rl::Close();
    });

}
#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace scene {

    void scene_0( ptr_t<Scene> self ) {

        struct NODE {
            array_t<bool> list;
            int size; int len;
            ulong speed = 100;
            bool state=0;
            Vector2 dim;
        };  ptr_t<NODE> obj = new NODE();
    
    /*─······································································─*/

        obj->len  = 10; obj->size = GetRenderWidth()*GetRenderHeight()/obj->len;
        obj->list = array_t<bool>( obj->size, 0 ); obj->dim = { 
            type::cast<float>( GetRenderWidth() /obj->len ),
            type::cast<float>( GetRenderHeight()/obj->len )
        };
    
    /*─······································································─*/

        function_t<Vector2,Vector2> Normalize ([=]( Vector2 pos ){
            float  x =(int)(pos.x/obj->len) % (int)(obj->dim.x);
            float  y =(int)(pos.y/obj->len) % (int)(obj->dim.y);
            return Vector2({ x*obj->len, y*obj->len });
        });

        function_t<int,Vector2> GetIndex ([=]( Vector2 pos ){
            float  x =(int)(pos.x/obj->len) % (int)(obj->dim.x);
            float  y =(int)(pos.y/obj->len) % (int)(obj->dim.y);
            return y *(int)(obj->dim.x) + x;
        });

        function_t<Vector2,int> GetVector ([=]( int index ){
            float x = index % (int)(obj->dim.x);
            float y = index / (int)(obj->dim.x);
            return Vector2({ x*obj->len, y*obj->len });
        });
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){

            if( IsKeyReleased('P') ){ obj->state =! obj->state; }
            if( IsKeyReleased('Q') ){ obj->list.fill(0); obj->state=0; }

            if( obj->state ){ return; }
        
            if( IsMouseButtonDown( 0 ) ){
                auto idx = GetIndex( GetMousePosition() );
                obj->list[idx] = 1;
            } elif( IsMouseButtonDown( 1 ) ){
                auto idx = GetIndex( GetMousePosition() );
                obj->list[idx] = 0;
            }

        });
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){ if( !obj->state ){ return; }
        [=](){ 
        coStart

            do {

            ptr_t<bool> arr ( obj->list.size(), 0 );
            
            int w = type::cast<uint>( obj->dim.x );
            int h = type::cast<uint>( obj->dim.y );

            for( int y=0; y<type::cast<int>(obj->dim.y); y++ ){ 
            for( int x=0; x<type::cast<int>(obj->dim.x); x++ ){

                uint pos = obj->dim.x * y + x, actived = 0;

                for( int k=-1; k<=1; k++ ){ for( int l=-1; l<=1; l++ ){
                
                    if( k==0 && l==0 ){ continue; } 

                    const int posX = x+l, posY = y+k;
                    const int i    = posX +posY *w;

                    if( posX < 0 || posY < 0 ){ continue; }
                    if( posX >=w || posY >=h ){ continue; }
                    if( obj->list[i] == 1 ){ actived++; } 

                }}

                if( obj->list[pos] == 1 ){
                      if( actived < 2 ) arr[pos]=false;
                    elif( actived > 3 ) arr[pos]=false;
                    else                arr[pos]=true;
                } else {
                      if( actived ==3 ) arr[pos]=true;
                    elif( actived < 2 ) arr[pos]=false;
                    else                arr[pos]=false;
                }

            }}  memcpy( obj->list.get(), &arr, arr.size() ); 
            
            } while(0); coDelay( obj->speed );

        coStop
        }();
        });
    
    /*─······································································─*/

        self->onDraw([=](){ 
            ClearBackground( BLACK );
            Vector2 pos, mouse = Normalize( GetMousePosition() );
            
            for( int x=0; x<obj->list.size(); x++ ){
             if( !obj->list[x] ){ continue; } pos = GetVector( x );
                 DrawRectangle( pos.x, pos.y, obj->len, obj->len, WHITE );
            }

            if( obj->state ){ goto DONE; }

            if( obj->list[GetIndex( GetMousePosition() )] ){
                DrawRectangleLines( mouse.x, mouse.y, obj->len, obj->len, RED );
            } else {
                DrawRectangleLines( mouse.x, mouse.y, obj->len, obj->len, GREEN );
            }

            DONE:; DrawFPS( 10, 10 );
        });
    
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/
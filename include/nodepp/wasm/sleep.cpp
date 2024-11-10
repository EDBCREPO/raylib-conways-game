/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#pragma once
#include <emscripten/emscripten.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {
    
    ulong _time_ = 0;

    ulong millis(){ return _time_; }

    ulong micros(){ return _time_ / 1000; }

    ulong seconds(){ return _time_ * 1000; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    void  delay( ulong time ){ emscripten_sleep( time ); }

    ulong now(){ return millis(); }

    void yield(){ 
        _time_ = emscripten_get_now(); 
        delay(TIMEOUT);
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/
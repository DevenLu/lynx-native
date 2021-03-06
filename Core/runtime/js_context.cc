// Copyright 2017 The Lynx Authors. All rights reserved.

#include "runtime/js_context.h"
#include "runtime/runtime.h"

namespace jscore {

    void JSContext::OnExceptionOccured(std::string &error) {
        if(runtime_ && runtime_->exception_handler()){
          runtime_->exception_handler()->OnReceiveResult(error);
        }
    }
}

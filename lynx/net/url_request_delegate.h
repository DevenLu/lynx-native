// Copyright 2017 The Lynx Authors. All rights reserved.

#ifndef URL_REQUEST_DELEGATE_H
#define URL_REQUEST_DELEGATE_H


#include "base/scoped_ptr.h"
#include "base/string/platform_string.h"
#include "base/ref_counted_ptr.h"

using namespace std;
namespace net {

class URLRequestDelegate : public base::RefCountPtr<URLRequestDelegate> {
public:
    URLRequestDelegate() {}
    virtual ~URLRequestDelegate() {}
    // Callback will be invoked on JSThread
    virtual void OnSuccess(const base::PlatformString& url, const base::PlatformString& response) {}
    // Callback will be invoked on JSThread
    virtual void OnFailed(const base::PlatformString& url, const base::PlatformString& error) {}
};
}
#endif // URL_REQUEST_DELEGATE_H

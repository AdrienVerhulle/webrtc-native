/*
* The MIT License (MIT)
*
* Copyright (c) 2015 vmolsa <ville.molsa@gmail.com> (http://github.com/vmolsa)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#ifndef WEBRTC_VIDEOSINK_H
#define WEBRTC_VIDEOSINK_H

#include "Common.h"
#include "Observers.h" 
#include "EventEmitter.h"
#include "Wrap.h"

namespace WebRTC {
  class VideoSink : public rtc::VideoSinkInterface<cricket::VideoFrame>, public RTCWrap, public EventEmitter {
   public:
    static void Init(v8::Handle<v8::Object> exports);

   private:
    VideoSink();
    ~VideoSink() final;
    
    static void New(const Nan::FunctionCallbackInfo<v8::Value> &info);
    static void Stop(const Nan::FunctionCallbackInfo<v8::Value> &info);

    static void GetOnData(v8::Local<v8::String> property, const Nan::PropertyCallbackInfo<v8::Value> &info);
    static void SetOnData(v8::Local<v8::String> property, v8::Local<v8::Value> value, const Nan::PropertyCallbackInfo<void> &info);
    
    void OnFrame(const cricket::VideoFrame &frame) final;
    void On(Event *event) final;

   protected:
     rtc::scoped_refptr<webrtc::VideoSourceInterface> _video;
     rtc::scoped_refptr<webrtc::MediaSourceInterface> _source;
     rtc::scoped_refptr<MediaStreamTrackObserver> _observer;
     
     Nan::Persistent<v8::Function> _ondata;
     
     static Nan::Persistent<v8::Function> constructor;
  };
};

#endif

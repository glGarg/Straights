#pragma once
#include <string>
#include "gst/gst.h"

class Music
{
public:
    Music(const char *);
    ~Music();
    void play();
    void stopPlaying();
    void pause();
private:
    guint busWatchId_;
    GMainLoop *loop_;
    GstBus *bus_;
    GstElement *pipeline_,
               *source_,
               *demuxer_,
               *decoder_,
               *converter_,
               *sink_;
};

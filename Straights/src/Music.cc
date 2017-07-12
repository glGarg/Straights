#include "Music.h"

namespace
{
    void onPadAdded(GstElement *element, GstPad *pad, gpointer data)
    {
        GstPad *sinkpad = gst_element_get_static_pad((GstElement *)data, "sink");
        gst_pad_link(pad, sinkpad);
        gst_object_unref(sinkpad);
    }

    gboolean busCall(GstBus *bus, GstMessage *msg, gpointer data)
    {
        GMainLoop *loop = (GMainLoop *) data;

        switch (GST_MESSAGE_TYPE (msg))
        {
            case GST_MESSAGE_EOS:
                g_main_loop_quit(loop);
                break;
            case GST_MESSAGE_ERROR:
            {
                gchar *debug;
                GError *error;
                gst_message_parse_error(msg, &error, &debug);
                g_free(debug);
                g_error_free(error);
                g_main_loop_quit(loop);
                break;
            }
            default:
                break;
        }

        return TRUE;
    }
};

Music::Music(const char *filename) : pipeline_(gst_pipeline_new("audio-player")),
                                     source_(gst_element_factory_make("filesrc", "file-source")),
                                     demuxer_(gst_element_factory_make("oggdemux", "ogg-demuxer")),
                                     decoder_(gst_element_factory_make("vorbisdec", "vorbis-decoder")),
                                     converter_(gst_element_factory_make("audioconvert", "converter")),
                                     sink_(gst_element_factory_make("autoaudiosink", "audio-output")),
                                     loop_(g_main_loop_new(nullptr, FALSE))
{
    g_object_set(G_OBJECT(source_), "location", filename, nullptr);
    bus_ = gst_pipeline_get_bus(GST_PIPELINE(pipeline_));
    busWatchId_ = gst_bus_add_watch(bus_, busCall, loop_);
    gst_bin_add_many(GST_BIN(pipeline_), source_, demuxer_, decoder_, converter_, sink_, nullptr);
    gst_element_link(source_, demuxer_);
    gst_element_link_many(decoder_, converter_, sink_, nullptr);
    g_signal_connect(demuxer_, "pad-added", G_CALLBACK(onPadAdded), decoder_);
    gst_element_set_state (pipeline_, GST_STATE_PLAYING);
}

Music::~Music()
{
    gst_element_set_state(pipeline_, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline_));
    g_source_remove(busWatchId_);
    gst_object_unref(bus_);
}

void Music::play()
{
    g_main_loop_run(loop_);
}

void Music::stopPlaying()
{
    gst_element_set_state(pipeline_, GST_STATE_NULL);
}

void Music::pause()
{
    gst_element_set_state(pipeline_, GST_STATE_PAUSED);
}

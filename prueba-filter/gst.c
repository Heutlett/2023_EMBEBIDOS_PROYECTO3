#include <gst/gst.h>

int main(int argc, char *argv[]) {
    gst_init(NULL, NULL);

    GstElement *pipeline, *source, *parse, *decode, *convert, *encode, *sink;

    // Crear los elementos
    pipeline = gst_pipeline_new("take-photo-pipeline");
    source = gst_element_factory_make("v4l2src", "source");
    parse = gst_element_factory_make("jpegparse", "parse");
    decode = gst_element_factory_make("jpegdec", "decode");
    convert = gst_element_factory_make("videoconvert", "convert");
    encode = gst_element_factory_make("pngenc", "encode");
    sink = gst_element_factory_make("filesink", "sink");

    if (!pipeline || !source || !parse || !decode || !convert || !encode || !sink) {
        g_error("Failed to create elements. Exiting.\n");
        return -1;
    }

    // Establecer las propiedades de los elementos
    g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);
    g_object_set(G_OBJECT(encode), "snapshot", TRUE, NULL);
    g_object_set(G_OBJECT(sink), "location", "foto.png", NULL);

    // Agregar elementos al pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, parse, decode, convert, encode, sink, NULL);

    // Enlazar los elementos
    if (!gst_element_link_many(source, parse, decode, convert, encode, sink, NULL)) {
        g_error("Failed to link elements. Exiting.\n");
        return -1;
    }

    // Iniciar el pipeline
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_error("Failed to start pipeline. Exiting.\n");
        return -1;
    }

    // Esperar a que termine la captura
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // Limpiar
    gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}

#include <gst/gst.h>

int main(int argc, char *argv[]) {
    // Inicializar GStreamer
    gst_init(&argc, &argv);

    // Crear el pipeline
    GstElement *pipeline = gst_pipeline_new("pipeline");

    // Crear los elementos
    GstElement *v4l2src = gst_element_factory_make("v4l2src", "v4l2-source");
    GstElement *videoconvert = gst_element_factory_make("videoconvert", "video-convert");
    GstElement *jpegenc = gst_element_factory_make("jpegenc", "jpeg-encoder");
    GstElement *filesink = gst_element_factory_make("filesink", "file-sink");

    // Verificar que todos los elementos se hayan creado correctamente
    if (!pipeline || !v4l2src || !videoconvert || !jpegenc || !filesink) {
        g_error("Error al crear elementos.");
        return -1;
    }

    // Configurar la fuente de video
    g_object_set(v4l2src, "device", "/dev/video0", NULL);

    // Configurar el destino del archivo
    g_object_set(filesink, "location", "foto.jpg", NULL);

    // Agregar los elementos al pipeline
    gst_bin_add_many(GST_BIN(pipeline), v4l2src, videoconvert, jpegenc, filesink, NULL);

    // Crear los enlaces entre los elementos
    if (!gst_element_link_many(v4l2src, videoconvert, jpegenc, filesink, NULL)) {
        g_error("Error al crear enlaces entre los elementos.");
        gst_object_unref(pipeline);
        return -1;
    }

    // Iniciar el pipeline
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_error("Error al iniciar el pipeline.");
        gst_object_unref(pipeline);
        return -1;
    }

    // Esperar a que el pipeline termine
    ret = gst_element_get_state(pipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_error("Error al esperar que el pipeline termine.");
        gst_object_unref(pipeline);
        return -1;
    }

    // Detener y liberar recursos
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}

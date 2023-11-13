lib_LTLIBRARIES = libfilter.la
include_HEADERS = $(top_srcdir)/include/filter_lib.h $(top_srcdir)/include/stb_image.h $(top_srcdir)/include/stb_image_write.h
#AM_CPPFLAGS = -I$(top_srcdir)/include
#libfilter_la_SOURCES = filter_lib.c

AM_CPPFLAGS = -I$(top_srcdir)/include $(GSTREAMER_CFLAGS)
libfilter_la_SOURCES = filter_lib.c
libfilter_la_LIBADD = $(GSTREAMER_LIBS)
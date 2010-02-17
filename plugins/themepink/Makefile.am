SUBDIRS = data

plugin_LTLIBRARIES = themepink.la
themepink_la_LDFLAGS = -avoid-version -module -shared 
themepink_la_LIBADD = data/libimagedata.a
themepink_la_SOURCES = themepink.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

INCLUDES = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinecutie -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = themepink.h 

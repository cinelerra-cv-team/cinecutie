plugin_LTLIBRARIES = svg.la
svg_la_LDFLAGS = -avoid-version -module -shared 
svg_la_LIBADD = 
svg_la_SOURCES = svg.C svgwin.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

INCLUDES = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinecutie -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

bin_PROGRAMS = cinecutie-rawc-convert
cinecutie_rawc_convert_SOURCES = cinecutie-rawc-convert.C


noinst_HEADERS = empty_svg.h picon_png.h svg.h svgwin.h 
EXTRA_DIST = picon.png

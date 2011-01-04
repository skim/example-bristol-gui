AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = bristolgui

bristolgui_SOURCES = Source/all/main.c

#FIXME: data dir (usr/share) is hardcoded, './configure --prefix=[]' won't work
bristolgui_CFLAGS = -ISource/all/include -DBG_DATA_PATH=\"/usr/share/@PACKAGE@\"

bristolguiextradir = $(datadir)/@PACKAGE@
bristolguiextra_DATA = Data/*

AM_CPPFLAGS=@GTK_CFLAGS@ @lgui_CFLAGS@

bristolgui_LDADD=@GTK_LIBS@ @lgui_LIBS@

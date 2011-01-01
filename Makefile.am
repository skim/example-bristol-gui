AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = bristolgui

bristolgui_SOURCES = Source/all/main.c

bristolgui_CFLAGS = -ISource/all/include -DL_PATH_DATA=\"$(datadir)/@PACKAGE@\"
bristolguiextradir = $(datadir)/@PACKAGE@
bristolguiextra_DATA = Data/*

AM_CPPFLAGS=@GTK_CFLAGS@ @lgui_CFLAGS@

bristolgui_LDADD=@GTK_LIBS@ @lgui_LIBS@

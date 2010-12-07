AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = bristolgui

bristolgui_SOURCES = Source/all/bg_common_basic.c Source/all/bg_common_gui.c Source/all/bg_data.c Source/all/bg_gui.c Source/all/main.c
bristolgui_CFLAGS = -ISource/all/include -DBG_PATH_DATA=\"$(datadir)/@PACKAGE@\"
bristolgui_BINARY = bristol-gui
bristolguiextradir = $(datadir)/@PACKAGE@
bristolguiextra_DATA = Data/Gtk/*

AM_CPPFLAGS=@GTK_CFLAGS@

bristolgui_LDADD=@GTK_LIBS@

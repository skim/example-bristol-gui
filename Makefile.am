AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = bristolgui

bristolgui_SOURCES = Source/all/bg_common.c Source/all/bg_control.c Source/all/bg_gui.c Source/all/bg_session.c Source/all/main.c
bristolgui_CFLAGS = -ISource/all/include -DL_PATH_DATA=\"$(datadir)/@PACKAGE@\"
bristolguiextradir = $(datadir)/@PACKAGE@
bristolguiextra_DATA = Data/Gtk/*

AM_CPPFLAGS=@GTK_CFLAGS@

bristolgui_LDADD=@GTK_LIBS@

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = bristolgui

bristolgui_SOURCES = \
Source/all/l_common.c \
Source/all/l_option.c \
Source/all/ltk_builder.c \
Source/all/ltk_common.c \
Source/all/ltk_switch.c \
Source/all/main.c

bristolgui_CFLAGS = -ISource/all/include -DL_PATH_DATA=\"$(datadir)/@PACKAGE@\"
bristolguiextradir = $(datadir)/@PACKAGE@
bristolguiextra_DATA = Data/*

AM_CPPFLAGS=@GTK_CFLAGS@

bristolgui_LDADD=@GTK_LIBS@

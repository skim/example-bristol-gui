#!/bin/sh

aclocal
automake --add-missing
autoreconf
echo "./configure is ready"


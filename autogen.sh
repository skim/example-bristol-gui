#!/bin/sh

automake --add-missing
autoreconf
echo "./configure is ready"


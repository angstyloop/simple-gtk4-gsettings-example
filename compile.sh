#! /bin/bash

# This SHOULD work, since 
#   g_setenv ("GSETTINGS_SCHEMA_DIR", ".", FALSE);
# is called in main() in main.c
echo compile schemas in project location
glib-compile-schemas .

# In practice, I need to do this though. Otherwise GIO can't find my schema.
echo compile schemas in system location
SCHEMA_DIR=/usr/share/glib-2.0/schemas
sudo mkdir -p $SCHEMA_DIR
sudo cp org.gtk.example.gschema.xml $SCHEMA_DIR
pushd $SCHEMA_DIR > /dev/null
sudo glib-compile-schemas .
popd > /dev/null

# Compile resources
echo compile resources
glib-compile-resources example.gresource.xml  --generate-source --target=resources.c

# Compile and link code
echo compile and link code
gcc `pkg-config --cflags gtk4` -o example *.c `pkg-config --libs gtk4`

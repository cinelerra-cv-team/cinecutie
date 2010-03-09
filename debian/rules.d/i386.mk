CFLAGS=-O2 -mmmx -pipe
CXXFLAGS=$(CFLAGS)
CONFFLAGS=--enable-mmx --enable-x86 --without-pic --enable-opengl
CFLAGSXT=-O3 -mssse3 -pipe
CXXFLAGSXT=$(CFLAGSXT)
CONFFLAGSXT=--enable-mmx --enable-x86 --without-pic --enable-opengl

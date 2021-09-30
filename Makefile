LIBNAME=libssd1306.so
LIB_VERSION=1.0.0

CC=gcc
CXX=g++
CFLAGS= -Ofast -Wall
LIKER_LIBS= -li2c

SHARED_LINKER_FLAGS= -shared -Wl,-soname,libssd1306.so
SHARED_LINKER_LIBS=

LIB_DIR=/usr/local/lib
HEADER_DIR=/usr/local/include/SSD1306

LDCONFIG=ldconfig

OBJECTS=ssd1306.o fonts.o

all: $(LIBNAME)

# Make the library
$(LIBNAME): $(OBJECTS)
	@echo "[Linking]"
	$(CC) $(SHARED_LINKER_FLAGS) $(CFLAGS) -o $(LIBNAME) $^ $(SHARED_LINKER_LIBS)

# Library parts
ssd1306.o: ssd1306.c
	$(CC) -fPIC $(CFLAGS) -c $^ $(LIKER_LIBS)

fonts.o: fonts.c
	$(CC) -fPIC $(CFLAGS) -c $^ $(LIKER_LIBS)

# clear build files
clean:
	@echo "[Cleaning]"
	rm -rf *.o $(LIBNAME)

install: all install-libs install-headers

# Install the library to LIBPATH
install-libs:
	@echo "[Installing Libs to $(LIB_DIR)]"
	@if ( test ! -d $(LIB_DIR) ); then mkdir -p $(LIB_DIR); fi
	@install -m 0755 $(LIBNAME) $(LIB_DIR)
ifneq ($(LDCONFIG),)
	@$(LDCONFIG)
endif

install-headers:
	@echo "[Installing Headers to $(HEADER_DIR)]"
	@mkdir -p $(HEADER_DIR)/$(DRIVER_DIR)
	@install -m 0644 *.h $(HEADER_DIR)

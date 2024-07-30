CC := g++
CFLAGS := -O0 -g -std=c++11 -Wall -Werror -Wno-strict-aliasing -I/home/arla/dev/sta-lib/platform -DPLATFORM_SDL=1 -DPLATFORM_GRAPHICS_SOFTWARE=1
LDFLAGS := -lm -lGL -lSDL2 -lX11
TARGET = main

c:
	$(CC) $(CFLAGS) src/main.cpp -o main $(LDFLAGS)

clean:
	rm -rf obj/ $(TARGET)

.PHONY: all clean

len:
	find ./src/ -name '*.cpp' | xargs wc -l

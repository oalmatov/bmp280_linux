#LDLIBS=-li2c -lsqlite3

bmp280runner: bmp280runner.cpp bmp280.cpp bmp280.h

clean:
	rm *.o

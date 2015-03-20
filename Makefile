distance.so: distance.c
	gcc -g -fPIC -shared distance.c -lm -o distance.so

clean:
	rm -f distance.so

test: distance.so
	sqlite3 -bail -cmd '.load ./distance' -version > /dev/null && echo "Loaded distance.so" || echo "Failed to load distance.so"

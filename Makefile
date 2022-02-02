ifeq ($(UNAME), Darwin)
	SHARED_FLAG = -dynamiclib
	SHARED_EXT = dylib
else
	SHARED_FLAG = -shared
	SHARED_EXT = so
endif
distance.so: distance.c
	gcc -g -fPIC $(SHARED_FLAG) distance.c -lm -o distance.$(SHARED_EXT)

clean:
	rm -f distance.$(SHARED_EXT)

test: distance.so
	sqlite3 -bail -cmd '.load ./distance' -version > /dev/null && echo "Loaded distance.$(SHARED_EXT)" || echo "Failed to load distance.$(SHARED_EXT)"

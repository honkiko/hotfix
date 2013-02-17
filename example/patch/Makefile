

PATCH = patch.so

all: $(PATCH)

$(PATCH): patch.c
	gcc -I../.. -shared -fPIC $< -o $@

clean:
	rm -f $(PATCH)

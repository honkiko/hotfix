

PATCH = patch.so
LINK = $(PWD)/../server_to_patch/patch.so

all: $(PATCH) $(LINK)

$(PATCH): patch.c
	gcc -I../.. -shared -fPIC $< -o $@

$(LINK):
	ln -s $(PWD)/$(PATCH) $(LINK)

clean:
	rm -f $(PATCH) $(LINK)

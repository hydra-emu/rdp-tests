SUBDIRS := $(wildcard tests/*/.)

all: $(SUBDIRS)
$(SUBDIRS):
		$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
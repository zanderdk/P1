CC = gcc
DEPDIR = deps
df = $(DEPDIR)/$(*F)
SRCS = main.c

all: $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $(df).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $(df).P; \
	rm -f $*.d

-include $(SRCS:%.c=$(DEPDIR)/%.P)

clean:
	rm *.o

cleandeps:
	rm deps/*.P
CC = gcc
CFLAGS = -lm -g -Wall
DEPDIR = deps
DF = $(DEPDIR)/$(*F)
SRCS = main.c
VPATH = Sources
OUTPUT = Program

.PHONY: all
all: $(OUTPUT)

$(OUTPUT): $(SRCS:.c=.o)
	$(CC) $^ $(CFLAGS) -o $@ 

%.o: %.c | $(DEPDIR)
	$(COMPILE.c) -MMD $< -o $@
	@cp $*.d $(DF).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $(DF).P; \
	rm -f $*.d 

-include $(SRCS:%.c=$(DEPDIR)/%.P)

$(DEPDIR):
	mkdir $(DEPDIR)

.PHONY: cleanall
cleanall: cleanobjs cleandeps
	rm Program

.PHONY: cleanobjs
cleanobjs:
	rm *.o

.PHONY: cleandeps
cleandeps:
	rm -r deps
	rm *.d
CC = gcc
CFLAGS = -Wall -g
DEPDIR = deps
DF = $(DEPDIR)/$(*F)
SRCS = main.c
VPATH = Sources
OUTPUT = Program

.PHONY: all
all: Program

$(OUTPUT): $(SRCS:.c=.o)
	$(CC) $^ -o $@ $(CFLAGS) 

%.o: %.c | $(DEPDIR)
	$(COMPILE.c) -MMD -o $@ $<
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
	rm deps
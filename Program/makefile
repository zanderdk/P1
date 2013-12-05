CC = gcc
CFLAGS = -Wall
DEPDIR = deps
DF = $(DEPDIR)/$(*F)
SRCS = main.c
OUTPUT = program
VPATH = Sources

all: $(SRCS:.c=.o)
	$(CC) $^ -o $(OUTPUT) $(CFLAGS) 

%.o: %.c
	$(COMPILE.c) -MMD -o $@ $<
	@cp $*.d $(DF).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $(DF).P; \
	rm -f $*.d 

-include $(SRCS:%.c=$(DEPDIR)/%.P)

clean:
	rm *.o

cleandeps:
	rm deps/*.P

cleanall: clean cleandeps
	rm $(OUTPUT)
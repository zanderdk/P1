CC = gcc
DEPDIR = deps
DF = $(DEPDIR)/$(*F)
SRCS = ppm.c pixel.c prog.c
OUTPUT = program

all: $(SRCS:.c=.o)
	$(CC) $^ -o $(OUTPUT) 

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
GCC	    := gcc

SOURCES_C   := $(wildcard *.c)
INCLUDES    :=  
LIBS        := -lhttp_fetcher -lroxml

all: 
	$(GCC) -O4 $(LIBS) $(INCLUDES) $(SOURCES_C) -o twicli

install:

clean:
	rm -f *.o *~ twicli

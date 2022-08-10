# Makefile simples para o TP2

#./ nome do arquivo e flags ou pastas

PROGRAMS =  ufenixcat ufenixtail ufenixuniq ufenixls ufenixsort

all:: $(PROGRAMS)

CC = gcc
CFLAGS = -g -O0  -Wall $$warnflags
export warnflags = -Wfloat-equal -Wtype-limits -Wpointer-arith -Wlogical-op -Wshadow -fno-diagnostics-show-option
LDFLAGS =
LDLIBS =

$(PROGRAMS): %:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

ufenixcat ufenixtail ufenixuniq ufenixls ufenixsort: ler_linha.c

clean::
	rm -f $(PROGRAMS) *.o

.PHONY: clean all

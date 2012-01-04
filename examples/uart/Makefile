export LPC2XXX_MODEL := lpc2138
export F_CPU         := 60000000L
export HSE_Val       := 12000000L

include ../../LPC2xxx.mk

PHONY += all clean

all: uart_noirq.bin

uart_noirq.elf: libLPC2xxx.a

libLPC2xxx.a: 
	$(MAKE) -C $(LPC2XXXLIB_DIR) $@ O="$(PWD)"

clean:
	rm -f *.{o,a,elf,hex,srec,bin,prg,map}

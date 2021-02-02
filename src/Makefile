export CFLAGS	:= -c -g -Wall -I$(INCLUDE_PATH)

.PHONY : _all test alogrithms data_struct

_all : test alogrithms data_struct

test : data_struct alogrithms
	$(MAKE) -C $@

data_struct : alogrithms

alogrithms data_struct :
	$(MAKE) -C $@ 

export PRO_ROOT 		= $(PWD)
export SRC_PATH			= $(PRO_ROOT)/src
export LIB_PATH			= $(PRO_ROOT)/lib
export INCLUDE_PATH 	= $(PRO_ROOT)/include
export BIN_PATH 		= $(PRO_ROOT)/bin

.PHONY : target clean_all clean

target : 
	$(MAKE) -C $(SRC_PATH)

clean_all :
	rm -rf $(LIB_PATH)/*
	rm -rf $(BIN_PATH)/*

clean :
	find . -name '*.o' -exec rm {} \;

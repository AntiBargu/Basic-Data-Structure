export LD_FLAGS := -L$(LIB_PATH) -llist -ldata -lalogr
modules = sqlist linklist

target_path := $(addprefix $(BIN_PATH)/,	\
					$(patsubst $(SRC_PATH)/test/%,%, $(shell pwd)/))

.PHONY : $(modules)

all : $(modules) 

$(modules) :
	-mkdir $(target_path)/$@
	$(MAKE) -C $@

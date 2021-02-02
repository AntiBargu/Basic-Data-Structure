subdirs = linear_list stack bitree

.PHONY : $(subdirs)

all : $(subdirs) 

$(subdirs) :
	-mkdir $(BIN_PATH)/$@
	$(MAKE) -C $@

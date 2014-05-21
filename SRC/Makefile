#==================================================================
#  **Makefile for 4thRobot**
# 
#  Version : 1.0
#  Date    : 2014/02/15
#  Author  : Ryodo Tanaka (Kyushu Institute of Technology)
#==================================================================

#**User Defile**===================================================
#  How to Use
#    1. SRC に、main()関数を含むCソースコードの名前を指定。
#    2. SUB に、分割コンパイルするCソースコードの名前を指定。
#    3. VPATH に、分割コンパイルするCソースコードのある場所を指定。
#       ディレクトリを新たに追加するときは、":" を使って追加すること。
#    4. OPTION や DEBUG に使うgccオプションを指定。
#==================================================================

SRC		= main
SUB		= lrf
VPATH		= $(OBJ_DIR):./LRF:

#DEBUG 		= -ggdb -O0 
OPTION  	= -Wall -O2

#==================================================================



#**Macro & Makefile Code**=========================================
#  Do not change !
#==================================================================

CC 		= gcc

OPENCV_FLG	= `pkg-config --cflags opencv`
OPENCV_LIB 	= `pkg-config --libs opencv`
URG_FLG 	= `urg_c-config --cflags`
URG_LIB 	= `urg_c-config --libs`

CFLAGS 		= $(OPENCV_FLG) $(URG_FLG)
LDLIBS		= $(OPENCV_FLG) $(URG_FLG)

MKFILE 		= Makefile
TAGS		= TAGS
OBJ_DIR		= ./bin/
.PHONY: clean

OBJS		= $(SUB:%=%.o) $(SRC).o


all : $(MKFILE) $(OBJ_DIR) $(OBJS) $(SRC) $(TAGS)

$(SRC).o : $(SRC).c $(SRC).h $(SUB:%=%.h) $(MKFILE)
	$(CC) -c $< $(OPTION) $(DEBUG) $(CFLAGS) $(LDLIBS) -o $(OBJ_DIR)$@ 

%.o : %.c %.h $(MKFILE)
	$(CC) -c $< $(OPTION) $(DEBUG) $(CFLAGS) $(LDLIBS) -o $(OBJ_DIR)$@ 

$(SRC) : $(OBJS) $(MKFILE)
	$(CC) $(OBJS:%=$(OBJ_DIR)%) $(OPTION) $(DEBUG) $(CFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR) :
	mkdir $@

$(TAGS) : $(OBJS)
	etags `find ./ -name "*.[ch]"`

clean :
	rm -r $(OBJS:%=$(OBJ_DIR)%) $(SRC) $(TAGS)
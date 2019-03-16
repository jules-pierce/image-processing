# Note that this makefile must end in
# a carriage return, and "command" lines must begin with a
# tab character

#ADDING A NEW APP:
# uncomment 3 lines: APPNAMEn, SRCn, and the appropriate rm line
# fill in the APPNAMEn and SRCn lines as required by replacing the "xxx"

#############################
# Edit the APPNAME and SRC lines below
############################

# The name of the app being built
APPNAME01 = firstprog
APPNAME02 = msobel
APPNAME03 = stretchprog
APPNAME04 = colorprog
APPNAME05 = histogram
APPNAME06 = rannum
APPNAME07 = histequalize
APPNAME08 = add_noise
APPNAME09 = median_filter
APPNAME10 = cut
APPNAME11 = paste
APPNAME12 = zoom
APPNAME13 = reduce
APPNAME14 = edge_detect
APPNAME15 = test1
APPNAME16 = mandelbrot
APPNAME17 = rotate
APPNAME18 = gravity
APPNAME19 = gravity2
APPNAME20 = gravity3
APPNAME21 = gravity4
APPNAME22 = gravity5
APPNAME23 = air_hockey
APPNAME24 = air_hockey1
APPNAME25 = move_detect
APPNAME26 = distribution
APPNAME27 = central_lim
APPNAME28 = large_num
APPNAME29 = verify
APPNAME30 = pi
APPNAME31 = integral

#  The source files needed to build this app
SRC01 = firstprog.c input_bmp.c output_bmp.c imgstuff.c
SRC02 = msobel.c input_bmp.c output_bmp.c imgstuff.c
SRC03 = stretchprog.c input_bmp.c output_bmp.c imgstuff.c
SRC04 = colorprog.c input_bmp.c output_bmp.c imgstuff.c
SRC05 = histogram.c input_bmp.c output_bmp.c imgstuff.c
SRC06 = rannum.c input_bmp.c output_bmp.c imgstuff.c
SRC07 = histequalize.c input_bmp.c output_bmp.c imgstuff.c
SRC08 = add_noise.c input_bmp.c output_bmp.c imgstuff.c
SRC09 = median_filter.c input_bmp.c output_bmp.c imgstuff.c
SRC10 = cut.c input_bmp.c output_bmp.c imgstuff.c
SRC11 = paste.c input_bmp.c output_bmp.c imgstuff.c
SRC12 = zoom.c input_bmp.c output_bmp.c imgstuff.c
SRC13 = reduce.c input_bmp.c output_bmp.c imgstuff.c
SRC14 = edge_detect.c input_bmp.c output_bmp.c imgstuff.c
SRC15 = test1.c CN.c input_bmp.c output_bmp.c imgstuff.c
SRC16 = mandelbrot.c CN.c input_bmp.c output_bmp.c imgstuff.c
SRC17 = rotate.c CN.c input_bmp.c output_bmp.c imgstuff.c
SRC18 = gravity.c output_bmp.c imgstuff.c
SRC19 = gravity2.c output_bmp.c imgstuff.c
SRC20 = gravity3.c output_bmp.c imgstuff.c
SRC21 = gravity4.c output_bmp.c imgstuff.c
SRC22 = gravity5.c output_bmp.c imgstuff.c
SRC23 = air_hockey.c output_bmp.c imgstuff.c
SRC24 = air_hockey1.c output_bmp.c imgstuff.c
SRC25 = move_detect.c output_bmp.c input_bmp.c imgstuff.c
SRC26 = distribution.c input_bmp.c output_bmp.c imgstuff.c
SRC27 = central_lim.c
SRC28 = large_num.c
SRC29 = verify.c
SRC30 = pi.c output_bmp.c imgstuff.c
SRC31 = integral.c output_bmp.c imgstuff.c

#############################
# Edit the lines below if any special libraries need to be linked
# or include directories need to be searched
############################

INCLUDES = -I.

LIBS = -lm

#############################
# Should not need to edit anything below here under normal circumstances
############################

# the C++ compiler we are using, and our preferred flags
CPP = g++
CPPFLAGS = -mms-bitfields -O3 $(INCLUDES)

#How to build a .o file from a .cpp file
.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

#How to build a .o file from a .cc file
.cc.o:
	$(CPP) $(CPPFLAGS) -c $<

#How to build a .o file from a .c file
.c.o:
	$(CPP) $(CPPFLAGS) -c $<

# Strip off the .cc, .c, and .cpp suffixes for all files in SRC and replace 
# them with .o.  These object files are our dependencies for building the
# target
OBJ01 = $(addsuffix .o, $(basename $(SRC01)))
OBJ02 = $(addsuffix .o, $(basename $(SRC02)))
OBJ03 = $(addsuffix .o, $(basename $(SRC03)))
OBJ04 = $(addsuffix .o, $(basename $(SRC04)))
OBJ05 = $(addsuffix .o, $(basename $(SRC05)))
OBJ06 = $(addsuffix .o, $(basename $(SRC06)))
OBJ07 = $(addsuffix .o, $(basename $(SRC07)))
OBJ08 = $(addsuffix .o, $(basename $(SRC08)))
OBJ09 = $(addsuffix .o, $(basename $(SRC09)))
OBJ10 = $(addsuffix .o, $(basename $(SRC10)))
OBJ11 = $(addsuffix .o, $(basename $(SRC11)))
OBJ12 = $(addsuffix .o, $(basename $(SRC12)))
OBJ13 = $(addsuffix .o, $(basename $(SRC13)))
OBJ14 = $(addsuffix .o, $(basename $(SRC14)))
OBJ15 = $(addsuffix .o, $(basename $(SRC15)))
OBJ16 = $(addsuffix .o, $(basename $(SRC16)))
OBJ17 = $(addsuffix .o, $(basename $(SRC17)))
OBJ18 = $(addsuffix .o, $(basename $(SRC18)))
OBJ19 = $(addsuffix .o, $(basename $(SRC19)))
OBJ20 = $(addsuffix .o, $(basename $(SRC20)))
OBJ21 = $(addsuffix .o, $(basename $(SRC21)))
OBJ22 = $(addsuffix .o, $(basename $(SRC22)))
OBJ23 = $(addsuffix .o, $(basename $(SRC23)))
OBJ24 = $(addsuffix .o, $(basename $(SRC24)))
OBJ25 = $(addsuffix .o, $(basename $(SRC25)))
OBJ26 = $(addsuffix .o, $(basename $(SRC26)))
OBJ27 = $(addsuffix .o, $(basename $(SRC27)))
OBJ28 = $(addsuffix .o, $(basename $(SRC28)))
OBJ29 = $(addsuffix .o, $(basename $(SRC29)))
OBJ30 = $(addsuffix .o, $(basename $(SRC30)))
OBJ31 = $(addsuffix .o, $(basename $(SRC31)))

# The target APPNAME depends on the OBJ files
$(APPNAME01): $(OBJ01)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ01) $(LIBS)

$(APPNAME02): $(OBJ02)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ02) $(LIBS)

$(APPNAME03): $(OBJ03)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ03) $(LIBS)

$(APPNAME04): $(OBJ04)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ04) $(LIBS)

$(APPNAME05): $(OBJ05)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ05) $(LIBS)

$(APPNAME06): $(OBJ06)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ06) $(LIBS)

$(APPNAME07): $(OBJ07)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ07) $(LIBS)

$(APPNAME08): $(OBJ08)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ08) $(LIBS)

$(APPNAME09): $(OBJ09)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ09) $(LIBS)

$(APPNAME10): $(OBJ10)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ10) $(LIBS)

$(APPNAME11): $(OBJ11)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ11) $(LIBS)

$(APPNAME12): $(OBJ12)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ12) $(LIBS)

$(APPNAME13): $(OBJ13)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ13) $(LIBS)

$(APPNAME14): $(OBJ14)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ14) $(LIBS)

$(APPNAME15): $(OBJ15)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ15) $(LIBS)

$(APPNAME16): $(OBJ16)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ16) $(LIBS)

$(APPNAME17): $(OBJ17)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ17) $(LIBS)

$(APPNAME18): $(OBJ18)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ18) $(LIBS)

$(APPNAME19): $(OBJ19)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ19) $(LIBS)

$(APPNAME20): $(OBJ20)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ20) $(LIBS)

$(APPNAME21): $(OBJ21)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ21) $(LIBS)

$(APPNAME22): $(OBJ22)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ22) $(LIBS)

$(APPNAME23): $(OBJ23)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ23) $(LIBS)

$(APPNAME24): $(OBJ24)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ24) $(LIBS)

$(APPNAME25): $(OBJ25)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ25) $(LIBS)

$(APPNAME26): $(OBJ26)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ26) $(LIBS)

$(APPNAME27): $(OBJ27)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ27) $(LIBS)

$(APPNAME28): $(OBJ28)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ28) $(LIBS)

$(APPNAME29): $(OBJ29)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ29) $(LIBS)

$(APPNAME30): $(OBJ30)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ30) $(LIBS)

$(APPNAME31): $(OBJ31)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ31) $(LIBS)

# clean up by removing .o files and the executable
# ***the "rm" lines below must be preceded by a TAB****
clean:
	rm -f $(OBJ01) $(APPNAME01).exe Makefile.am
	rm -f $(OBJ02) $(APPNAME02).exe Makefile.am
	rm -f $(OBJ03) $(APPNAME03).exe Makefile.am
	rm -f $(OBJ04) $(APPNAME04).exe Makefile.am
#rm -f $(OBJ05) $(APPNAME05).exe Makefile.am
#rm -f $(OBJ06) $(APPNAME06).exe Makefile.am
#rm -f $(OBJ07) $(APPNAME07).exe Makefile.am
#rm -f $(OBJ08) $(APPNAME08).exe Makefile.am
#rm -f $(OBJ09) $(APPNAME09).exe Makefile.am
#rm -f $(OBJ10) $(APPNAME10).exe Makefile.am
#rm -f $(OBJ11) $(APPNAME11).exe Makefile.am
#rm -f $(OBJ12) $(APPNAME12).exe Makefile.am
#rm -f $(OBJ13) $(APPNAME13).exe Makefile.am
#rm -f $(OBJ14) $(APPNAME14).exe Makefile.am
#rm -f $(OBJ15) $(APPNAME15).exe Makefile.am
#rm -f $(OBJ16) $(APPNAME16).exe Makefile.am
#rm -f $(OBJ17) $(APPNAME17).exe Makefile.am
#rm -f $(OBJ18) $(APPNAME18).exe Makefile.am
#rm -f $(OBJ19) $(APPNAME19).exe Makefile.am
#rm -f $(OBJ20) $(APPNAME20).exe Makefile.am
#rm -f $(OBJ21) $(APPNAME21).exe Makefile.am
#rm -f $(OBJ22) $(APPNAME22).exe Makefile.am
#rm -f $(OBJ23) $(APPNAME23).exe Makefile.am
#rm -f $(OBJ24) $(APPNAME24).exe Makefile.am
#rm -f $(OBJ25) $(APPNAME25).exe Makefile.am
#rm -f $(OBJ26) $(APPNAME26).exe Makefile.am
#rm -f $(OBJ27) $(APPNAME27).exe Makefile.am
#rm -f $(OBJ28) $(APPNAME28).exe Makefile.am
#rm -f $(OBJ30) $(APPNAME30).exe Makefile.am
#rm -f $(OBJ31) $(APPNAME31).exe Makefile.am

# executing this target will add .h dependencies on the end of this
# file.  NOTE: this doesn't work on windows under mingw, msys
depend:
	makedepend $(CPPFLAGS) -Y $(SRC)

# can list .o dependencies on .h files here manually if desired.  This
# can be useful on a platform where makedepend does not work.
# NOTE: the file must end in a carriage return


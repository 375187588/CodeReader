# platform_hpux_orbix.GNU,v 4.5 1997/09/10 16:47:17 levine Exp

# Assume the existence of Orbix with HP/UX...

debug = 1

CC		= /bin/cc
CXX		= /usr/bin/CC
CFLAGS		= -Aa -z +z
CCFLAGS		= $(CFLAGS) -pta -ptb
DCFLAGS		+= -g
DLD		= $(CXX)
LD		= $(CXX) 
INCLDIRS        = -I$(ORBIX_ROOT)/include
PIC		= 
ARFLAGS		= ruv
RANLIB		= echo
LDFLAGS		= -L$(ORBIX_ROOT)/lib -L$(ACE_ROOT)/ace -Wl,+s
SOFLAGS		= -b
SOBUILD     = @echo ""; \
  echo "$(COMPILE.cc) $(PIC) -o $(VSHDIR)$*.o $<"; \
  $(COMPILE.cc) $(PIC) -o $(VSHDIR)$*.o $<; \
  $(RM) -rf $(VSHDIR)pt$*; mkdir $(VSHDIR)pt$*; \
  echo "int main() { return 0; }" >dummy.C; \
  echo "$(CXX) $(CCFLAGS) $(PIC) $(CPPFLAGS) $(LDFLAGS) -ptr$(VSHDIR)pt$* -ptr./ptrepository dummy.C $<";\
  YYZ="`$(CXX) $(CCFLAGS) $(PIC) $(CPPFLAGS) $(LDFLAGS) -ptr$(VSHDIR)pt$* -ptr./ptrepository dummy.C $<`"; \
  $(RM) -rf a.out dummy.*; \
  YYZ="`echo $(VSHDIR)pt$*/*.o`"; \
  echo "$(SOLINK.cc) -o $@ ./$(VSHDIR)$*.o $(YYZ)"; \
  $(SOLINK.cc) -o $@ ./$(VSHDIR)$*.o $(YYZ)

#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages
override XDCROOT = D:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages;D:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif

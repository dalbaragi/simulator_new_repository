#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ndk_2_24_02_31/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages;D:/ti/mathlib_c66x_3_0_1_1/packages;D:/ti/xdais_7_21_01_07/packages;D:/ti/xdais_7_21_01_07/examples;D:/ti/uia_1_01_00_04/packages;D:/ti/nsp_1_10_03_15/packages
override XDCROOT = D:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ndk_2_24_02_31/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages;D:/ti/mathlib_c66x_3_0_1_1/packages;D:/ti/xdais_7_21_01_07/packages;D:/ti/xdais_7_21_01_07/examples;D:/ti/uia_1_01_00_04/packages;D:/ti/nsp_1_10_03_15/packages;D:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif

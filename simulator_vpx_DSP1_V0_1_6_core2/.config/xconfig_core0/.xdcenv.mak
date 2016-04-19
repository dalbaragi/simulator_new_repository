#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ndk_2_24_02_31/packages;D:/ti/bios_6_33_06_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages;D:/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_V0_1_3_core2/.config
override XDCROOT = D:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ndk_2_24_02_31/packages;D:/ti/bios_6_33_06_50/packages;D:/ti/mcsdk_2_01_02_06/demos;D:/ti/ccsv5/ccs_base;D:/ti/ipc_1_24_03_32/packages;D:/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_V0_1_3_core2/.config;D:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif

#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ccsv5/ccs_base;D:/ti/mcsdk_2_01_02_06/demos;D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/.config
override XDCROOT = D:/ti/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ccsv5/ccs_base;D:/ti/mcsdk_2_01_02_06/demos;D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/.config;D:/ti/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif

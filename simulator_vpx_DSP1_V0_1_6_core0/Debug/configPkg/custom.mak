## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/core0_pe66.oe66

linker.cmd: package/cfg/core0_pe66.xdl
	$(SED) 's"^\"\(package/cfg/core0_pe66cfg.cmd\)\"$""\"D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core0/Debug/configPkg/\1\""' package/cfg/core0_pe66.xdl > $@

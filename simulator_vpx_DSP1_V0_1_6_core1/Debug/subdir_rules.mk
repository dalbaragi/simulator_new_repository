################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SRIO_switch.obj: ../SRIO_switch.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="SRIO_switch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: ../core1.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/ti/xdctools_3_23_03_53/xs" --xdcpath="D:/ti/edma3_lld_02_11_05_02/packages;D:/ti/ipc_1_24_03_32/packages;D:/ti/bios_6_35_04_50/packages;D:/ti/pdk_C6678_1_1_2_6/packages;D:/ti/ccsv5/ccs_base;D:/ti/mcsdk_2_01_02_06/demos;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platforms.evm6678 -r debug -c "D:/ti/ccsv5/tools/compiler/c6000_7.4.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: configPkg/compiler.opt
configPkg/: configPkg/compiler.opt

cppi_device.obj: ../cppi_device.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="cppi_device.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cppi_drv.obj: ../cppi_drv.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="cppi_drv.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

device_srio_loopback.obj: ../device_srio_loopback.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="device_srio_loopback.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

loopbackDioIsr_osal.obj: ../loopbackDioIsr_osal.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="loopbackDioIsr_osal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main1.obj: ../main1.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

qmss_device.obj: ../qmss_device.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="qmss_device.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

srio_drv.obj: ../srio_drv.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -g --include_path="D:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/lrh_workspace/projects/simulator_new/dsp_projects/workspace/workspace20151125/simulator_vpx_DSP1_V0_1_6_core1/common" --include_path="D:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="D:/ti/pdk_C6678_1_1_2_6/ti/drv/srio/example/SRIOLoopbackDioIsr" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="srio_drv.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



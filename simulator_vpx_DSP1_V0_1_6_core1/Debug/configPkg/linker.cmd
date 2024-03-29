/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.targets.elf package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"D:\lrh_workspace\projects\simulator_new\dsp_projects\workspace\workspace20151125\simulator_vpx_DSP1_V0_1_6_core1\Debug\configPkg\package\cfg\core1_pe66.oe66"
-l"D:\ti\ipc_1_24_03_32\packages\ti\sdo\ipc\lib\instrumented_e66\ipc\ipc.lib"
-l"D:\ti\bios_6_35_04_50\packages\ti\sysbios\lib\sysbios\instrumented\sysbios.ae66"
-l"D:\ti\pdk_C6678_1_1_2_6\packages\ti\drv\srio\lib\ti.drv.srio.ae66"
-l"D:\ti\pdk_C6678_1_1_2_6\packages\ti\drv\cppi\lib\ti.drv.cppi.ae66"
-l"D:\ti\pdk_C6678_1_1_2_6\packages\ti\drv\qmss\lib\ti.drv.qmss.ae66"
-l"D:\ti\pdk_C6678_1_1_2_6\packages\ti\csl\lib\ti.csl.ae66"
-l"D:\ti\xdctools_3_23_03_53\packages\ti\targets\rts6000\lib\ti.targets.rts6000.ae66"
-l"D:\ti\xdctools_3_23_03_53\packages\ti\targets\rts6000\lib\boot.ae66"

--retain="*(xdc.meta)"


--args 0x0
-heap  0x0
-stack 0x1000

MEMORY
{
    L2SRAM (RWX) : org = 0x800000, len = 0x80000
    MSMCSRAM (RWX) : org = 0xc000000, len = 0x400000
    DDR3 : org = 0x80000000, len = 0x20000000
}

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.elf (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from ti.targets.rts6000 (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.csl (null): */

/* Content from ti.drv.qmss (null): */

/* Content from ti.drv.cppi (null): */

/* Content from ti.drv.srio (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.sdo.ipc.family (null): */

/* Content from ti.sdo.ipc.interfaces (null): */

/* Content from ti.sysbios.family.c66 (ti/sysbios/family/c66/linkcmd.xdt): */

/* Content from ti.sysbios.rts (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios.family.c64p (ti/sysbios/family/c64p/linkcmd.xdt): */

/* Content from ti.sysbios.family.c66.tci66xx (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sdo.utils (null): */

/* Content from ti.sysbios.syncs (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.family.c62 (null): */

/* Content from ti.sysbios.timers.timer64 (null): */

/* Content from ti.sysbios.family.c64p.tci6488 (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.catalog.c6000 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.evm6678 (null): */

/* Content from ti.sdo.ipc.heaps (null): */

/* Content from ti.sdo.ipc (ti/sdo/ipc/linkcmd.xdt): */

SECTIONS
{
    ti.sdo.ipc.SharedRegion_0:  { . += 0x200000;} run > 0xc000000, type = NOLOAD
    ti.sdo.ipc.SharedRegion_1:  { . += 0x4400;} run > 0xc200000, type = NOLOAD
}


/* Content from ti.sdo.ipc.family.c647x (null): */

/* Content from ti.sdo.ipc.notifyDrivers (null): */

/* Content from ti.sdo.ipc.transports (null): */

/* Content from ti.sdo.ipc.nsremote (null): */

/* Content from ti.sdo.ipc.gates (null): */

/* Content from configPkg (null): */


/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
TSK_idle = ti_sysbios_knl_Task_Object__table__V + 76;

SECTIONS
{
    .text: load >> L2SRAM
    .ti.decompress: load > L2SRAM
    .stack: load > L2SRAM
    GROUP: load > L2SRAM
    {
        .bss:
        .neardata:
        .rodata:
    }
    .cinit: load > L2SRAM
    .pinit: load >> L2SRAM
    .init_array: load > L2SRAM
    .const: load >> L2SRAM
    .data: load >> L2SRAM
    .fardata: load >> L2SRAM
    .switch: load >> L2SRAM
    .sysmem: load > L2SRAM
    .far: load >> L2SRAM
    .args: load > L2SRAM align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> L2SRAM
    .ti.handler_table: load > L2SRAM
    systemHeap: load >> L2SRAM
    .cppi: load >> MSMCSRAM
    .qmss: load >> MSMCSRAM
    .vecs: load >> L2SRAM
    xdc.meta: load >> L2SRAM, type = COPY

}

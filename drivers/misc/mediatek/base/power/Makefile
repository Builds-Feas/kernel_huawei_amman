#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#


obj-$(CONFIG_MACH_MT3967) += drcc_v1/
obj-$(CONFIG_MACH_MT6779) += drcc_v1/

obj-$(CONFIG_MACH_MT8163) += $(subst ",,$(CONFIG_MTK_PLATFORM))/
obj-$(CONFIG_MACH_MT8173) += $(subst ",,$(CONFIG_MTK_PLATFORM))/
obj-$(CONFIG_MACH_MT6758) += spm/
obj-$(CONFIG_MACH_MT6765) += spm/
obj-$(CONFIG_MACH_MT6761) += spm/
obj-$(CONFIG_MACH_MT3967) += spm/
obj-$(CONFIG_MACH_MT6779) += spm/
obj-$(CONFIG_MACH_MT6758) += leakage_table_v2/
obj-$(CONFIG_MTK_STATIC_POWER) += leakage_table_v2/
obj-$(CONFIG_MTK_CPU_FREQ) += cpufreq_v1/
obj-$(CONFIG_MACH_MT6758) += cpufreq_v1/
ifneq ($(CONFIG_FPGA_EARLY_PORTING),y)
obj-$(CONFIG_MACH_MT6758) += eem_v2/
obj-$(CONFIG_MTK_PTPOD) += eem_v2/
endif
obj-$(CONFIG_MTK_UNIFY_POWER) += upower_v2/
ifeq ($(CONFIG_MTK_UNIFY_POWER), y)
obj-$(CONFIG_MACH_MT6758) += upower_v2/
endif
obj-$(CONFIG_MACH_MT3967) += ppm_v3/
obj-$(CONFIG_MACH_MT6761) += ppm_v3/
obj-$(CONFIG_MACH_MT6758) += ppm_v3/
obj-$(CONFIG_MACH_MT6765) += ppm_v3/
obj-$(CONFIG_MACH_MT6779) += ppm_v3/
obj-$(CONFIG_MACH_MT3967) += dcm_v1/
obj-$(CONFIG_MACH_MT6758) += dcm_v1/
obj-$(CONFIG_MACH_MT6761) += dcm_v1/
obj-$(CONFIG_MACH_MT6765) += dcm_v1/
obj-$(CONFIG_MACH_MT6779) += dcm_v1/
ifneq ($(CONFIG_FPGA_EARLY_PORTING),y)
obj-$(CONFIG_MACH_MT6758) += clkbuf_v1/
obj-$(CONFIG_MACH_MT6765) += clkbuf_v1/
obj-$(CONFIG_MACH_MT6761) += clkbuf_v1/
obj-$(CONFIG_MACH_MT3967) += clkbuf_v1/
obj-$(CONFIG_MACH_MT6779) += clkbuf_v1/
obj-$(CONFIG_MACH_MT6758) += pbm_v2/
obj-$(CONFIG_MACH_MT6765) += pbm_v4/
obj-$(CONFIG_MACH_MT6761) += pbm_v4/
obj-$(CONFIG_MACH_MT3967) += pbm_v4/
obj-$(CONFIG_MACH_MT6779) += pbm_v4/
obj-$(CONFIG_MACH_MT6765) += mdpm_v1/
obj-$(CONFIG_MACH_MT6761) += mdpm_v1/
obj-$(CONFIG_MACH_MT3967) += mdpm_v2/
obj-$(CONFIG_MACH_MT6779) += mdpm_v2/
obj-$(CONFIG_MACH_MT3967) += $(subst ",,$(CONFIG_MTK_PLATFORM))/
obj-$(CONFIG_MACH_MT6765) += $(subst ",,$(CONFIG_MTK_PLATFORM))/
obj-$(CONFIG_MACH_MT6761) += $(subst ",,$(CONFIG_MTK_PLATFORM))/
endif
obj-$(CONFIG_MACH_MT8163) += hps_v1/
obj-$(CONFIG_MACH_MT6758) += hps_v3/
obj-$(CONFIG_MACH_MT6765) += hps_v3/
obj-$(CONFIG_MACH_MT6761) += hps_v3/
obj-$(CONFIG_MACH_MT6779) += cpuhotplug/
obj-$(CONFIG_MACH_MT3967) += cpuhotplug/
obj-$(CONFIG_MACH_MT6758) += cpuidle_v3/
obj-$(CONFIG_MACH_MT6765) += cpuidle_v3/
obj-$(CONFIG_MACH_MT6761) += cpuidle_v3/
obj-$(CONFIG_MACH_MT3967) += cpuidle_v3/
obj-$(CONFIG_MACH_MT6758) += power_gs_v1/
obj-$(CONFIG_MACH_MT6765) += power_gs_v1/
obj-$(CONFIG_MACH_MT6761) += power_gs_v1/
obj-$(CONFIG_MACH_MT3967) += power_gs_v1/
obj-$(CONFIG_MACH_MT6779) += power_gs_v1/
obj-$(CONFIG_MACH_MT6758) += udi_v1/
obj-$(CONFIG_MACH_MT6765) += udi_v1/
obj-$(CONFIG_MACH_MT6761) += udi_v1/
obj-$(CONFIG_MACH_MT3967) += udi_v1/
obj-$(CONFIG_MACH_MT6758) += mcdi/
obj-$(CONFIG_MACH_MT6765) += mcdi/
obj-$(CONFIG_MACH_MT6761) += mcdi/
obj-$(CONFIG_MACH_MT6779) += mcdi/
obj-$(CONFIG_MACH_MT3967) += mcdi/
ifeq ($(CONFIG_MTK_CM_MGR), y)
obj-$(CONFIG_MACH_MT6765) += cm_mgr_v1/
obj-$(CONFIG_MACH_MT6761) += cm_mgr_v1/
obj-$(CONFIG_MACH_MT3967) += cm_mgr_v1/
endif
obj-$(CONFIG_MTK_SWPM) += swpm_v1/

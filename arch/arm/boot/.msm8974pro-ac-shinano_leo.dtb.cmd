cmd_arch/arm/boot/msm8974pro-ac-shinano_leo.dtb := /home/dev/Desktop/leo/kernel/scripts/dtc/dtc -O dtb -o arch/arm/boot/msm8974pro-ac-shinano_leo.dtb -b 0  -d arch/arm/boot/.msm8974pro-ac-shinano_leo.dtb.d arch/arm/boot/dts/msm8974pro-ac-shinano_leo.dts

source_arch/arm/boot/msm8974pro-ac-shinano_leo.dtb := arch/arm/boot/dts/msm8974pro-ac-shinano_leo.dts

deps_arch/arm/boot/msm8974pro-ac-shinano_leo.dtb := \
  arch/arm/boot/dts/msm8974pro-ac-pm8941.dtsi \
  arch/arm/boot/dts/msm8974pro-pm8941.dtsi \
  arch/arm/boot/dts/msm8974pro.dtsi \
  arch/arm/boot/dts/msm8974.dtsi \
  arch/arm/boot/dts/skeleton.dtsi \
  arch/arm/boot/dts/msm8974-camera.dtsi \
  arch/arm/boot/dts/msm8974-coresight.dtsi \
  arch/arm/boot/dts/msm-gdsc.dtsi \
  arch/arm/boot/dts/msm8974-ion.dtsi \
  arch/arm/boot/dts/msm8974-gpu.dtsi \
  arch/arm/boot/dts/msm8974-mdss.dtsi \
  arch/arm/boot/dts/msm8974-mdss-panels.dtsi \
  arch/arm/boot/dts/dsi-panel-orise-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-toshiba-720p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-sharp-qhd-video.dtsi \
  arch/arm/boot/dts/dsi-panel-generic-720p-cmd.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-1080p-video.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-dualmipi0-video.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-dualmipi1-video.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-dualmipi0-cmd.dtsi \
  arch/arm/boot/dts/dsi-panel-jdi-dualmipi1-cmd.dtsi \
  arch/arm/boot/dts/msm8974-smp2p.dtsi \
  arch/arm/boot/dts/msm8974-bus.dtsi \
  arch/arm/boot/dts/msm-rdbg.dtsi \
  arch/arm/boot/dts/msm8974-v2-iommu.dtsi \
  arch/arm/boot/dts/msm-iommu-v1.dtsi \
  arch/arm/boot/dts/msm8974-v2-iommu-domains.dtsi \
  arch/arm/boot/dts/msm8974pro-pm.dtsi \
  arch/arm/boot/dts/msm8974pro-ion.dtsi \
  arch/arm/boot/dts/msm-pm8x41-rpm-regulator.dtsi \
  arch/arm/boot/dts/msm-pm8841.dtsi \
  arch/arm/boot/dts/msm-pm8941.dtsi \
  arch/arm/boot/dts/msm8974-regulator.dtsi \
  arch/arm/boot/dts/msm8974-clock.dtsi \
  arch/arm/boot/dts/msm8974-mtp.dtsi \
  arch/arm/boot/dts/msm8974-leds.dtsi \
  arch/arm/boot/dts/msm8974pro-ac-shinano_common.dtsi \
  arch/arm/boot/dts/msm8974pro-ab-shinano_common.dtsi \
  arch/arm/boot/dts/msm8974pro-ac-shinano_leo_common.dtsi \
  arch/arm/boot/dts/msm8974pro-ac-shinano_leo.dtsi \
  arch/arm/boot/dts/dsi-panel-leo.dtsi \

arch/arm/boot/msm8974pro-ac-shinano_leo.dtb: $(deps_arch/arm/boot/msm8974pro-ac-shinano_leo.dtb)

$(deps_arch/arm/boot/msm8974pro-ac-shinano_leo.dtb):

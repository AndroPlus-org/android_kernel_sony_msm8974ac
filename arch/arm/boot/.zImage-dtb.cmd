cmd_arch/arm/boot/zImage-dtb := (cat arch/arm/boot/zImage arch/arm/boot/msm8974pro-ac-shinano_leo.dtb > arch/arm/boot/zImage-dtb) || (rm -f arch/arm/boot/zImage-dtb; false)

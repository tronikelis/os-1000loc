#!/bin/bash

set -xue

# build shell
clang \
    -std=c11 \
    -O2 \
    -g3 \
    -Wall \
    -Wextra \
    --target=riscv32-unknown-elf \
    -fno-stack-protector \
    -ffreestanding \
    -nostdlib \
    -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c

llvm-objcopy \
    --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
llvm-objcopy \
    -Ibinary -Oelf32-littleriscv shell.bin shell.bin.o

clang \
    -std=c11 \
    -O2 \
    -g3 \
    -Wall \
    -Wextra \
    --target=riscv32-unknown-elf \
    -fno-stack-protector \
    -ffreestanding \
    -nostdlib \
    -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c common.c shell.bin.o

qemu-system-riscv32 \
    -machine virt \
    -bios default \
    -nographic \
    -serial mon:stdio \
    --no-reboot \
    -kernel kernel.elf

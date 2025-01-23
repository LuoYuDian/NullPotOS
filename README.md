# NullPotOS Project

![NullPotOSLogo](./Docs/Img/Logo/Logo.bmp)

## Project brief introduction

NullPotOS is a UNIX like operating system, it is UEFI and X86_64 architecture.

--------------------------------

## Project status

##### Bootloader

- [X] UEFI
- [X] UEFI Memory Map
- [X] UEFI File System Protocol
- [X] UEFI Graphics Output Protocol

##### Kernel

- [X] Uefi Init
- [X] Uefi Graphics Output Protocol
- [X] Format output
- [X] Bmp output
- [X] A20
- [X] GDT
- [ ] TSS
- [ ] IDT

##### Hal

- [X] IO

##### Drivers

- [X] Serial Port Driver
- [X] Beep Driver
- [X] Gop

## Build and run NullPotOS Project

#### Get ready

- Linux (Because use Linux to build the project,Windows use WSL2)
- Git (Because use Git to clone the project)
- Python 3.10+ (Because use Python to build the project)
- SignTool (Because use SignTool to sign the project)
- GCC (Because use GCC to build the Kernel)
- MinGW (Because use MinGW to build the Bootloader)
- QEMU (Because use QEMU to run the project)
- GDB (Because use GDB to debug the project)

#### My build configuration

- Intel(R) Xeon(R) CPU E5-2676 v3 @ 2.40GHz   2.40 GHz(12 cores and 24 threads)
- 4 * 16GB DDR3
- 1 * 1TB SSD

- Windows 11 24H2 Pro
- WSL2
- Python 3.12.7
- GCC 13.2.0
- MinGW 14.2.0
- QEMU 9.1.0
- GDB 14.2

#### Start

``` Shell
git clone https://github.com/LuoYuDian/NullPotOS.git
cd NullPotOS
```

Open your WSL2

#### Build

``` Shell
make all
```

If you want to clean the project, you can use the following command

``` Shell
make Clean
```

#### Run

``` Shell
make Run
```

Of course, you can also boot it on a real machine.

###### Tip:

The premise is that you have a USB flash drive with a Fat32 file system and a computer with Uefi firmware

## Refer to the documentation

[Intel® 64 and IA-32 Architectures Software Developers' Manual-volumes-1-2abcd-3abcd-4](./Docs/Intel®%2064%20and%20IA-32%20Architectures%20Software%20Developers'%20Manual-volumes-1-2abcd-3abcd-4.pdf)

[UEFI Specification](./Docs/UEFI_Spec_2_10_Aug29.pdf)

## Project License

NullPotOS is licensed under the [MIT LISENSE](LICENSE.md) -You should see the LICENSE file for more details

## Project Developer

[LuoYuDian](https://github.com/LuoYuDian) - Project Founder

[MaxSinoh](https://github.com/MaxSinoh) - Project Developer and Contributor

## Coed line

`117491`
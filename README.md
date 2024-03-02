# WSL2 ARM64 Init

A simple C-program that loads some required kernel modules before loading /init.

## Quickstart

Build, place at /init-wsl and set add to your .wslconfig:

```
[wsl2]
kernel=C:\\<location-of-debian-vmlinux>
kernelCommandLine=console=tty0 console=hvc init=/init-wsl 
```

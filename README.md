# saturdayOS
Almost written-from-scratch operating system for x86 PCs (arm is coming soon). 
I think name is because I study 6 days a week (lol). And it's written on C.

## Project State
Currently system is at version 0.3.0. 

### Who is developing project?
Me, but you can join in. Any contribution is welcomed! I don't have work email, send PRs
instead.

## Not Asked Questions
**Q**: How?<br/>
**A**: This OS written on C and uses GCC to compile. Simple.

**Q**: Basic information about saturdayOS maybe?<br/>
**A**: saturdayOS is currently 32-bit and only on x86. UEFI and ARM are planned.

**Q**: How to modify the OS?<br/>
**A**: saturdayOS build system uses makefile-like files called `pointer.txt`s. These are 
little scripts describing what build system must do. Currently no docs, because I have no 
time, you can read build script code.

**Q**: How to compile it?<br/>
**A**: Run `build.py` script with Python 3. Resulting Live CD can be found in build-\<arch name\>. 
By default, it builds system for i386. You can provide `--arch <arch name>` argument to build for 
another architecture. If you want for it to automatically run QEMU, pass `run` option.


**Q**: Minimum system requirements?<br/>
**A**: Sure,

| RAM           | Disk       | CD-ROM              | Video           | CPU                |
|---------------|------------|---------------------|-----------------|--------------------|
| 16 MiB, maybe | recomended | yes, needed to boot | VGA-compatible  | starting from i386 |


**Q**: Recomended system requirements?<br/>
**A**: Sure,

| RAM           | Disk       | CD-ROM              | Video           | CPU                   |
|---------------|------------|---------------------|-----------------|-----------------------|
| 24 MiB, maybe | recomended | yes, needed to boot | VGA-compatible  | starting from Pentium |


**Q**: Can I make apps or drivers for this OS?<br/>
**A**: Somewhat. Process infrastructure is almost done! Stay tuned.


**Q**: Can I install system to drive?<br/>
**A**: Yes, but you need to install it manually. Not recommended though.

## Credits

Brandon Freisen - For making bkern, which serves as foundation for satkrnl. License: public domain, perhaps.

Limine Contributors - For making Limine bootloader, which serves as saturdayOS bootloader. License: BSD-2-Clause.

Contributors - For saturdayOS. License: BSD-3-Clause.

<b>Copyright 2022-2023 saturdayOS Project.</b>

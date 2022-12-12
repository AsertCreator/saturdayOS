# saturdayOS
Written-from-scratch (almost) operating system for x86 PCs. 
I think name is because i study 6 days a week (lol)

### Development process
Currently system is at version 0.1.0. I guess 
Almost implemented features:
- IDT
- GDT
- PIT
- PS2
- Simple memory allocator without freeing
Will be implemented:
- Normal memory allocator
Third-party features:
- None

### Not Asked Questions
**Q**: How?

**A**: This OS written on C++ and uses `x86-64-elf-gcc` to compile.


**Q**: Minimum system requirements?
| RAM          | Disk | CD-ROM | Video | CPU |
|--------------|------|--------|-------|-----|
| 2 MiB, maybe | none | none   | any   | any |


**Q**: Recomended system requirements?

**A**: Same as minimum


**Q**: Can I make apps or drivers for this OS?

**A**: No


**Q**: Can I install system to drive?

**A**: Yes, but you need to install it manually

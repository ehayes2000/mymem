# An exploratory implementation of `malloc`

Manage process memory using `sbrk` and by storing block metadata.

Malloc either finds free memory or gets more momory from the OS. Free frees and coalesces adjacent free memory. This is a simple and naive implimentation and there are some obvious optimizations that could be made. 

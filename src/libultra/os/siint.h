#ifndef _LIBULTRA_SIINT_H
#define _LIBULTRA_SIINT_H

void __osSiGetAccess(void);
void __osSiRelAccess(void);
int __osSiDeviceBusy(void);
void __osSiCreateAccessQueue(void);

#endif

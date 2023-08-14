
#ifndef __otp_h__
#define __otp_h__

#include "TOTP.h"
#include "utils.h"

byte *load_key();

extern TOTP otp;
#endif


#ifndef __otp_h__
#define __otp_h__

#include "TOTP.h"
#include "utils.h"
#include "config.h"

TOTP *otp;

inline void start_otp(env_t &env) { otp = new TOTP(env.otp.secret, env.otp.size, 60); }
#endif

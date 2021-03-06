/**
   @brief Internal iphb service definitions

   @file iphb_internal.h

   Internal iphb service definitions

   <p>
   Copyright (C) 2008-2010 Nokia. All rights reserved.

   @author Raimo Vuonnala <raimo.vuonnala@nokia.com>
   @author Semi Malinen <semi.malinen@nokia.com>

   This file is part of Dsme.

   Dsme is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Dsme is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Dsme.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef IPHB_INTERNAL_H
#define IPHB_INTERNAL_H

#include <sys/types.h>

#define HB_SOCKET_PATH		"/dev/shm/iphb"	    /**@brief IPC path between client and iphbd */
#define HB_KERNEL_DEVICE        "/dev/iphb"	    /**@brief Device between kernel module and iphbd */
#define HB_KERNEL_DEVICE_TEST   "/tmp/iphb"	    /**@brief Test device between kernel module and iphbd */

#define HB_MINTIME(__interval) (__interval - __interval/3)	/* Default minimum heartbeat wait time	*/
#define HB_MAXTIME(__interval) (__interval + __interval/3)	/* Default maximum heartbeat wait time  */

#define HB_LKM_KICK_ME_PERIOD    	"30"				/**@brief Period (seconds) the kernel sends messages to iphbd when IP traffic is seen */

/**@brief Message from iphbd to client open request */
struct _iphb_open_resp_t {
  /*!< Hartbeat interval */
  int timeout;
  /*!< iphbd client id */
  unsigned long uid;
};

/**@brief Message from client to iphbd ("wake me up") */
struct _iphb_wait_req_t {
  unsigned short mintime;	/*!< minimum wait time in seconds, zero means use default */
  unsigned short maxtime;	/*!< maximum wait time in seconds, zero means use default */
  pid_t          pid;           /*!< client process ID (PID) */
};

/**@brief Message from iphbd to client ("wake up!") */
struct _iphb_wait_resp_t {
  time_t waited;  /*!< time in secs client really waited */
};

/**@brief Command code */
enum _iphb_cmd_t {
  IPHB_WAIT = 0,  /*!< wait heartbeat */
  IPHB_STAT = 1,  /*!< get statistics */
};

/**@brief Request */
struct _iphb_req_t {
  enum _iphb_cmd_t cmd;		   /*!< command code */
  union {
    struct _iphb_wait_req_t wait;  /*!< wait request */
    char dummy[64];
  }
  u;
};

#endif  /* IPHB_INTERNAL_H */


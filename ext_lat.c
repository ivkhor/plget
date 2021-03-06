/*
 * Copyright (C) 2017
 * Authors:	Ivan Khoronzhuk <ivan.khoronzhuk@linaro.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/net_tstamp.h>
#include <time.h>
#include "rx_lat.h"
#include "tx_lat.h"
#include "ext_lat.h"

int extlat(struct plgett *plget)
{
	int sid = plget->stream_id;
	unsigned int i = 0;

	for (; i < plget->pkt_num; ++i) {
		*plget->seq_id_wr = htons((i & SEQ_ID_MASK) | sid);
		*plget->packet_id_wr = i;
		txlat_proc_packet(plget);
		rxlat_proc_packet(plget);
	}

	return 0;
}

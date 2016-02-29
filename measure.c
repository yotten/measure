#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "pktlib.h"

int main(int argc, char *argv[])
{
	pktif_t pktif;
	int r, packets = 0, bytes = 0;
	char buffer[65536];
	time_t oldtime = 0, nowtime;

	pktif = pktif_open(argv[1], 0, 0); /* インターフェースをオープンする */

	while (1) {
		r = 0;
		if (pktlib_iflist_select(1000)) /* 受信待ち */
			r = pktif_recv(pktif, buffer, sizeof(buffer), NULL); /* パケットを受信 */

		time(&nowtime);
		if (oldtime != nowtime) { /* １秒ごとに統計を表示 */
			printf("%dpackets / %dbytes\n", packets, bytes);
			packets = bytes = 0;
			oldtime = nowtime;
		}

		if (r > 0) { /* 統計をカウント */
			packets++; /* パケット数 */
			bytes += r; /* 総サイズ */
		}
	}

  return 0;
}

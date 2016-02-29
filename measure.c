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

	pktif = pktif_open(argv[1], 0, 0); /* ���󥿡��ե������򥪡��ץ󤹤� */

	while (1) {
		r = 0;
		if (pktlib_iflist_select(1000)) /* �����Ԥ� */
			r = pktif_recv(pktif, buffer, sizeof(buffer), NULL); /* �ѥ��åȤ���� */

		time(&nowtime);
		if (oldtime != nowtime) { /* ���ä��Ȥ����פ�ɽ�� */
			printf("%dpackets / %dbytes\n", packets, bytes);
			packets = bytes = 0;
			oldtime = nowtime;
		}

		if (r > 0) { /* ���פ򥫥���� */
			packets++; /* �ѥ��åȿ� */
			bytes += r; /* ������ */
		}
	}

  return 0;
}

/*
 * Copyright (c) 2012, Sucola Superiore Sant'Anna
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Sniffer example for the Tmote Sky platform.
 *
 * \author
 *         Original code : Daniele Alessandrelli - <d.alessandrelli@sssup.it>
 *         Changes       : Théo Plockyn - <theo.plockyn@etudiant.univ-lille1.fr>
 *         Changes       : Rémy Debue - <remy.debue@etudiant.univ-lille1.fr>
 */



#include "contiki.h"
#include "netstack.h"
#include "net/packetbuf.h"
#include "dev/cc2420.h"
#include "lib/ringbuf.h"

#define DEBUG DEBUG_NONE
#include "net/uip-debug.h"

#define set_channel cc2420_set_channel

/*---------------------------------------------------------------------------*/

// TEST BUFFER CYCLIQUE
#define RING_SIZE 128
struct ringbuf infos;
uint8_t infos_array[64];

/*---------------------------------------------------------------------------*/
void
sniffer_input()
{
  uint8_t *pkt; 
  uint8_t *hdr;
  uint16_t pkt_len;
  uint16_t hdr_len;
  uint8_t rssi;
  uint8_t lqi;
  uint16_t timestamp;
  uint16_t i;

  hdr = packetbuf_hdrptr();
  hdr_len = packetbuf_hdrlen();
  pkt = packetbuf_dataptr();
  pkt_len = packetbuf_datalen();
  rssi = packetbuf_attr(PACKETBUF_ATTR_RSSI);
  lqi = packetbuf_attr(PACKETBUF_ATTR_LINK_QUALITY);
  timestamp = packetbuf_attr(PACKETBUF_ATTR_TIMESTAMP);
  
  // TEST BUFFER CYCLIQUE
  if(ringbuf_put(*infos, 0xFF)==0){
        ringbuf_get(*infos);
        ringbuf_put(*infos, 0xFF);
  }
  
  printf("New packet\n");
  printf("Header len: %u\n", hdr_len);
  printf("Header:\n");
  for (i = 0; i < hdr_len; i++) {
    if(i%20==0) {printf("\n");}
    printf(" %2x", hdr[i]);
  }
  printf("Packet len: %u\n", pkt_len);
  printf("Packet:\n");
  for (i = 0; i < pkt_len; i++) {
    if(i%20==0) {printf("\n");}
    printf(" %2x", pkt[i]);
  }
  printf("\n");
  printf("RSSI: %u\n", 255 - rssi);
  printf("LQI: %u\n", lqi);
  printf("Timestamp: %u\n", timestamp);
}


/*---------------------------------------------------------------------------*/
PROCESS(sniffer_process, "Sniffer process");
AUTOSTART_PROCESSES(&sniffer_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sniffer_process, ev, data)
{

  PROCESS_BEGIN();
  //TEST BUFFER CYCLIQUE
  ringbuf_init(*infos, *infos_array, 128);
  
  PRINTF("Sniffer started\n");
  NETSTACK_RADIO.on();

  while(1) {    
    PROCESS_WAIT_EVENT();
  } 

  PROCESS_EXIT();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

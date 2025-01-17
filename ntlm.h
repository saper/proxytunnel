/* Proxytunnel - (C) 2001-2008 Jos Visser / Mark Janssen    */
/* Contact:                  josv@osp.nl / maniac@maniac.nl */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ntlm.h */

#include <stdint.h>

void build_type1();
int parse_type2(unsigned char *buf);
void build_type3_response();

void build_ntlm2_response();

extern int ntlm_challenge;

extern char ntlm_type1_buf[160];
extern char ntlm_type3_buf[4096];


// Below are the flag definitions.
#define NEG_UNICODE		0x00000001
#define NEG_OEM			0x00000002
#define REQ_TARGET		0x00000004
#define NEG_NTLM		0x00000200
#define NEG_DOMAIN		0x00001000
#define NEG_WORK		0x00002000
#define NEG_LOCAL		0x00004000
#define NEG_ASIGN		0x00008000
#define TAR_DOMAIN		0x00010000
#define TAR_SERVER		0x00020000
#define TAR_SHARE		0x00040000
#define NEG_NTLM2		0x00080000
#define NEG_TARINFO		0x00800000
#define	IE_SETSTHIS		0x02000000
#define NEG_128			0x20000000
#define NEG_56			0x80000000

// Below are the NTLM Message Types
#define NTLM_TYPE_1		0x00000001
#define NTLM_TYPE_2		0x00000002
#define NTLM_TYPE_3		0x00000003


typedef struct {
	uint16_t	length;
	uint16_t	space;
	uint32_t	offset;
} security_buf_t;

typedef struct {
	uint8_t	signature[8];
	uint32_t	message_type;
	uint32_t	flags;
	security_buf_t	domain;
	security_buf_t	workstation;
} ntlm_type1;

typedef struct {
	uint8_t	signature[8];
	uint32_t	message_type;
	security_buf_t	target_name;
	uint32_t	flags;
	uint8_t	challenge[8];
	uint32_t	context1;
	uint32_t	context2;
	security_buf_t	target_info;
	uint8_t	data_start;
} ntlm_type2;

typedef struct {
	uint8_t	signature[8];
	uint32_t	message_type;
	security_buf_t	LM_response;
	security_buf_t	NTLM_response;
	security_buf_t	domain;
	security_buf_t	user;
	security_buf_t	workstation;
	uint8_t	session[8];
	uint32_t	flags;
	uint8_t	pad[8];

} ntlm_type3;

typedef struct {
	uint8_t	digest[16];
	uint32_t	signature;
	uint32_t	reserved;
	uint64_t	timestamp;
	uint8_t	client_challenge[8];
	uint32_t	unknown;
	uint32_t	data_start;
} blob;

// vim:noexpandtab:ts=4

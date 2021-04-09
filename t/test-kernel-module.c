#include <assert.h>
#include "kernel.h"
#include "../kernel-module/xt_RTPENGINE.h"

int main(void) {
	int ret;

	ret = kernel_setup_table(0);
	assert(ret == 0);

	struct rtpengine_target_info reti;

	reti = (struct rtpengine_target_info) {
		.local = {
			.family = AF_INET,
			.u.ipv4 = 0x7f000001,
			.port = 4444,
		},
		.expected_src = {
			.family = AF_INET,
			.u.ipv4 = 0x7f000001,
			.port = 5555,
		},
		.src_mismatch = MSM_IGNORE,
		.src_addr = {
			.family = AF_INET,
			.u.ipv4 = 0x7f000001,
			.port = 6666,
		},
		.dst_addr = {
			.family = AF_INET,
			.u.ipv4 = 0x7f000001,
			.port = 7777,
		},
		.decrypt = {
			.cipher = REC_NULL,
			.hmac = REH_NULL,
		},
		.encrypt = {
			.cipher = REC_AEAD_AES_GCM_256,
			.hmac = REH_NULL,
			.master_key_len = 32,
			.master_salt_len = 12,
			.session_key_len = 32,
			.session_salt_len = 12,
			.master_key = {
				0xb8, 0x9a, 0x55, 0xee, 0xd9, 0xb6, 0x6f, 0xca, 0x76, 0xd3, 0x2a, 0x7e,
				0x49, 0xfb, 0x8e, 0xa7, 0xff, 0xa7, 0xa9, 0xcd, 0x46, 0x42, 0x93, 0xf2,
				0xd6, 0x23, 0x2c, 0x65, 0x77, 0x06, 0xdc, 0x71
			},
			.master_salt = {
				0xc5, 0xd5, 0x69, 0x14, 0x90, 0x6a, 0x15, 0xfc, 0x52, 0x7b, 0x0a, 0xdb
			},
		},
		.rtp = 1,
	};

	ret = kernel_add_stream(&reti);
	assert(ret == 0);

	return 0;
}

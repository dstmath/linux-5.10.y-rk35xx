/*
 * Copyright (c) 2017		Intel Deutschland GmbH
 * Copyright (c) 2018-2019, 2021-2022 Intel Corporation
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef __RADIOTAP_H
#define __RADIOTAP_H

#include <linux/kernel.h>
#include <asm/unaligned.h>

/**
 * struct ieee82011_radiotap_header - base radiotap header
 */
struct ieee80211_radiotap_header {
	/**
	 * @it_version: radiotap version, always 0
	 */
	uint8_t it_version;

	/**
	 * @it_pad: padding (or alignment)
	 */
	uint8_t it_pad;

	/**
	 * @it_len: overall radiotap header length
	 */
	__le16 it_len;

	/**
	 * @it_present: (first) present word
	 */
	__le32 it_present;
	/**
	 * @it_optional: all remaining presence bitmaps
	 */
	__le32 it_optional[];
} __packed;

/* version is always 0 */
#define PKTHDR_RADIOTAP_VERSION	0

/* see the radiotap website for the descriptions */
enum ieee80211_radiotap_presence {
	IEEE80211_RADIOTAP_TSFT = 0,
	IEEE80211_RADIOTAP_FLAGS = 1,
	IEEE80211_RADIOTAP_RATE = 2,
	IEEE80211_RADIOTAP_CHANNEL = 3,
	IEEE80211_RADIOTAP_FHSS = 4,
	IEEE80211_RADIOTAP_DBM_ANTSIGNAL = 5,
	IEEE80211_RADIOTAP_DBM_ANTNOISE = 6,
	IEEE80211_RADIOTAP_LOCK_QUALITY = 7,
	IEEE80211_RADIOTAP_TX_ATTENUATION = 8,
	IEEE80211_RADIOTAP_DB_TX_ATTENUATION = 9,
	IEEE80211_RADIOTAP_DBM_TX_POWER = 10,
	IEEE80211_RADIOTAP_ANTENNA = 11,
	IEEE80211_RADIOTAP_DB_ANTSIGNAL = 12,
	IEEE80211_RADIOTAP_DB_ANTNOISE = 13,
	IEEE80211_RADIOTAP_RX_FLAGS = 14,
	IEEE80211_RADIOTAP_TX_FLAGS = 15,
	IEEE80211_RADIOTAP_RTS_RETRIES = 16,
	IEEE80211_RADIOTAP_DATA_RETRIES = 17,
	/* 18 is XChannel, but it's not defined yet */
	IEEE80211_RADIOTAP_MCS = 19,
	IEEE80211_RADIOTAP_AMPDU_STATUS = 20,
	IEEE80211_RADIOTAP_VHT = 21,
	IEEE80211_RADIOTAP_TIMESTAMP = 22,
	IEEE80211_RADIOTAP_HE = 23,
	IEEE80211_RADIOTAP_HE_MU = 24,
	IEEE80211_RADIOTAP_ZERO_LEN_PSDU = 26,
	IEEE80211_RADIOTAP_LSIG = 27,
	IEEE80211_RADIOTAP_TLV = 28,

	/* valid in every it_present bitmap, even vendor namespaces */
	IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE = 29,
	IEEE80211_RADIOTAP_VENDOR_NAMESPACE = 30,
	IEEE80211_RADIOTAP_EXT = 31,
	IEEE80211_RADIOTAP_EHT_USIG = 33,
	IEEE80211_RADIOTAP_EHT = 34,
};

/* for IEEE80211_RADIOTAP_FLAGS */
enum ieee80211_radiotap_flags {
	IEEE80211_RADIOTAP_F_CFP = 0x01,
	IEEE80211_RADIOTAP_F_SHORTPRE = 0x02,
	IEEE80211_RADIOTAP_F_WEP = 0x04,
	IEEE80211_RADIOTAP_F_FRAG = 0x08,
	IEEE80211_RADIOTAP_F_FCS = 0x10,
	IEEE80211_RADIOTAP_F_DATAPAD = 0x20,
	IEEE80211_RADIOTAP_F_BADFCS = 0x40,
};

/* for IEEE80211_RADIOTAP_CHANNEL */
enum ieee80211_radiotap_channel_flags {
	IEEE80211_CHAN_CCK = 0x0020,
	IEEE80211_CHAN_OFDM = 0x0040,
	IEEE80211_CHAN_2GHZ = 0x0080,
	IEEE80211_CHAN_5GHZ = 0x0100,
	IEEE80211_CHAN_DYN = 0x0400,
	IEEE80211_CHAN_HALF = 0x4000,
	IEEE80211_CHAN_QUARTER = 0x8000,
};

/* for IEEE80211_RADIOTAP_RX_FLAGS */
enum ieee80211_radiotap_rx_flags {
	IEEE80211_RADIOTAP_F_RX_BADPLCP = 0x0002,
};

/* for IEEE80211_RADIOTAP_TX_FLAGS */
enum ieee80211_radiotap_tx_flags {
	IEEE80211_RADIOTAP_F_TX_FAIL = 0x0001,
	IEEE80211_RADIOTAP_F_TX_CTS = 0x0002,
	IEEE80211_RADIOTAP_F_TX_RTS = 0x0004,
	IEEE80211_RADIOTAP_F_TX_NOACK = 0x0008,
	IEEE80211_RADIOTAP_F_TX_NOSEQNO = 0x0010,
	IEEE80211_RADIOTAP_F_TX_ORDER = 0x0020,
};

/* for IEEE80211_RADIOTAP_MCS "have" flags */
enum ieee80211_radiotap_mcs_have {
	IEEE80211_RADIOTAP_MCS_HAVE_BW = 0x01,
	IEEE80211_RADIOTAP_MCS_HAVE_MCS = 0x02,
	IEEE80211_RADIOTAP_MCS_HAVE_GI = 0x04,
	IEEE80211_RADIOTAP_MCS_HAVE_FMT = 0x08,
	IEEE80211_RADIOTAP_MCS_HAVE_FEC = 0x10,
	IEEE80211_RADIOTAP_MCS_HAVE_STBC = 0x20,
};

enum ieee80211_radiotap_mcs_flags {
	IEEE80211_RADIOTAP_MCS_BW_MASK = 0x03,
	IEEE80211_RADIOTAP_MCS_BW_20 = 0,
	IEEE80211_RADIOTAP_MCS_BW_40 = 1,
	IEEE80211_RADIOTAP_MCS_BW_20L = 2,
	IEEE80211_RADIOTAP_MCS_BW_20U = 3,

	IEEE80211_RADIOTAP_MCS_SGI = 0x04,
	IEEE80211_RADIOTAP_MCS_FMT_GF = 0x08,
	IEEE80211_RADIOTAP_MCS_FEC_LDPC = 0x10,
	IEEE80211_RADIOTAP_MCS_STBC_MASK = 0x60,
	IEEE80211_RADIOTAP_MCS_STBC_1 = 1,
	IEEE80211_RADIOTAP_MCS_STBC_2 = 2,
	IEEE80211_RADIOTAP_MCS_STBC_3 = 3,
	IEEE80211_RADIOTAP_MCS_STBC_SHIFT = 5,
};

/* for IEEE80211_RADIOTAP_AMPDU_STATUS */
enum ieee80211_radiotap_ampdu_flags {
	IEEE80211_RADIOTAP_AMPDU_REPORT_ZEROLEN = 0x0001,
	IEEE80211_RADIOTAP_AMPDU_IS_ZEROLEN = 0x0002,
	IEEE80211_RADIOTAP_AMPDU_LAST_KNOWN = 0x0004,
	IEEE80211_RADIOTAP_AMPDU_IS_LAST = 0x0008,
	IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR = 0x0010,
	IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_KNOWN = 0x0020,
	IEEE80211_RADIOTAP_AMPDU_EOF = 0x0040,
	IEEE80211_RADIOTAP_AMPDU_EOF_KNOWN = 0x0080,
};

/* for IEEE80211_RADIOTAP_VHT */
enum ieee80211_radiotap_vht_known {
	IEEE80211_RADIOTAP_VHT_KNOWN_STBC = 0x0001,
	IEEE80211_RADIOTAP_VHT_KNOWN_TXOP_PS_NA = 0x0002,
	IEEE80211_RADIOTAP_VHT_KNOWN_GI = 0x0004,
	IEEE80211_RADIOTAP_VHT_KNOWN_SGI_NSYM_DIS = 0x0008,
	IEEE80211_RADIOTAP_VHT_KNOWN_LDPC_EXTRA_OFDM_SYM = 0x0010,
	IEEE80211_RADIOTAP_VHT_KNOWN_BEAMFORMED = 0x0020,
	IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH = 0x0040,
	IEEE80211_RADIOTAP_VHT_KNOWN_GROUP_ID = 0x0080,
	IEEE80211_RADIOTAP_VHT_KNOWN_PARTIAL_AID = 0x0100,
};

enum ieee80211_radiotap_vht_flags {
	IEEE80211_RADIOTAP_VHT_FLAG_STBC = 0x01,
	IEEE80211_RADIOTAP_VHT_FLAG_TXOP_PS_NA = 0x02,
	IEEE80211_RADIOTAP_VHT_FLAG_SGI = 0x04,
	IEEE80211_RADIOTAP_VHT_FLAG_SGI_NSYM_M10_9 = 0x08,
	IEEE80211_RADIOTAP_VHT_FLAG_LDPC_EXTRA_OFDM_SYM = 0x10,
	IEEE80211_RADIOTAP_VHT_FLAG_BEAMFORMED = 0x20,
};

enum ieee80211_radiotap_vht_coding {
	IEEE80211_RADIOTAP_CODING_LDPC_USER0 = 0x01,
	IEEE80211_RADIOTAP_CODING_LDPC_USER1 = 0x02,
	IEEE80211_RADIOTAP_CODING_LDPC_USER2 = 0x04,
	IEEE80211_RADIOTAP_CODING_LDPC_USER3 = 0x08,
};

/* for IEEE80211_RADIOTAP_TIMESTAMP */
enum ieee80211_radiotap_timestamp_unit_spos {
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MASK = 0x000F,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MS = 0x0000,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US = 0x0001,
	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_NS = 0x0003,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_MASK = 0x00F0,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_BEGIN_MDPU = 0x0000,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_PLCP_SIG_ACQ = 0x0010,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_PPDU = 0x0020,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_MPDU = 0x0030,
	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_UNKNOWN = 0x00F0,
};

enum ieee80211_radiotap_timestamp_flags {
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_64BIT = 0x00,
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_32BIT = 0x01,
	IEEE80211_RADIOTAP_TIMESTAMP_FLAG_ACCURACY = 0x02,
};

struct ieee80211_radiotap_he {
	__le16 data1, data2, data3, data4, data5, data6;
};

enum ieee80211_radiotap_he_bits {
	IEEE80211_RADIOTAP_HE_DATA1_FORMAT_MASK		= 3,
	IEEE80211_RADIOTAP_HE_DATA1_FORMAT_SU		= 0,
	IEEE80211_RADIOTAP_HE_DATA1_FORMAT_EXT_SU	= 1,
	IEEE80211_RADIOTAP_HE_DATA1_FORMAT_MU		= 2,
	IEEE80211_RADIOTAP_HE_DATA1_FORMAT_TRIG		= 3,

	IEEE80211_RADIOTAP_HE_DATA1_BSS_COLOR_KNOWN	= 0x0004,
	IEEE80211_RADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN	= 0x0008,
	IEEE80211_RADIOTAP_HE_DATA1_UL_DL_KNOWN		= 0x0010,
	IEEE80211_RADIOTAP_HE_DATA1_DATA_MCS_KNOWN	= 0x0020,
	IEEE80211_RADIOTAP_HE_DATA1_DATA_DCM_KNOWN	= 0x0040,
	IEEE80211_RADIOTAP_HE_DATA1_CODING_KNOWN	= 0x0080,
	IEEE80211_RADIOTAP_HE_DATA1_LDPC_XSYMSEG_KNOWN	= 0x0100,
	IEEE80211_RADIOTAP_HE_DATA1_STBC_KNOWN		= 0x0200,
	IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN	= 0x0400,
	IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE2_KNOWN	= 0x0800,
	IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE3_KNOWN	= 0x1000,
	IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE4_KNOWN	= 0x2000,
	IEEE80211_RADIOTAP_HE_DATA1_BW_RU_ALLOC_KNOWN	= 0x4000,
	IEEE80211_RADIOTAP_HE_DATA1_DOPPLER_KNOWN	= 0x8000,

	IEEE80211_RADIOTAP_HE_DATA2_PRISEC_80_KNOWN	= 0x0001,
	IEEE80211_RADIOTAP_HE_DATA2_GI_KNOWN		= 0x0002,
	IEEE80211_RADIOTAP_HE_DATA2_NUM_LTF_SYMS_KNOWN	= 0x0004,
	IEEE80211_RADIOTAP_HE_DATA2_PRE_FEC_PAD_KNOWN	= 0x0008,
	IEEE80211_RADIOTAP_HE_DATA2_TXBF_KNOWN		= 0x0010,
	IEEE80211_RADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN	= 0x0020,
	IEEE80211_RADIOTAP_HE_DATA2_TXOP_KNOWN		= 0x0040,
	IEEE80211_RADIOTAP_HE_DATA2_MIDAMBLE_KNOWN	= 0x0080,
	IEEE80211_RADIOTAP_HE_DATA2_RU_OFFSET		= 0x3f00,
	IEEE80211_RADIOTAP_HE_DATA2_RU_OFFSET_KNOWN	= 0x4000,
	IEEE80211_RADIOTAP_HE_DATA2_PRISEC_80_SEC	= 0x8000,

	IEEE80211_RADIOTAP_HE_DATA3_BSS_COLOR		= 0x003f,
	IEEE80211_RADIOTAP_HE_DATA3_BEAM_CHANGE		= 0x0040,
	IEEE80211_RADIOTAP_HE_DATA3_UL_DL		= 0x0080,
	IEEE80211_RADIOTAP_HE_DATA3_DATA_MCS		= 0x0f00,
	IEEE80211_RADIOTAP_HE_DATA3_DATA_DCM		= 0x1000,
	IEEE80211_RADIOTAP_HE_DATA3_CODING		= 0x2000,
	IEEE80211_RADIOTAP_HE_DATA3_LDPC_XSYMSEG	= 0x4000,
	IEEE80211_RADIOTAP_HE_DATA3_STBC		= 0x8000,

	IEEE80211_RADIOTAP_HE_DATA4_SU_MU_SPTL_REUSE	= 0x000f,
	IEEE80211_RADIOTAP_HE_DATA4_MU_STA_ID		= 0x7ff0,
	IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE1	= 0x000f,
	IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE2	= 0x00f0,
	IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE3	= 0x0f00,
	IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE4	= 0xf000,

	IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC	= 0x000f,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_20MHZ	= 0,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_40MHZ	= 1,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_80MHZ	= 2,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_160MHZ	= 3,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_26T	= 4,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_52T	= 5,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_106T	= 6,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_242T	= 7,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_484T	= 8,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_996T	= 9,
		IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_2x996T	= 10,

	IEEE80211_RADIOTAP_HE_DATA5_GI			= 0x0030,
		IEEE80211_RADIOTAP_HE_DATA5_GI_0_8			= 0,
		IEEE80211_RADIOTAP_HE_DATA5_GI_1_6			= 1,
		IEEE80211_RADIOTAP_HE_DATA5_GI_3_2			= 2,

	IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE		= 0x00c0,
		IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_UNKNOWN		= 0,
		IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_1X			= 1,
		IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_2X			= 2,
		IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_4X			= 3,
	IEEE80211_RADIOTAP_HE_DATA5_NUM_LTF_SYMS	= 0x0700,
	IEEE80211_RADIOTAP_HE_DATA5_PRE_FEC_PAD		= 0x3000,
	IEEE80211_RADIOTAP_HE_DATA5_TXBF		= 0x4000,
	IEEE80211_RADIOTAP_HE_DATA5_PE_DISAMBIG		= 0x8000,

	IEEE80211_RADIOTAP_HE_DATA6_NSTS		= 0x000f,
	IEEE80211_RADIOTAP_HE_DATA6_DOPPLER		= 0x0010,
	IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_KNOWN	= 0x0020,
	IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW		= 0x00c0,
		IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_20MHZ	= 0,
		IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_40MHZ	= 1,
		IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_80MHZ	= 2,
		IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_160MHZ	= 3,
	IEEE80211_RADIOTAP_HE_DATA6_TXOP		= 0x7f00,
	IEEE80211_RADIOTAP_HE_DATA6_MIDAMBLE_PDCTY	= 0x8000,
};

struct ieee80211_radiotap_he_mu {
	__le16 flags1, flags2;
	u8 ru_ch1[4];
	u8 ru_ch2[4];
};

enum ieee80211_radiotap_he_mu_bits {
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS		= 0x000f,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS_KNOWN		= 0x0010,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM		= 0x0020,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM_KNOWN		= 0x0040,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH2_CTR_26T_RU_KNOWN	= 0x0080,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_RU_KNOWN		= 0x0100,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH2_RU_KNOWN		= 0x0200,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_CTR_26T_RU_KNOWN	= 0x1000,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_CTR_26T_RU		= 0x2000,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_COMP_KNOWN	= 0x4000,
	IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_SYMS_USERS_KNOWN	= 0x8000,

	IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW	= 0x0003,
		IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_20MHZ	= 0x0000,
		IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_40MHZ	= 0x0001,
		IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_80MHZ	= 0x0002,
		IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_160MHZ	= 0x0003,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_KNOWN	= 0x0004,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_COMP		= 0x0008,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_SYMS_USERS	= 0x00f0,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW	= 0x0300,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW_KNOWN= 0x0400,
	IEEE80211_RADIOTAP_HE_MU_FLAGS2_CH2_CTR_26T_RU		= 0x0800,
};

enum ieee80211_radiotap_lsig_data1 {
	IEEE80211_RADIOTAP_LSIG_DATA1_RATE_KNOWN		= 0x0001,
	IEEE80211_RADIOTAP_LSIG_DATA1_LENGTH_KNOWN		= 0x0002,
};

enum ieee80211_radiotap_lsig_data2 {
	IEEE80211_RADIOTAP_LSIG_DATA2_RATE			= 0x000f,
	IEEE80211_RADIOTAP_LSIG_DATA2_LENGTH			= 0xfff0,
};

struct ieee80211_radiotap_lsig {
	__le16 data1, data2;
};

enum ieee80211_radiotap_zero_len_psdu_type {
	IEEE80211_RADIOTAP_ZERO_LEN_PSDU_SOUNDING		= 0,
	IEEE80211_RADIOTAP_ZERO_LEN_PSDU_NOT_CAPTURED		= 1,
	IEEE80211_RADIOTAP_ZERO_LEN_PSDU_VENDOR			= 0xff,
};

struct ieee80211_radiotap_tlv {
	__le16 type;
	__le16 len;
	u8 data[];
} __packed;

/* ieee80211_radiotap_eht_usig - content of U-SIG tlv (type 33)
 * see www.radiotap.org/fields/U-SIG.html for details
 */
struct ieee80211_radiotap_eht_usig {
	__le32 common;
	__le32 value;
	__le32 mask;
} __packed;

/* ieee80211_radiotap_eht - content of EHT tlv (type 34)
 * see www.radiotap.org/fields/EHT.html for details
 */
struct ieee80211_radiotap_eht {
	__le32 known;
	__le32 data[9];
	__le32 user_info[];
} __packed;

/* Known field for EHT TLV
 * The ending defines for what the field applies as following
 * O - OFDMA (including TB), M - MU-MIMO, S - EHT sounding.
 */
enum ieee80211_radiotap_eht_known {
	IEEE80211_RADIOTAP_EHT_KNOWN_SPATIAL_REUSE		= 0x00000002,
	IEEE80211_RADIOTAP_EHT_KNOWN_GI				= 0x00000004,
	IEEE80211_RADIOTAP_EHT_KNOWN_EHT_LTF			= 0x00000010,
	IEEE80211_RADIOTAP_EHT_KNOWN_LDPC_EXTRA_SYM_OM		= 0x00000020,
	IEEE80211_RADIOTAP_EHT_KNOWN_PRE_PADD_FACOR_OM		= 0x00000040,
	IEEE80211_RADIOTAP_EHT_KNOWN_PE_DISAMBIGUITY_OM		= 0x00000080,
	IEEE80211_RADIOTAP_EHT_KNOWN_DISREGARD_O		= 0x00000100,
	IEEE80211_RADIOTAP_EHT_KNOWN_DISREGARD_S		= 0x00000200,
	IEEE80211_RADIOTAP_EHT_KNOWN_CRC1			= 0x00002000,
	IEEE80211_RADIOTAP_EHT_KNOWN_TAIL1			= 0x00004000,
	IEEE80211_RADIOTAP_EHT_KNOWN_CRC2_O			= 0x00008000,
	IEEE80211_RADIOTAP_EHT_KNOWN_TAIL2_O			= 0x00010000,
	IEEE80211_RADIOTAP_EHT_KNOWN_NSS_S			= 0x00020000,
	IEEE80211_RADIOTAP_EHT_KNOWN_BEAMFORMED_S		= 0x00040000,
	IEEE80211_RADIOTAP_EHT_KNOWN_NR_NON_OFDMA_USERS_M	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_KNOWN_ENCODING_BLOCK_CRC_M	= 0x00100000,
	IEEE80211_RADIOTAP_EHT_KNOWN_ENCODING_BLOCK_TAIL_M	= 0x00200000,
	IEEE80211_RADIOTAP_EHT_KNOWN_RU_MRU_SIZE_OM		= 0x00400000,
	IEEE80211_RADIOTAP_EHT_KNOWN_RU_MRU_INDEX_OM		= 0x00800000,
	IEEE80211_RADIOTAP_EHT_KNOWN_RU_ALLOC_TB_FMT		= 0x01000000,
	IEEE80211_RADIOTAP_EHT_KNOWN_PRIMARY_80			= 0x02000000,
};

enum ieee80211_radiotap_eht_data {
	/* Data 0 */
	IEEE80211_RADIOTAP_EHT_DATA0_SPATIAL_REUSE		= 0x00000078,
	IEEE80211_RADIOTAP_EHT_DATA0_GI				= 0x00000180,
	IEEE80211_RADIOTAP_EHT_DATA0_LTF			= 0x00000600,
	IEEE80211_RADIOTAP_EHT_DATA0_EHT_LTF			= 0x00003800,
	IEEE80211_RADIOTAP_EHT_DATA0_LDPC_EXTRA_SYM_OM		= 0x00004000,
	IEEE80211_RADIOTAP_EHT_DATA0_PRE_PADD_FACOR_OM		= 0x00018000,
	IEEE80211_RADIOTAP_EHT_DATA0_PE_DISAMBIGUITY_OM		= 0x00020000,
	IEEE80211_RADIOTAP_EHT_DATA0_DISREGARD_S		= 0x000c0000,
	IEEE80211_RADIOTAP_EHT_DATA0_DISREGARD_O		= 0x003c0000,
	IEEE80211_RADIOTAP_EHT_DATA0_CRC1_O			= 0x03c00000,
	IEEE80211_RADIOTAP_EHT_DATA0_TAIL1_O			= 0xfc000000,
	/* Data 1 */
	IEEE80211_RADIOTAP_EHT_DATA1_RU_SIZE			= 0x0000001f,
	IEEE80211_RADIOTAP_EHT_DATA1_RU_INDEX			= 0x00001fe0,
	IEEE80211_RADIOTAP_EHT_DATA1_RU_ALLOC_CC_1_1_1		= 0x003fe000,
	IEEE80211_RADIOTAP_EHT_DATA1_RU_ALLOC_CC_1_1_1_KNOWN	= 0x00400000,
	IEEE80211_RADIOTAP_EHT_DATA1_PRIMARY_80			= 0xc0000000,
	/* Data 2 */
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_2_1_1		= 0x000001ff,
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_2_1_1_KNOWN	= 0x00000200,
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_1_1_2		= 0x0007fc00,
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_1_1_2_KNOWN	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_2_1_2		= 0x1ff00000,
	IEEE80211_RADIOTAP_EHT_DATA2_RU_ALLOC_CC_2_1_2_KNOWN	= 0x20000000,
	/* Data 3 */
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_1_2_1		= 0x000001ff,
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_1_2_1_KNOWN	= 0x00000200,
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_2_2_1		= 0x0007fc00,
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_2_2_1_KNOWN	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_1_2_2		= 0x1ff00000,
	IEEE80211_RADIOTAP_EHT_DATA3_RU_ALLOC_CC_1_2_2_KNOWN	= 0x20000000,
	/* Data 4 */
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_2_2_2		= 0x000001ff,
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_2_2_2_KNOWN	= 0x00000200,
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_1_2_3		= 0x0007fc00,
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_1_2_3_KNOWN	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_2_2_3		= 0x1ff00000,
	IEEE80211_RADIOTAP_EHT_DATA4_RU_ALLOC_CC_2_2_3_KNOWN	= 0x20000000,
	/* Data 5 */
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_1_2_4		= 0x000001ff,
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_1_2_4_KNOWN	= 0x00000200,
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_2_2_4		= 0x0007fc00,
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_2_2_4_KNOWN	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_1_2_5		= 0x1ff00000,
	IEEE80211_RADIOTAP_EHT_DATA5_RU_ALLOC_CC_1_2_5_KNOWN	= 0x20000000,
	/* Data 6 */
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_2_2_5		= 0x000001ff,
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_2_2_5_KNOWN	= 0x00000200,
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_1_2_6		= 0x0007fc00,
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_1_2_6_KNOWN	= 0x00080000,
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_2_2_6		= 0x1ff00000,
	IEEE80211_RADIOTAP_EHT_DATA6_RU_ALLOC_CC_2_2_6_KNOWN	= 0x20000000,
	/* Data 7 */
	IEEE80211_RADIOTAP_EHT_DATA7_CRC2_O			= 0x0000000f,
	IEEE80211_RADIOTAP_EHT_DATA7_TAIL_2_O			= 0x000003f0,
	IEEE80211_RADIOTAP_EHT_DATA7_NSS_S			= 0x0000f000,
	IEEE80211_RADIOTAP_EHT_DATA7_BEAMFORMED_S		= 0x00010000,
	IEEE80211_RADIOTAP_EHT_DATA7_NUM_OF_NON_OFDMA_USERS	= 0x000e0000,
	IEEE80211_RADIOTAP_EHT_DATA7_USER_ENCODING_BLOCK_CRC	= 0x00f00000,
	IEEE80211_RADIOTAP_EHT_DATA7_USER_ENCODING_BLOCK_TAIL	= 0x3f000000,
	/* Data 8 */
	IEEE80211_RADIOTAP_EHT_DATA8_RU_ALLOC_TB_FMT_PS_160	= 0x00000001,
	IEEE80211_RADIOTAP_EHT_DATA8_RU_ALLOC_TB_FMT_B0		= 0x00000002,
	IEEE80211_RADIOTAP_EHT_DATA8_RU_ALLOC_TB_FMT_B7_B1	= 0x000001fc,
};

enum ieee80211_radiotap_eht_user_info {
	IEEE80211_RADIOTAP_EHT_USER_INFO_STA_ID_KNOWN		= 0x00000001,
	IEEE80211_RADIOTAP_EHT_USER_INFO_MCS_KNOWN		= 0x00000002,
	IEEE80211_RADIOTAP_EHT_USER_INFO_CODING_KNOWN		= 0x00000004,
	IEEE80211_RADIOTAP_EHT_USER_INFO_NSS_KNOWN_O		= 0x00000010,
	IEEE80211_RADIOTAP_EHT_USER_INFO_BEAMFORMING_KNOWN_O	= 0x00000020,
	IEEE80211_RADIOTAP_EHT_USER_INFO_SPATIAL_CONFIG_KNOWN_M	= 0x00000040,
	IEEE80211_RADIOTAP_EHT_USER_INFO_DATA_FOR_USER		= 0x00000080,
	IEEE80211_RADIOTAP_EHT_USER_INFO_STA_ID			= 0x0007ff00,
	IEEE80211_RADIOTAP_EHT_USER_INFO_CODING			= 0x00080000,
	IEEE80211_RADIOTAP_EHT_USER_INFO_MCS			= 0x00f00000,
	IEEE80211_RADIOTAP_EHT_USER_INFO_NSS_O			= 0x0f000000,
	IEEE80211_RADIOTAP_EHT_USER_INFO_BEAMFORMING_O		= 0x20000000,
	IEEE80211_RADIOTAP_EHT_USER_INFO_SPATIAL_CONFIG_M	= 0x3f000000,
	IEEE80211_RADIOTAP_EHT_USER_INFO_RESEVED_c0000000	= 0xc0000000,
};

enum ieee80211_radiotap_eht_usig_common {
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_PHY_VER_KNOWN	= 0x00000001,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_BW_KNOWN		= 0x00000002,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_UL_DL_KNOWN		= 0x00000004,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_BSS_COLOR_KNOWN	= 0x00000008,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_TXOP_KNOWN		= 0x00000010,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_BAD_USIG_CRC		= 0x00000020,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_PHY_VER		= 0x00007000,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_BW			= 0x00038000,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_UL_DL		= 0x00040000,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_BSS_COLOR		= 0x01f80000,
	IEEE80211_RADIOTAP_EHT_USIG_COMMON_TXOP			= 0xfe000000,
};

enum ieee80211_radiotap_eht_usig_mu {
	/* MU-USIG-1 */
	IEEE80211_RADIOTAP_EHT_USIG1_MU_B20_B24_DISREGARD	= 0x0000001f,
	IEEE80211_RADIOTAP_EHT_USIG1_MU_B25_VALIDATE		= 0x00000020,
	/* MU-USIG-2 */
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B0_B1_PPDU_TYPE		= 0x000000c0,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B2_VALIDATE		= 0x00000100,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B3_B7_PUNCTURED_INFO	= 0x00003e00,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B8_VALIDATE		= 0x00004000,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B9_B10_SIG_MCS		= 0x00018000,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B11_B15_EHT_SIG_SYMBOLS = 0x003e0000,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B16_B19_CRC		= 0x03c00000,
	IEEE80211_RADIOTAP_EHT_USIG2_MU_B20_B25_TAIL		= 0xfc000000,
};

enum ieee80211_radiotap_eht_usig_tb {
	/* TB-USIG-1 */
	IEEE80211_RADIOTAP_EHT_USIG1_TB_B20_B25_DISREGARD	= 0x0000001f,

	/* TB-USIG-2 */
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B0_B1_PPDU_TYPE		= 0x000000c0,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B2_VALIDATE		= 0x00000100,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B3_B6_SPATIAL_REUSE_1	= 0x00001e00,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B7_B10_SPATIAL_REUSE_2	= 0x0001e000,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B11_B15_DISREGARD	= 0x003e0000,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B16_B19_CRC		= 0x03c00000,
	IEEE80211_RADIOTAP_EHT_USIG2_TB_B20_B25_TAIL		= 0xfc000000,
};

/**
 * ieee80211_get_radiotap_len - get radiotap header length
 */
static inline u16 ieee80211_get_radiotap_len(const char *data)
{
	const struct ieee80211_radiotap_header *hdr = (const void *)data;

	return get_unaligned_le16(&hdr->it_len);
}

#endif /* __RADIOTAP_H */

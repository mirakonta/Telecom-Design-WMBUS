#ifndef __WMBUS_TLG_API_H__
#define __WMBUS_TLG_API_H__
#ifndef __DECL_WMBUS_TLG_API_H__
#define __DECL_WMBUS_TLG_API_H__ extern
#else
#define __WMBUS_API_TLG_INIT_VAR__
#endif /* __DECL_WMBUS_TLG_API_H__ */

/**
  @file       wmbus_tlg_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Definition of macros, structures and enumerations dealing with
              Wireless M-Bus telegrams.

              Include before:
              - stezdn_typedefs.h
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/

/*==============================================================================
                            DEFINES
==============================================================================*/

/*! The telegram is not available. */
#define WMBUS_ERR_TLG_ID_INVALID        0xFFU
/*! The data could not be read because the reading index is out of range. */
#define WMBUS_ERR_INDEX_OUT_OF_RANGE    0xFFFFU
/*! Append data to the telegram. */
#define WMBUS_TLG_WRITE_APPEND          0xFFU


/*! The different frame formats: format A is used in S-, T-, C- and N-mode */
#define WMBUS_FRAME_FORMAT_A                      0x00U
/*! The different frame formats: format B is only used in C-mode */
#define WMBUS_FRAME_FORMAT_B                      0x01U

/*! Length of the manufacturer-field */
#define WMBUS_ADDR_MANUFR_LEN         2U
/*! Length of the ident number-field */
#define WMBUS_ADDR_IDENT_LEN          4U
/*! Length of the version-field */
#define WMBUS_ADDR_VERSION_LEN        1U
/*! Length of the type-field */
#define WMBUS_ADDR_TYPE_LEN           1U
/*! Length of the complete address. */
#define WMBUS_ADDR_LEN \
  (WMBUS_ADDR_MANUFR_LEN + WMBUS_ADDR_IDENT_LEN + \
    WMBUS_ADDR_VERSION_LEN + WMBUS_ADDR_TYPE_LEN)

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! \brief Enumeration of header types needed for unknown CI fields.
 *  Enumeration is used by @ref wmbus_apl_evt_getCiHeader().
 */
typedef enum
{
  /*! \brief No application header (0 bytes). */
  E_APL_HEADER_TYPE_NO,
  /*! \brief Short application header (4 bytes). */
  E_APL_HEADER_TYPE_SHORT,
  /*! \brief Long application header (12 bytes). */
  E_APL_HEADER_TYPE_LONG,
  /*! \brief Invalid header. */
  E_APL_HEADER_TYPE_INVALID
} E_APL_HEADER_TYPE_t;

/*! Status of a received telegram. */
typedef enum
{
  /*! A telegram is available. */
  E_WMBUS_RX_TLG_AVAILABLE = 0x01U,
  /*! Timeout. A request was repeated several times but no respond is
      available. */
  E_WMBUS_RX_REQUEST_TIMEOUT,
  /*! A telegram is received but there are not enough free buffers. */
  E_WMBUS_RX_BUFFER_OVERFLOW,
  /*! A telegram is read but the signature is unknown. */
  E_WMBUS_RX_SIGNATURE_UNKNOWN,
  /*! A telegram is read but there is no valid key to decrypt the message. */
  E_WMBUS_RX_SIGNATURE_ERROR,
  /*! The telegram could not be sent. */
  E_WMBUS_RX_TX_ERROR
} E_WMBUS_RX_t;

/*! Wireless M-Bus frame types. */
typedef enum
{
  /*! Frame type A:
      Checksum after maximal 16 bytes. */
  E_WMBUS_FRAME_A,
  /*! Frame type B */
  E_WMBUS_FRAME_B,
  /*! Unknown frame type. */
  E_WMBUS_FRAME_UNKNOWN
} E_WMBUS_FRAME_t;

/* Wireless M-Bus mode */
typedef enum
{
  /*! Mode S @ 868MHz. */
  E_WMBUS_MODE_S        = 0x00,
  /*! Mode T @ 868MHz. */
  E_WMBUS_MODE_T        = 0x01,
  /*! Mode C @ 868MHz. */
  E_WMBUS_MODE_C        = 0x02,
  /*! Mode N @ 169MHz. */
  E_WMBUS_MODE_N        = 0x03,
  /*! Mode S @ 868MHz. used for synchronized messages in meters */
  E_WMBUS_MODE_S_SYNC   = 0x04,
  /*! Unknown mode. */
  E_WMBUS_MODE_UNKNOWN  = 0x05
}E_WMBUS_MODE_t;

/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Wireless M-Bus address. */
PACKED_STRUCT( typedef struct S_WMBUS_ADDR_T
{
  /*! Manufacturer ID */
  uint8_t pc_manufr[WMBUS_ADDR_MANUFR_LEN];
  /*! Ident number */
  uint8_t pc_ident[WMBUS_ADDR_IDENT_LEN];
  /*! Version */
  uint8_t c_version;
  /*! Type */
  uint8_t c_type;
}, s_wmbus_addr_t);

#endif /* __WMBUS_TLG_API_H__ */

/* cell_introduce1.h -- generated by Trunnel v1.5.2.
 * https://gitweb.torproject.org/trunnel.git
 * You probably shouldn't edit this file.
 */
#ifndef TRUNNEL_CELL_INTRODUCE1_H
#define TRUNNEL_CELL_INTRODUCE1_H

#include <stdint.h>
#include "trunnel.h"

struct trn_cell_extension_st;
struct link_specifier_st;
#define TRUNNEL_SHA1_LEN 20
#define TRUNNEL_REND_COOKIE_LEN 20
#define TRUNNEL_HS_INTRO_ACK_STATUS_SUCCESS 0
#define TRUNNEL_HS_INTRO_ACK_STATUS_UNKNOWN_ID 1
#define TRUNNEL_HS_INTRO_ACK_STATUS_BAD_FORMAT 2
#define TRUNNEL_HS_INTRO_AUTH_KEY_TYPE_LEGACY0 0
#define TRUNNEL_HS_INTRO_AUTH_KEY_TYPE_LEGACY1 1
#define TRUNNEL_HS_INTRO_AUTH_KEY_TYPE_ED25519 2
#if !defined(TRUNNEL_OPAQUE) && !defined(TRUNNEL_OPAQUE_TRN_CELL_INTRODUCE1)
struct trn_cell_introduce1_st {
  uint8_t legacy_key_id[TRUNNEL_SHA1_LEN];
  uint8_t auth_key_type;
  uint16_t auth_key_len;
  TRUNNEL_DYNARRAY_HEAD(, uint8_t) auth_key;
  struct trn_cell_extension_st *extensions;
  TRUNNEL_DYNARRAY_HEAD(, uint8_t) encrypted;
  uint8_t trunnel_error_code_;
};
#endif
typedef struct trn_cell_introduce1_st trn_cell_introduce1_t;
#if !defined(TRUNNEL_OPAQUE) && !defined(TRUNNEL_OPAQUE_TRN_CELL_INTRODUCE_ACK)
struct trn_cell_introduce_ack_st {
  uint16_t status;
  struct trn_cell_extension_st *extensions;
  uint8_t trunnel_error_code_;
};
#endif
typedef struct trn_cell_introduce_ack_st trn_cell_introduce_ack_t;
#if !defined(TRUNNEL_OPAQUE) && !defined(TRUNNEL_OPAQUE_TRN_CELL_INTRODUCE_ENCRYPTED)
struct trn_cell_introduce_encrypted_st {
  uint8_t rend_cookie[TRUNNEL_REND_COOKIE_LEN];
  struct trn_cell_extension_st *extensions;
  uint8_t onion_key_type;
  uint16_t onion_key_len;
  TRUNNEL_DYNARRAY_HEAD(, uint8_t) onion_key;
  uint8_t nspec;
  TRUNNEL_DYNARRAY_HEAD(, struct link_specifier_st *) nspecs;
  TRUNNEL_DYNARRAY_HEAD(, uint8_t) pad;
  uint8_t trunnel_error_code_;
};
#endif
typedef struct trn_cell_introduce_encrypted_st trn_cell_introduce_encrypted_t;
/** Return a newly allocated trn_cell_introduce1 with all elements set
 * to zero.
 */
trn_cell_introduce1_t *trn_cell_introduce1_new(void);
/** Release all storage held by the trn_cell_introduce1 in 'victim'.
 * (Do nothing if 'victim' is NULL.)
 */
void trn_cell_introduce1_free(trn_cell_introduce1_t *victim);
/** Try to parse a trn_cell_introduce1 from the buffer in 'input',
 * using up to 'len_in' bytes from the input buffer. On success,
 * return the number of bytes consumed and set *output to the newly
 * allocated trn_cell_introduce1_t. On failure, return -2 if the input
 * appears truncated, and -1 if the input is otherwise invalid.
 */
ssize_t trn_cell_introduce1_parse(trn_cell_introduce1_t **output, const uint8_t *input, const size_t len_in);
/** Return the number of bytes we expect to need to encode the
 * trn_cell_introduce1 in 'obj'. On failure, return a negative value.
 * Note that this value may be an overestimate, and can even be an
 * underestimate for certain unencodeable objects.
 */
ssize_t trn_cell_introduce1_encoded_len(const trn_cell_introduce1_t *obj);
/** Try to encode the trn_cell_introduce1 from 'input' into the buffer
 * at 'output', using up to 'avail' bytes of the output buffer. On
 * success, return the number of bytes used. On failure, return -2 if
 * the buffer was not long enough, and -1 if the input was invalid.
 */
ssize_t trn_cell_introduce1_encode(uint8_t *output, size_t avail, const trn_cell_introduce1_t *input);
/** Check whether the internal state of the trn_cell_introduce1 in
 * 'obj' is consistent. Return NULL if it is, and a short message if
 * it is not.
 */
const char *trn_cell_introduce1_check(const trn_cell_introduce1_t *obj);
/** Clear any errors that were set on the object 'obj' by its setter
 * functions. Return true iff errors were cleared.
 */
int trn_cell_introduce1_clear_errors(trn_cell_introduce1_t *obj);
/** Return the (constant) length of the array holding the
 * legacy_key_id field of the trn_cell_introduce1_t in 'inp'.
 */
size_t trn_cell_introduce1_getlen_legacy_key_id(const trn_cell_introduce1_t *inp);
/** Return the element at position 'idx' of the fixed array field
 * legacy_key_id of the trn_cell_introduce1_t in 'inp'.
 */
uint8_t trn_cell_introduce1_get_legacy_key_id(trn_cell_introduce1_t *inp, size_t idx);
/** As trn_cell_introduce1_get_legacy_key_id, but take and return a
 * const pointer
 */
uint8_t trn_cell_introduce1_getconst_legacy_key_id(const trn_cell_introduce1_t *inp, size_t idx);
/** Change the element at position 'idx' of the fixed array field
 * legacy_key_id of the trn_cell_introduce1_t in 'inp', so that it
 * will hold the value 'elt'.
 */
int trn_cell_introduce1_set_legacy_key_id(trn_cell_introduce1_t *inp, size_t idx, uint8_t elt);
/** Return a pointer to the TRUNNEL_SHA1_LEN-element array field
 * legacy_key_id of 'inp'.
 */
uint8_t * trn_cell_introduce1_getarray_legacy_key_id(trn_cell_introduce1_t *inp);
/** As trn_cell_introduce1_get_legacy_key_id, but take and return a
 * const pointer
 */
const uint8_t  * trn_cell_introduce1_getconstarray_legacy_key_id(const trn_cell_introduce1_t *inp);
/** Return the value of the auth_key_type field of the
 * trn_cell_introduce1_t in 'inp'
 */
uint8_t trn_cell_introduce1_get_auth_key_type(const trn_cell_introduce1_t *inp);
/** Set the value of the auth_key_type field of the
 * trn_cell_introduce1_t in 'inp' to 'val'. Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce1_set_auth_key_type(trn_cell_introduce1_t *inp, uint8_t val);
/** Return the value of the auth_key_len field of the
 * trn_cell_introduce1_t in 'inp'
 */
uint16_t trn_cell_introduce1_get_auth_key_len(const trn_cell_introduce1_t *inp);
/** Set the value of the auth_key_len field of the
 * trn_cell_introduce1_t in 'inp' to 'val'. Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce1_set_auth_key_len(trn_cell_introduce1_t *inp, uint16_t val);
/** Return the length of the dynamic array holding the auth_key field
 * of the trn_cell_introduce1_t in 'inp'.
 */
size_t trn_cell_introduce1_getlen_auth_key(const trn_cell_introduce1_t *inp);
/** Return the element at position 'idx' of the dynamic array field
 * auth_key of the trn_cell_introduce1_t in 'inp'.
 */
uint8_t trn_cell_introduce1_get_auth_key(trn_cell_introduce1_t *inp, size_t idx);
/** As trn_cell_introduce1_get_auth_key, but take and return a const
 * pointer
 */
uint8_t trn_cell_introduce1_getconst_auth_key(const trn_cell_introduce1_t *inp, size_t idx);
/** Change the element at position 'idx' of the dynamic array field
 * auth_key of the trn_cell_introduce1_t in 'inp', so that it will
 * hold the value 'elt'.
 */
int trn_cell_introduce1_set_auth_key(trn_cell_introduce1_t *inp, size_t idx, uint8_t elt);
/** Append a new element 'elt' to the dynamic array field auth_key of
 * the trn_cell_introduce1_t in 'inp'.
 */
int trn_cell_introduce1_add_auth_key(trn_cell_introduce1_t *inp, uint8_t elt);
/** Return a pointer to the variable-length array field auth_key of
 * 'inp'.
 */
uint8_t * trn_cell_introduce1_getarray_auth_key(trn_cell_introduce1_t *inp);
/** As trn_cell_introduce1_get_auth_key, but take and return a const
 * pointer
 */
const uint8_t  * trn_cell_introduce1_getconstarray_auth_key(const trn_cell_introduce1_t *inp);
/** Change the length of the variable-length array field auth_key of
 * 'inp' to 'newlen'.Fill extra elements with 0. Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce1_setlen_auth_key(trn_cell_introduce1_t *inp, size_t newlen);
/** Return the value of the extensions field of the
 * trn_cell_introduce1_t in 'inp'
 */
struct trn_cell_extension_st * trn_cell_introduce1_get_extensions(trn_cell_introduce1_t *inp);
/** As trn_cell_introduce1_get_extensions, but take and return a const
 * pointer
 */
const struct trn_cell_extension_st * trn_cell_introduce1_getconst_extensions(const trn_cell_introduce1_t *inp);
/** Set the value of the extensions field of the trn_cell_introduce1_t
 * in 'inp' to 'val'. Free the old value if any. Steals the
 * referenceto 'val'.Return 0 on success; return -1 and set the error
 * code on 'inp' on failure.
 */
int trn_cell_introduce1_set_extensions(trn_cell_introduce1_t *inp, struct trn_cell_extension_st *val);
/** As trn_cell_introduce1_set_extensions, but does not free the
 * previous value.
 */
int trn_cell_introduce1_set0_extensions(trn_cell_introduce1_t *inp, struct trn_cell_extension_st *val);
/** Return the length of the dynamic array holding the encrypted field
 * of the trn_cell_introduce1_t in 'inp'.
 */
size_t trn_cell_introduce1_getlen_encrypted(const trn_cell_introduce1_t *inp);
/** Return the element at position 'idx' of the dynamic array field
 * encrypted of the trn_cell_introduce1_t in 'inp'.
 */
uint8_t trn_cell_introduce1_get_encrypted(trn_cell_introduce1_t *inp, size_t idx);
/** As trn_cell_introduce1_get_encrypted, but take and return a const
 * pointer
 */
uint8_t trn_cell_introduce1_getconst_encrypted(const trn_cell_introduce1_t *inp, size_t idx);
/** Change the element at position 'idx' of the dynamic array field
 * encrypted of the trn_cell_introduce1_t in 'inp', so that it will
 * hold the value 'elt'.
 */
int trn_cell_introduce1_set_encrypted(trn_cell_introduce1_t *inp, size_t idx, uint8_t elt);
/** Append a new element 'elt' to the dynamic array field encrypted of
 * the trn_cell_introduce1_t in 'inp'.
 */
int trn_cell_introduce1_add_encrypted(trn_cell_introduce1_t *inp, uint8_t elt);
/** Return a pointer to the variable-length array field encrypted of
 * 'inp'.
 */
uint8_t * trn_cell_introduce1_getarray_encrypted(trn_cell_introduce1_t *inp);
/** As trn_cell_introduce1_get_encrypted, but take and return a const
 * pointer
 */
const uint8_t  * trn_cell_introduce1_getconstarray_encrypted(const trn_cell_introduce1_t *inp);
/** Change the length of the variable-length array field encrypted of
 * 'inp' to 'newlen'.Fill extra elements with 0. Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce1_setlen_encrypted(trn_cell_introduce1_t *inp, size_t newlen);
/** Return a newly allocated trn_cell_introduce_ack with all elements
 * set to zero.
 */
trn_cell_introduce_ack_t *trn_cell_introduce_ack_new(void);
/** Release all storage held by the trn_cell_introduce_ack in
 * 'victim'. (Do nothing if 'victim' is NULL.)
 */
void trn_cell_introduce_ack_free(trn_cell_introduce_ack_t *victim);
/** Try to parse a trn_cell_introduce_ack from the buffer in 'input',
 * using up to 'len_in' bytes from the input buffer. On success,
 * return the number of bytes consumed and set *output to the newly
 * allocated trn_cell_introduce_ack_t. On failure, return -2 if the
 * input appears truncated, and -1 if the input is otherwise invalid.
 */
ssize_t trn_cell_introduce_ack_parse(trn_cell_introduce_ack_t **output, const uint8_t *input, const size_t len_in);
/** Return the number of bytes we expect to need to encode the
 * trn_cell_introduce_ack in 'obj'. On failure, return a negative
 * value. Note that this value may be an overestimate, and can even be
 * an underestimate for certain unencodeable objects.
 */
ssize_t trn_cell_introduce_ack_encoded_len(const trn_cell_introduce_ack_t *obj);
/** Try to encode the trn_cell_introduce_ack from 'input' into the
 * buffer at 'output', using up to 'avail' bytes of the output buffer.
 * On success, return the number of bytes used. On failure, return -2
 * if the buffer was not long enough, and -1 if the input was invalid.
 */
ssize_t trn_cell_introduce_ack_encode(uint8_t *output, size_t avail, const trn_cell_introduce_ack_t *input);
/** Check whether the internal state of the trn_cell_introduce_ack in
 * 'obj' is consistent. Return NULL if it is, and a short message if
 * it is not.
 */
const char *trn_cell_introduce_ack_check(const trn_cell_introduce_ack_t *obj);
/** Clear any errors that were set on the object 'obj' by its setter
 * functions. Return true iff errors were cleared.
 */
int trn_cell_introduce_ack_clear_errors(trn_cell_introduce_ack_t *obj);
/** Return the value of the status field of the
 * trn_cell_introduce_ack_t in 'inp'
 */
uint16_t trn_cell_introduce_ack_get_status(const trn_cell_introduce_ack_t *inp);
/** Set the value of the status field of the trn_cell_introduce_ack_t
 * in 'inp' to 'val'. Return 0 on success; return -1 and set the error
 * code on 'inp' on failure.
 */
int trn_cell_introduce_ack_set_status(trn_cell_introduce_ack_t *inp, uint16_t val);
/** Return the value of the extensions field of the
 * trn_cell_introduce_ack_t in 'inp'
 */
struct trn_cell_extension_st * trn_cell_introduce_ack_get_extensions(trn_cell_introduce_ack_t *inp);
/** As trn_cell_introduce_ack_get_extensions, but take and return a
 * const pointer
 */
const struct trn_cell_extension_st * trn_cell_introduce_ack_getconst_extensions(const trn_cell_introduce_ack_t *inp);
/** Set the value of the extensions field of the
 * trn_cell_introduce_ack_t in 'inp' to 'val'. Free the old value if
 * any. Steals the referenceto 'val'.Return 0 on success; return -1
 * and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_ack_set_extensions(trn_cell_introduce_ack_t *inp, struct trn_cell_extension_st *val);
/** As trn_cell_introduce_ack_set_extensions, but does not free the
 * previous value.
 */
int trn_cell_introduce_ack_set0_extensions(trn_cell_introduce_ack_t *inp, struct trn_cell_extension_st *val);
/** Return a newly allocated trn_cell_introduce_encrypted with all
 * elements set to zero.
 */
trn_cell_introduce_encrypted_t *trn_cell_introduce_encrypted_new(void);
/** Release all storage held by the trn_cell_introduce_encrypted in
 * 'victim'. (Do nothing if 'victim' is NULL.)
 */
void trn_cell_introduce_encrypted_free(trn_cell_introduce_encrypted_t *victim);
/** Try to parse a trn_cell_introduce_encrypted from the buffer in
 * 'input', using up to 'len_in' bytes from the input buffer. On
 * success, return the number of bytes consumed and set *output to the
 * newly allocated trn_cell_introduce_encrypted_t. On failure, return
 * -2 if the input appears truncated, and -1 if the input is otherwise
 * invalid.
 */
ssize_t trn_cell_introduce_encrypted_parse(trn_cell_introduce_encrypted_t **output, const uint8_t *input, const size_t len_in);
/** Return the number of bytes we expect to need to encode the
 * trn_cell_introduce_encrypted in 'obj'. On failure, return a
 * negative value. Note that this value may be an overestimate, and
 * can even be an underestimate for certain unencodeable objects.
 */
ssize_t trn_cell_introduce_encrypted_encoded_len(const trn_cell_introduce_encrypted_t *obj);
/** Try to encode the trn_cell_introduce_encrypted from 'input' into
 * the buffer at 'output', using up to 'avail' bytes of the output
 * buffer. On success, return the number of bytes used. On failure,
 * return -2 if the buffer was not long enough, and -1 if the input
 * was invalid.
 */
ssize_t trn_cell_introduce_encrypted_encode(uint8_t *output, size_t avail, const trn_cell_introduce_encrypted_t *input);
/** Check whether the internal state of the
 * trn_cell_introduce_encrypted in 'obj' is consistent. Return NULL if
 * it is, and a short message if it is not.
 */
const char *trn_cell_introduce_encrypted_check(const trn_cell_introduce_encrypted_t *obj);
/** Clear any errors that were set on the object 'obj' by its setter
 * functions. Return true iff errors were cleared.
 */
int trn_cell_introduce_encrypted_clear_errors(trn_cell_introduce_encrypted_t *obj);
/** Return the (constant) length of the array holding the rend_cookie
 * field of the trn_cell_introduce_encrypted_t in 'inp'.
 */
size_t trn_cell_introduce_encrypted_getlen_rend_cookie(const trn_cell_introduce_encrypted_t *inp);
/** Return the element at position 'idx' of the fixed array field
 * rend_cookie of the trn_cell_introduce_encrypted_t in 'inp'.
 */
uint8_t trn_cell_introduce_encrypted_get_rend_cookie(trn_cell_introduce_encrypted_t *inp, size_t idx);
/** As trn_cell_introduce_encrypted_get_rend_cookie, but take and
 * return a const pointer
 */
uint8_t trn_cell_introduce_encrypted_getconst_rend_cookie(const trn_cell_introduce_encrypted_t *inp, size_t idx);
/** Change the element at position 'idx' of the fixed array field
 * rend_cookie of the trn_cell_introduce_encrypted_t in 'inp', so that
 * it will hold the value 'elt'.
 */
int trn_cell_introduce_encrypted_set_rend_cookie(trn_cell_introduce_encrypted_t *inp, size_t idx, uint8_t elt);
/** Return a pointer to the TRUNNEL_REND_COOKIE_LEN-element array
 * field rend_cookie of 'inp'.
 */
uint8_t * trn_cell_introduce_encrypted_getarray_rend_cookie(trn_cell_introduce_encrypted_t *inp);
/** As trn_cell_introduce_encrypted_get_rend_cookie, but take and
 * return a const pointer
 */
const uint8_t  * trn_cell_introduce_encrypted_getconstarray_rend_cookie(const trn_cell_introduce_encrypted_t *inp);
/** Return the value of the extensions field of the
 * trn_cell_introduce_encrypted_t in 'inp'
 */
struct trn_cell_extension_st * trn_cell_introduce_encrypted_get_extensions(trn_cell_introduce_encrypted_t *inp);
/** As trn_cell_introduce_encrypted_get_extensions, but take and
 * return a const pointer
 */
const struct trn_cell_extension_st * trn_cell_introduce_encrypted_getconst_extensions(const trn_cell_introduce_encrypted_t *inp);
/** Set the value of the extensions field of the
 * trn_cell_introduce_encrypted_t in 'inp' to 'val'. Free the old
 * value if any. Steals the referenceto 'val'.Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_set_extensions(trn_cell_introduce_encrypted_t *inp, struct trn_cell_extension_st *val);
/** As trn_cell_introduce_encrypted_set_extensions, but does not free
 * the previous value.
 */
int trn_cell_introduce_encrypted_set0_extensions(trn_cell_introduce_encrypted_t *inp, struct trn_cell_extension_st *val);
/** Return the value of the onion_key_type field of the
 * trn_cell_introduce_encrypted_t in 'inp'
 */
uint8_t trn_cell_introduce_encrypted_get_onion_key_type(const trn_cell_introduce_encrypted_t *inp);
/** Set the value of the onion_key_type field of the
 * trn_cell_introduce_encrypted_t in 'inp' to 'val'. Return 0 on
 * success; return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_set_onion_key_type(trn_cell_introduce_encrypted_t *inp, uint8_t val);
/** Return the value of the onion_key_len field of the
 * trn_cell_introduce_encrypted_t in 'inp'
 */
uint16_t trn_cell_introduce_encrypted_get_onion_key_len(const trn_cell_introduce_encrypted_t *inp);
/** Set the value of the onion_key_len field of the
 * trn_cell_introduce_encrypted_t in 'inp' to 'val'. Return 0 on
 * success; return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_set_onion_key_len(trn_cell_introduce_encrypted_t *inp, uint16_t val);
/** Return the length of the dynamic array holding the onion_key field
 * of the trn_cell_introduce_encrypted_t in 'inp'.
 */
size_t trn_cell_introduce_encrypted_getlen_onion_key(const trn_cell_introduce_encrypted_t *inp);
/** Return the element at position 'idx' of the dynamic array field
 * onion_key of the trn_cell_introduce_encrypted_t in 'inp'.
 */
uint8_t trn_cell_introduce_encrypted_get_onion_key(trn_cell_introduce_encrypted_t *inp, size_t idx);
/** As trn_cell_introduce_encrypted_get_onion_key, but take and return
 * a const pointer
 */
uint8_t trn_cell_introduce_encrypted_getconst_onion_key(const trn_cell_introduce_encrypted_t *inp, size_t idx);
/** Change the element at position 'idx' of the dynamic array field
 * onion_key of the trn_cell_introduce_encrypted_t in 'inp', so that
 * it will hold the value 'elt'.
 */
int trn_cell_introduce_encrypted_set_onion_key(trn_cell_introduce_encrypted_t *inp, size_t idx, uint8_t elt);
/** Append a new element 'elt' to the dynamic array field onion_key of
 * the trn_cell_introduce_encrypted_t in 'inp'.
 */
int trn_cell_introduce_encrypted_add_onion_key(trn_cell_introduce_encrypted_t *inp, uint8_t elt);
/** Return a pointer to the variable-length array field onion_key of
 * 'inp'.
 */
uint8_t * trn_cell_introduce_encrypted_getarray_onion_key(trn_cell_introduce_encrypted_t *inp);
/** As trn_cell_introduce_encrypted_get_onion_key, but take and return
 * a const pointer
 */
const uint8_t  * trn_cell_introduce_encrypted_getconstarray_onion_key(const trn_cell_introduce_encrypted_t *inp);
/** Change the length of the variable-length array field onion_key of
 * 'inp' to 'newlen'.Fill extra elements with 0. Return 0 on success;
 * return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_setlen_onion_key(trn_cell_introduce_encrypted_t *inp, size_t newlen);
/** Return the value of the nspec field of the
 * trn_cell_introduce_encrypted_t in 'inp'
 */
uint8_t trn_cell_introduce_encrypted_get_nspec(const trn_cell_introduce_encrypted_t *inp);
/** Set the value of the nspec field of the
 * trn_cell_introduce_encrypted_t in 'inp' to 'val'. Return 0 on
 * success; return -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_set_nspec(trn_cell_introduce_encrypted_t *inp, uint8_t val);
/** Return the length of the dynamic array holding the nspecs field of
 * the trn_cell_introduce_encrypted_t in 'inp'.
 */
size_t trn_cell_introduce_encrypted_getlen_nspecs(const trn_cell_introduce_encrypted_t *inp);
/** Return the element at position 'idx' of the dynamic array field
 * nspecs of the trn_cell_introduce_encrypted_t in 'inp'.
 */
struct link_specifier_st * trn_cell_introduce_encrypted_get_nspecs(trn_cell_introduce_encrypted_t *inp, size_t idx);
/** As trn_cell_introduce_encrypted_get_nspecs, but take and return a
 * const pointer
 */
 const struct link_specifier_st * trn_cell_introduce_encrypted_getconst_nspecs(const trn_cell_introduce_encrypted_t *inp, size_t idx);
/** Change the element at position 'idx' of the dynamic array field
 * nspecs of the trn_cell_introduce_encrypted_t in 'inp', so that it
 * will hold the value 'elt'. Free the previous value, if any.
 */
int trn_cell_introduce_encrypted_set_nspecs(trn_cell_introduce_encrypted_t *inp, size_t idx, struct link_specifier_st * elt);
/** As trn_cell_introduce_encrypted_set_nspecs, but does not free the
 * previous value.
 */
int trn_cell_introduce_encrypted_set0_nspecs(trn_cell_introduce_encrypted_t *inp, size_t idx, struct link_specifier_st * elt);
/** Append a new element 'elt' to the dynamic array field nspecs of
 * the trn_cell_introduce_encrypted_t in 'inp'.
 */
int trn_cell_introduce_encrypted_add_nspecs(trn_cell_introduce_encrypted_t *inp, struct link_specifier_st * elt);
/** Return a pointer to the variable-length array field nspecs of
 * 'inp'.
 */
struct link_specifier_st * * trn_cell_introduce_encrypted_getarray_nspecs(trn_cell_introduce_encrypted_t *inp);
/** As trn_cell_introduce_encrypted_get_nspecs, but take and return a
 * const pointer
 */
const struct link_specifier_st *  const  * trn_cell_introduce_encrypted_getconstarray_nspecs(const trn_cell_introduce_encrypted_t *inp);
/** Change the length of the variable-length array field nspecs of
 * 'inp' to 'newlen'.Fill extra elements with NULL; free removed
 * elements. Return 0 on success; return -1 and set the error code on
 * 'inp' on failure.
 */
int trn_cell_introduce_encrypted_setlen_nspecs(trn_cell_introduce_encrypted_t *inp, size_t newlen);
/** Return the length of the dynamic array holding the pad field of
 * the trn_cell_introduce_encrypted_t in 'inp'.
 */
size_t trn_cell_introduce_encrypted_getlen_pad(const trn_cell_introduce_encrypted_t *inp);
/** Return the element at position 'idx' of the dynamic array field
 * pad of the trn_cell_introduce_encrypted_t in 'inp'.
 */
uint8_t trn_cell_introduce_encrypted_get_pad(trn_cell_introduce_encrypted_t *inp, size_t idx);
/** As trn_cell_introduce_encrypted_get_pad, but take and return a
 * const pointer
 */
uint8_t trn_cell_introduce_encrypted_getconst_pad(const trn_cell_introduce_encrypted_t *inp, size_t idx);
/** Change the element at position 'idx' of the dynamic array field
 * pad of the trn_cell_introduce_encrypted_t in 'inp', so that it will
 * hold the value 'elt'.
 */
int trn_cell_introduce_encrypted_set_pad(trn_cell_introduce_encrypted_t *inp, size_t idx, uint8_t elt);
/** Append a new element 'elt' to the dynamic array field pad of the
 * trn_cell_introduce_encrypted_t in 'inp'.
 */
int trn_cell_introduce_encrypted_add_pad(trn_cell_introduce_encrypted_t *inp, uint8_t elt);
/** Return a pointer to the variable-length array field pad of 'inp'.
 */
uint8_t * trn_cell_introduce_encrypted_getarray_pad(trn_cell_introduce_encrypted_t *inp);
/** As trn_cell_introduce_encrypted_get_pad, but take and return a
 * const pointer
 */
const uint8_t  * trn_cell_introduce_encrypted_getconstarray_pad(const trn_cell_introduce_encrypted_t *inp);
/** Change the length of the variable-length array field pad of 'inp'
 * to 'newlen'.Fill extra elements with 0. Return 0 on success; return
 * -1 and set the error code on 'inp' on failure.
 */
int trn_cell_introduce_encrypted_setlen_pad(trn_cell_introduce_encrypted_t *inp, size_t newlen);


#endif

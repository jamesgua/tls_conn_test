/*
 * COPYRIGHT (c) International Business Machines Corp. 2005-2017
 *
 * This program is provided under the terms of the Common Public License,
 * version 1.0 (CPL-1.0). Any use, reproduction or distribution for this
 * software constitutes recipient's acceptance of CPL-1.0 terms which can be
 * found in the file LICENSE file or at
 * https://opensource.org/licenses/cpl1.0.php
 */

/*----------------------------------------------------------------------
 *  IBM Research & Development
 *  Author: Urban, Volker (volker.urban@de.ibm.com)
 *----------------------------------------------------------------------*/

#include "ep11grpc.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "pkcs11types.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <dlfcn.h>

#ifndef CKR_OK
#define CKR_OK 0x00000000
#endif

// SHA224 etc. are additions to PKCS#11 2.20
// remove these when host migrates beyond 2.20
//
#if !defined(CKM_SHA224)
#define  CKM_SHA224                 0x00000255
#define  CKM_SHA224_HMAC            0x00000256
#define  CKM_SHA224_HMAC_GENERAL    0x00000257
#define  CKM_SHA224_RSA_PKCS        0x00000046
#define  CKM_SHA224_RSA_PKCS_PSS    0x00000047
#define  CKM_SHA224_KEY_DERIVATION  0x00000396
#define  CKM_AES_CTR                0x00001086
#define  CKG_MGF1_SHA224            0x00000005
#endif

#if !defined(CKM_AES_CMAC)
#define  CKM_AES_CMAC               0x0000108a
#endif

#if !defined(CKM_ALG_DES3_CMAC)
#define  CKM_DES3_CMAC              0x00000138
#endif

static void* libep11 = NULL;
static CK_MECHANISM_INFO infoArray[0x10000];

void getMechanismInfo(int index);
/*----------------------------------------------------------------------
 *  CK_... type arguments correspond to the original PKCS#11 call's
 *  arguments.  Standard types mean PKCS#11 objects (session, token etc.)
 *  are mapped to a native type (key blob, mechanism) etc.
 *
 *  As an example, for _Encrypt and _Decrypt, a session is passed to
 *  the PKCS#11 function.  This session needs to be matched to a key blob,
 *  so our _Encrypt interface takes a key/keylen buffer instead of the
 *  session.  All other parameters should be passed through unchanged.
 *
 *  For certain operations, such as _GenerateKey, there are no real
 *  PKCS#11 type parameters at this level.
 */
CK_RV m_GenerateRandom   (CK_BYTE_PTR rnd, CK_ULONG len,     uint64_t target) {

    int res = 0;
    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

    return res;
}
/**/
/* note: external seeding not supported */
CK_RV m_SeedRandom (CK_BYTE_PTR pSeed,   CK_ULONG ulSeedLen,
                       uint64_t target) {

                                            int res = 0;
                                            printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                            return res;
                                        }
CK_RV m_DigestInit     (unsigned char *state,     size_t *len,
               const CK_MECHANISM_PTR pmech,
                             uint64_t target) {

                                                  int res = 0;
                                                  printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                  return res;
                                              }
/**/
CK_RV m_Digest (const unsigned char *state,       size_t slen,
                        CK_BYTE_PTR data,       CK_ULONG len,
                        CK_BYTE_PTR digest, CK_ULONG_PTR dglen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_DigestUpdate (unsigned char *state,       size_t slen,
                        CK_BYTE_PTR data,       CK_ULONG dlen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_DigestKey    (unsigned char *state,       size_t slen,
                const unsigned char *key,         size_t klen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_DigestFinal  (const unsigned char *state,       size_t slen,
                              CK_BYTE_PTR digest, CK_ULONG_PTR dlen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
CK_RV m_DigestSingle (CK_MECHANISM_PTR pmech,
                           CK_BYTE_PTR data,       CK_ULONG len,
                           CK_BYTE_PTR digest, CK_ULONG_PTR dlen,
                              uint64_t target) {

                                                   int res = 0;
                                                   printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                   return res;
                                               }

CK_RV m_EncryptInit        (unsigned char *state, size_t *slen,
                         CK_MECHANISM_PTR pmech,
                      const unsigned char *key,   size_t klen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
CK_RV m_DecryptInit        (unsigned char *state, size_t *slen,
                         CK_MECHANISM_PTR pmech,
                      const unsigned char *key,   size_t klen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
/**/
CK_RV m_EncryptUpdate      (unsigned char *state,       size_t slen,
                              CK_BYTE_PTR plain,      CK_ULONG plen,
                              CK_BYTE_PTR cipher, CK_ULONG_PTR clen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
CK_RV m_DecryptUpdate      (unsigned char *state,       size_t slen,
                              CK_BYTE_PTR cipher,     CK_ULONG clen,
                              CK_BYTE_PTR plain,  CK_ULONG_PTR plen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
/**/
/* one-pass en/decrypt with key blob */
CK_RV m_Encrypt       (const unsigned char *state,       size_t slen,
                               CK_BYTE_PTR plain,      CK_ULONG plen,
                               CK_BYTE_PTR cipher, CK_ULONG_PTR clen,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
CK_RV m_Decrypt       (const unsigned char *state,       size_t slen,
                               CK_BYTE_PTR cipher,     CK_ULONG clen,
                               CK_BYTE_PTR plain,  CK_ULONG_PTR plen,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
/**/
CK_RV m_EncryptFinal  (const unsigned char *state,       size_t slen,
                               CK_BYTE_PTR output, CK_ULONG_PTR len,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
CK_RV m_DecryptFinal  (const unsigned char *state,       size_t slen,
                               CK_BYTE_PTR output, CK_ULONG_PTR len,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
/**/
/* en/decrypt directly with key blob */
CK_RV m_EncryptSingle (const unsigned char *key,         size_t klen,
                          CK_MECHANISM_PTR mech,
                               CK_BYTE_PTR plain,      CK_ULONG plen,
                               CK_BYTE_PTR cipher, CK_ULONG_PTR clen,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
CK_RV m_DecryptSingle (const unsigned char *key,         size_t klen,
                          CK_MECHANISM_PTR mech,
                               CK_BYTE_PTR cipher,     CK_ULONG clen,
                               CK_BYTE_PTR plain,  CK_ULONG_PTR plen,
                                  uint64_t target) {

                                                       int res = 0;
                                                       printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                       return res;
                                                   }
/**/
/* de+encrypt in one pass, without exposing cleartext */
CK_RV m_ReencryptSingle (const unsigned char *dkey,     size_t dklen,
                         const unsigned char *ekey,     size_t eklen,
                         CK_MECHANISM_PTR pdecrmech,
                         CK_MECHANISM_PTR pencrmech,
                              CK_BYTE_PTR in,       CK_ULONG ilen,
                              CK_BYTE_PTR out,  CK_ULONG_PTR olen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }

CK_RV m_GenerateKey (CK_MECHANISM_PTR pmech,
                     CK_ATTRIBUTE_PTR ptempl, CK_ULONG templcount,
                  const unsigned char *pin,     size_t pinlen,
                        unsigned char *key,     size_t *klen,
                        unsigned char *csum,    size_t *clen,
                             uint64_t target) {
    int res = 0;
//    typedef CK_RV (*fptr)_GenerateKey*(CK_MECHANISM_PTR pmech,
//                                                     CK_ATTRIBUTE_PTR ptempl, CK_ULONG templcount,
//                                                  const unsigned char *pin,     size_t pinlen,
//                                                        unsigned char *key,     size_t *klen,
//                                                        unsigned char *csum,    size_t *clen,
//                                                             uint64_t target);
//    fptr myfunc;
//    myfunc = dlsym(libep11, "m_GenerateKey");
//    if(myfunc)
        printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
//        res = myfunc->(pmech, ptempl, templcount, pin, pinlen, key, klen, csum, clen, target);
//    else
//        printf("dlsym error: %s", dlerror());
    return res;
}
/**/
CK_RV m_GenerateKeyPair (CK_MECHANISM_PTR pmech,
			 CK_ATTRIBUTE_PTR ppublic,  CK_ULONG pubattrs,
                         CK_ATTRIBUTE_PTR pprivate, CK_ULONG prvattrs,
                      const unsigned char *pin,       size_t pinlen,
                            unsigned char *key,       size_t *klen,
                            unsigned char *pubkey,    size_t *pklen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }

CK_RV m_SignInit     (unsigned char *state,     size_t *slen,
                   CK_MECHANISM_PTR alg,
                const unsigned char *key,       size_t klen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_VerifyInit   (unsigned char *state,     size_t *slen,
                   CK_MECHANISM_PTR alg,
                const unsigned char *key,       size_t klen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
/**/
CK_RV m_SignUpdate   (unsigned char *state,     size_t slen,
                        CK_BYTE_PTR data,     CK_ULONG dlen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_VerifyUpdate (unsigned char *state,     size_t slen,
                        CK_BYTE_PTR data,     CK_ULONG dlen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
/**/
CK_RV m_SignFinal    (const unsigned char *state,      size_t stlen,
                              CK_BYTE_PTR sig,   CK_ULONG_PTR siglen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
CK_RV m_VerifyFinal  (const unsigned char *state,      size_t stlen,
                              CK_BYTE_PTR sig,       CK_ULONG siglen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
/**/
CK_RV m_Sign   (const unsigned char *state,     size_t stlen,
                        CK_BYTE_PTR data,     CK_ULONG dlen,
                        CK_BYTE_PTR sig,  CK_ULONG_PTR siglen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
CK_RV m_Verify (const unsigned char *state,     size_t stlen,
                        CK_BYTE_PTR data,     CK_ULONG dlen,
                        CK_BYTE_PTR sig,      CK_ULONG siglen,
                           uint64_t target) {

                                                int res = 0;
                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                return res;
                                            }
/**/
CK_RV m_SignSingle   (const unsigned char *key,      size_t klen,
                         CK_MECHANISM_PTR pmech,
                              CK_BYTE_PTR data,    CK_ULONG dlen,
                              CK_BYTE_PTR sig, CK_ULONG_PTR slen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }
CK_RV m_VerifySingle (const unsigned char *key,      size_t klen,
                         CK_MECHANISM_PTR pmech,
                              CK_BYTE_PTR data,    CK_ULONG dlen,
                              CK_BYTE_PTR sig,     CK_ULONG slen,
                                 uint64_t target) {

                                                      int res = 0;
                                                      printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                      return res;
                                                  }

/* mackey is NULL for PKCS#11 formats, not for authenticated ones */
CK_RV m_WrapKey (const unsigned char *key,          size_t keylen,
                 const unsigned char *kek,          size_t keklen,
                 const unsigned char *mackey,       size_t mklen,
              const CK_MECHANISM_PTR pmech,
                         CK_BYTE_PTR wrapped, CK_ULONG_PTR wlen,
                            uint64_t target) {

                                                 int res = 0;
                                                 printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                 return res;
                                             }
/**/
/* mackey is NULL for PKCS#11 formats, not for authenticated ones */
CK_RV m_UnwrapKey (const   CK_BYTE_PTR wrapped,  CK_ULONG wlen,
                   const unsigned char *kek,       size_t keklen,
                   const unsigned char *mackey,    size_t mklen,
                   const unsigned char *pin,       size_t pinlen,
                const CK_MECHANISM_PTR uwmech,
                const CK_ATTRIBUTE_PTR ptempl,   CK_ULONG pcount,
                         unsigned char *unwrapped, size_t *uwlen,
                           CK_BYTE_PTR csum,     CK_ULONG *cslen,
                              uint64_t target) {

                                                   int res = 0;
                                                   printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                   return res;
                                               }

CK_RV m_DeriveKey ( CK_MECHANISM_PTR pderivemech,
                    CK_ATTRIBUTE_PTR ptempl, CK_ULONG templcount,
                 const unsigned char *basekey, size_t bklen,
                 const unsigned char *data,    size_t dlen,
                 const unsigned char *pin,     size_t pinlen,
                       unsigned char *newkey,  size_t *nklen,
                       unsigned char *csum,    size_t *cslen,
                       uint64_t target) {

                                            int res = 0;
                                            printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                            return res;
                                        }

/**/
CK_RV m_GetMechanismList (CK_SLOT_ID slot,
               CK_MECHANISM_TYPE_PTR mechs,
                        CK_ULONG_PTR count,
                            uint64_t target) {

                                                 int res = 0;
                                                 printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                 return res;
                                             }

//typedef struct CK_MECHANISM_INFO {
//     CK_ULONG    ulMinKeySize;
//     CK_ULONG    ulMaxKeySize;
//     CK_FLAGS    flags;
//} CK_MECHANISM_INFO;
CK_RV m_GetMechanismInfo (CK_SLOT_ID slot,
                   CK_MECHANISM_TYPE mech,
               CK_MECHANISM_INFO_PTR pmechinfo,
                            uint64_t target) {
    int res = 0;
    printf("%s %d %s: mech %lx\n", __FILE__, __LINE__, __FUNCTION__, mech);
    getMechanismInfo(mech);
    switch (mech) {
    case 0x80010008:
    case 0x80010009:
    case 0x800a000a:
    case 0x8001000b:
    pmechinfo->ulMinKeySize = 192; pmechinfo->ulMaxKeySize = 521; pmechinfo->flags = 0x1902800;
    break;
    case 0x80010012:
    case 0x80010013:
    pmechinfo->ulMinKeySize = 0; pmechinfo->ulMaxKeySize = 0; pmechinfo->flags = 0x400;
    break;
    case 0x80010014:
    pmechinfo->ulMinKeySize = 16; pmechinfo->ulMaxKeySize = 256; pmechinfo->flags = 0x2800;
    break;
    case 0x80010015:
    pmechinfo->ulMinKeySize = 14; pmechinfo->ulMaxKeySize = 256; pmechinfo->flags = 0x2800;
    break;
    default:
    pmechinfo->ulMinKeySize = 0; pmechinfo->ulMaxKeySize = 0; pmechinfo->flags = 0;
    break;
    }
    if(mech < 0x10000)
        memcpy(pmechinfo, (CK_MECHANISM_INFO_PTR) (&infoArray[mech]), sizeof(CK_MECHANISM_INFO));
    printf("%lu-%lu, flag %lx\n", pmechinfo->ulMinKeySize, pmechinfo->ulMaxKeySize, pmechinfo->flags);
    return res;
}

CK_RV m_GetAttributeValue (const unsigned char *obj,        size_t olen,
                              CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
                                      uint64_t target) {

                                                           int res = 0;
                                                           printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                           return res;
                                                       }
CK_RV m_SetAttributeValue       (unsigned char *obj,        size_t olen,
                              CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
                                      uint64_t target) {

                                                           int res = 0;
                                                           printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                           return res;
                                                       }


CK_RV m_Login ( CK_UTF8CHAR_PTR pin,      CK_ULONG pinlen,
            const unsigned char *nonce,     size_t nlen,
                  unsigned char *pinblob,   size_t *pinbloblen,
                       uint64_t target) {

                                            int res = 0;
                                            printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                            return res;
                                        }
CK_RV m_Logout ( const unsigned char *pin, size_t len,     uint64_t target) {

                                                                                int res = 0;
                                                                                printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                                                return res;
                                                                            }

CK_RV m_admin (unsigned char *response1, size_t *r1len,
               unsigned char *response2, size_t *r2len,
         const unsigned char *cmd,       size_t clen,
         const unsigned char *sigs,      size_t slen,
                         uint64_t target) {

                                              int res = 0;
                                              printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                              return res;
                                          }
CK_RV m_get_ep11_info () {

    int res = 0;
    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

    return res;
}
CK_RV m_get_xcp_info () {

    int res = 0;
    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

    return res;
}

/*--------------------------------------------------------------------------
 *  Module management.
 */
int m_add_backend(const char *name, unsigned int port) {

                                                           int res = 0;
                                                           printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

                                                           return res;
                                                       }
int m_init     (void) {
    int res = 0;
//    if(!libep11) {
//        dlerror();
//        libep11 = dlopen("libep11.so", RTLD_NOW);
//    }
//    if(libep11)
        printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
//    else
//        printf("ERROR: fail to open libep11.so: %s", dlerror());
    return res;
}
int m_shutdown (void) {
    int res = 0;
//    if(libep11) {
//        dlclose(libep11);
        printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
//    }
//    libep11 = NULL;
    return res;
}

//CK_RV ep11tok_get_mechanism_list(STDLL_TokData_t *tokdata,
//                                 CK_MECHANISM_TYPE_PTR mlist,
//                                 CK_ULONG_PTR count) {
//
//    int res = 0;
//    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
//
//    return res;
//                                                                           }
//CK_RV ep11tok_get_mechanism_info(STDLL_TokData_t *tokdata,
//                                 CK_MECHANISM_TYPE type,
//                                 CK_MECHANISM_INFO_PTR pInfo) {
//
//    int res = 0;
//    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
//
//    return res;
//}

void getMechanismInfo(int index) {
    switch (index) {
    case 0:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x10000;
    break;
    case 1:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x62b00;
    break;
    case 6:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x2800;
    break;
    case 0xa:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x10000;
    break;
    case 0x10:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 3072; infoArray[index].flags = 0x10000;
    break;
    case 0x11:
    case 0x12:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 3072; infoArray[index].flags = 0x2800;
    break;
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x2800;
    break;
    case 0x20:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 3072; infoArray[index].flags = 0x10000;
    break;
    case 0x21:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 3072; infoArray[index].flags = 0x80000;
    break;
    case 0x40:
    case 0x41:
    case 0x42:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 4096; infoArray[index].flags = 0x2800;
    break;
    case 0x130:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 16; infoArray[index].flags = 0x8000;
    break;
    case 0x131:
    infoArray[index].ulMinKeySize = 24; infoArray[index].ulMaxKeySize = 24; infoArray[index].flags = 0x8000;
    break;
    case 0x132:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 24; infoArray[index].flags = 0x300;
    break;
    case 0x133:
    case 0x136:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 24; infoArray[index].flags = 0x62b00;
    break;
    case 0x220:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x221:
    infoArray[index].ulMinKeySize = 10; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x250:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x251:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x260:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x261:
    infoArray[index].ulMinKeySize = 24; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x270:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x271:
    infoArray[index].ulMinKeySize = 32; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x2b0:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x2b1:
    infoArray[index].ulMinKeySize = 14; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x2c0:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x400;
    break;
    case 0x2c1:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 256; infoArray[index].flags = 0x2800;
    break;
    case 0x392:
    case 0x393:
    infoArray[index].ulMinKeySize = 0; infoArray[index].ulMaxKeySize = 0; infoArray[index].flags = 0x80000;
    break;
    case 0x3a8:
    infoArray[index].ulMinKeySize = 24; infoArray[index].ulMaxKeySize = 24; infoArray[index].flags = 0x8000;
    break;
    case 0x1040:
    infoArray[index].ulMinKeySize = 192; infoArray[index].ulMaxKeySize = 521; infoArray[index].flags = 0x1910000;
    break;
    case 0x1041:
    case 0x1042:
    case 0x1043:
    case 0x1044:
    case 0x1045:
    case 0x1046:
    infoArray[index].ulMinKeySize = 192; infoArray[index].ulMaxKeySize = 521; infoArray[index].flags = 0x1902800;
    break;
    case 0x1050:
    infoArray[index].ulMinKeySize = 192; infoArray[index].ulMaxKeySize = 521; infoArray[index].flags = 0x1180000;
    break;
    case 0x1080:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 32; infoArray[index].flags = 0x8000;
    break;
    case 0x1081:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 32; infoArray[index].flags = 0x300;
    break;
    case 0x1082:
    case 0x1085:
    infoArray[index].ulMinKeySize = 16; infoArray[index].ulMaxKeySize = 32; infoArray[index].flags = 0x60300;
    break;
    case 0x2000:
    case 0x2001:
    infoArray[index].ulMinKeySize = 1024; infoArray[index].ulMaxKeySize = 3072; infoArray[index].flags = 0x8000;
    break;
    default:
    printf("Dummy content at %d ???\n", index);
    break;
    }
    return;
}

#ifdef __cplusplus
} //extern "C" }
#endif

#include "ep11grpc.h"
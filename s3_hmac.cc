#include "s3_hmac.h"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <cstring>
#include <assert.h>
//g++ hmac_demo.cc -lssl  -lcrypto
#include <iostream>
#include <string>
#include "Base64.h"

extern "C" {
  const EVP_MD *EVP_md5(void);
  const EVP_MD *EVP_sha1(void);
  const EVP_MD *EVP_sha256(void);
  const EVP_MD *EVP_sha512(void);
}

/*
https://www.openssl.org/docs/man1.1.0/man3/HMAC.html
*/
HMAC::HMAC(const EVP_MD *type, const void* key, int len)
  : mCtx(HMAC_CTX_new()) {
  assert(type != nullptr && key != nullptr);
  assert(mCtx != nullptr);
  int r = HMAC_Init_ex(mCtx, key, len, type, nullptr);
  if(r != 1) {
    perror("Error: HMAC init failed");
  }
}

HMAC::~HMAC() {
  HMAC_CTX_free(mCtx);
}

void HMAC::Update(const void* data, size_t len) {
  assert(data != nullptr);
  if(len) {
    int r = HMAC_Update(mCtx, reinterpret_cast<const unsigned char*>(data), len);
    if(r != 1) {
      perror("Error: HMAC Update failed");
    }
  }
}

//unsigned int Final(unsigned char* result) {
unsigned int HMAC::Final(void* res) {
  unsigned char* result = reinterpret_cast<unsigned char*>(res);
  assert(result != nullptr);
  unsigned int len;
  int r = HMAC_Final(mCtx, result, &len);
  if(r != 1) {
      perror("Error: HMAC Final failed");
  }
  return len;
}

void HMAC::Restart() {
  int r = HMAC_Init_ex(mCtx, nullptr, 0, nullptr, nullptr);
  if(r != 1) {
    perror("Error: HMAC Restart failed");
  }
}

void HMAC::Reset(const void* key, int len) {
  assert(key != nullptr);
  int r = HMAC_Init_ex(mCtx, key, len, nullptr, nullptr);
  if(r != 1) {
    perror("Error: HMAC Reset failed");
  }
} 

HMAC_SHA256::HMAC_SHA256(const void* key, int len) 
  : HMAC(EVP_sha256(), key, len) {}

HMAC_SHA1::HMAC_SHA1(const void* key, int len) 
  : HMAC(EVP_sha1(), key, len) {}

// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TINK_SUBTLE_SUBTLE_UTIL_BORINGSSL_H_
#define TINK_SUBTLE_SUBTLE_UTIL_BORINGSSL_H_

#include "absl/strings/string_view.h"
#include "cc/subtle/common_enums.h"
#include "cc/util/status.h"
#include "cc/util/statusor.h"
#include "openssl/bn.h"
#include "openssl/evp.h"

namespace crypto {
namespace tink {
namespace subtle {

class SubtleUtilBoringSSL {
 public:
  struct EcKey {
    EllipticCurveType curve;
    std::string pub_x;   // affine coordinates in bigendian representation
    std::string pub_y;
    std::string priv;    // big integer in bigendian represnetation
  };

  // Returns BoringSSL's EC_GROUP constructed from the curve type.
  static crypto::tink::util::StatusOr<EC_GROUP *> GetEcGroup(
      EllipticCurveType curve_type);

  // Returns BoringSSL's EC_POINT constructed from the curve type, big-endian
  // representation of public key's x-coordinate and y-coordinate.
  static crypto::tink::util::StatusOr<EC_POINT *> GetEcPoint(
      EllipticCurveType curve,
      absl::string_view pubx,
      absl::string_view puby);

  // Returns a new EC key for the specified curve.
  static crypto::tink::util::StatusOr<EcKey> GetNewEcKey(
      EllipticCurveType curve_type);

  // Returns BoringSSL's EC_POINT constructed from curve type, point format and
  // encoded public key's point. The uncompressed point is encoded as
  // 0x04 || x || y where x, y are curve_size_in_bytes big-endian byte array.
  // The compressed point is encoded as 1-byte || x where x is
  // curve_size_in_bytes big-endian byte array and if the least significant bit
  // of y is 1, the 1st byte is 0x03, otherwise it's 0x02.
  static crypto::tink::util::StatusOr<EC_POINT *> EcPointDecode(
      EllipticCurveType curve,
      EcPointFormat format,
      absl::string_view encoded);

  // Returns the encoded public key based on curve type, point format and
  // BoringSSL's EC_POINT public key point. The uncompressed point is encoded as
  // 0x04 || x || y where x, y are curve_size_in_bytes big-endian byte array.
  // The compressed point is encoded as 1-byte || x where x is
  // curve_size_in_bytes big-endian byte array and if the least significant bit
  // of y is 1, the 1st byte is 0x03, otherwise it's 0x02.
  static crypto::tink::util::StatusOr<std::string> EcPointEncode(
      EllipticCurveType curve,
      EcPointFormat format,
      const EC_POINT *point);

  // Returns the ECDH's shared secret based on our private key and peer's public
  // key. Returns error if the public key is not on private key's curve.
  static crypto::tink::util::StatusOr<std::string> ComputeEcdhSharedSecret(
      EllipticCurveType curve,
      const BIGNUM *priv_key,
      const EC_POINT *pub_key);

  // Returns an EVP structure for a hash function.
  // The EVP_MD instances are sigletons owned by BoringSSL.
  static crypto::tink::util::StatusOr<const EVP_MD *> EvpHash(
      HashType hash_type);
};

}  // namespace subtle
}  // namespace tink
}  // namespace crypto

#endif  // TINK_SUBTLE_SUBTLE_UTIL_BORINGSSL_H_

// Copyright 2017 Google Inc.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//      http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////////////////////

/**
 * Interface for MACs (Message Authentication Codes).
 * This interface should be used for authentication only, and not for other purposes
 * (for example, it should not be used to generate pseudorandom bytes).
 */
package tink

type Mac interface {
  /**
  * Computes message authentication code (MAC) for {@code data}.
  *
  * @return MAC value.
  */
  ComputeMac(data []byte) ([]byte, error)

  /**
  * Verifies whether {@code mac} is a correct authentication code (MAC) for {@code data}.
  *
  * @return 0 if {@code mac} is correct; 1 otherwise.
  */
  VerifyMac(mac []byte, data []byte) (bool, error)
}

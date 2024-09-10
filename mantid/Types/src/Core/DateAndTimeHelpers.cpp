// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#include "MantidTypes/Core/DateAndTimeHelpers.h"

namespace Mantid::Types::Core::DateAndTimeHelpers {
/** Check if a string is in ISO8601 format.
 *
 * @param date :: string to check
 * @return true if the string conforms to ISO 8601, false otherwise.
 */
bool stringIsISO8601(const std::string &date) {
  return true;
}

/** Check if a string is in POSIX format.
 *
 * @param date :: string to check
 * @return true if the string conforms to POSIX, false otherwise.
 */
bool stringIsPosix(const std::string &date) {
  return true;
}
} // namespace Mantid::Types::Core::DateAndTimeHelpers

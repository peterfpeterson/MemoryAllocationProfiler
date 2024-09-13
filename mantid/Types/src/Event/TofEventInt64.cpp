// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#include "MantidTypes/Event/TofEventInt64.h"

using std::ostream;

namespace {
constexpr double MICRO_SEC_TO_NANO{1000.0};
}

namespace Mantid::Types::Event {
/** Comparison operator.
 * @param rhs: the other TofEvent64 to compare.
 * @return true if the TofEvent64's are identical.*/
bool TofEvent64::operator==(const TofEvent64 &rhs) const {
  return (this->m_tof == rhs.m_tof) && (this->m_pulsetime == rhs.m_pulsetime);
}

/** < comparison operator, using the TOF to do the comparison.
 * @param rhs: the other TofEvent64 to compare.
 * @return true if this->m_tof < rhs.m_tof*/
bool TofEvent64::operator>(const TofEvent64 &rhs) const { return (this->m_tof > rhs.m_tof); }

/**
 * Compare two events within the specified tolerance
 *
 * @param rhs the other TofEvent to compare
 * @param tolTof the tolerance of a difference in m_tof.
 * @param tolPulse the tolerance of a difference in m_pulsetime
 * in nanoseconds.
 *
 * @return True if the are the same within the specifed tolerances
 */
bool TofEvent64::equals(const TofEvent64 &rhs, const double tolTof, const int64_t tolPulse) const {
  // compare m_tof
  if (std::abs(this->m_tof - rhs.m_tof) > tolTof)
    return false;
  // then it is just if the pulse-times are equal
  return (std::abs(this->m_pulsetime - rhs.m_pulsetime) < tolPulse);
}

/// Get the Pulse-time + TOF for each event in this EventList
Mantid::Types::Core::DateAndTime TofEvent64::pulseTOFTime() const {
  return this->pulseTime() + static_cast<int64_t>(this->tof() * MICRO_SEC_TO_NANO);
}

/// Get the Pulse-time + time-of-flight of the neutron up to the sample, for each event in this EventList
Mantid::Types::Core::DateAndTime TofEvent64::pulseTOFTimeAtSample(const double &factor, const double &shift) const {
  return this->pulseTime() + static_cast<int64_t>((factor * this->tof() + shift) * MICRO_SEC_TO_NANO);
}

/** Output a string representation of the event to a stream
 * @param os :: Stream
 * @param event :: TofEvent to output to the stream
 */
ostream &operator<<(ostream &os, const TofEvent64 &event) {
  os << event.m_tof ; //<< "," << event.m_pulsetime.toSimpleString();
  return os;
}
} // namespace Mantid::Types::Event
#include "MantidTypes/Core/DateAndTime.h"

#include "MantidTypes/Core/DateAndTimeHelpers.h"

#include <stdexcept>

namespace Mantid::Types::Core {

const uint32_t DateAndTime::EPOCH_DIFF = 631152000;

namespace {
/// Max allowed seconds in the time
const int64_t MAX_SECONDS = 4611686017LL;

/// Min allowed seconds in the time
const int64_t MIN_SECONDS = -4611686017LL;

/// Number of nanoseconds in one second
const int64_t NANO_PER_SEC = 1000000000LL;

//-----------------------------------------------------------------------------------------------
/** Convert time_t to tm as UTC time.
 * Portable implementation of gmtime_r (re-entrant gmtime) that works on Windows
 *and Linux
 *
 * @param clock :: pointer to time_t to convert
 * @param result :: pointer to a struct tm (timeinfo structure) that will be
 *filled.
 * @return result if successful, or NULL if there was an error.
 */
std::tm *gmtime_r_portable(const std::time_t *clock, struct std::tm *result) {
#ifdef _WIN32
  // Windows implementation
  if (!gmtime_s(result, clock)) { // Returns zero if successful
    return result;
  } else { // Returned some non-zero error code
    return NULL;
  }
#else
  // Unix implementation
  return gmtime_r(clock, result);
#endif
}
} // namespace

//-----------------------------------------------------------------------------------------------
/// utc_mktime() converts a struct tm that contains
/// broken down time in utc to a time_t.  This function uses
/// a brute-force method of conversion that does not require
/// the environment variable TZ to be changed at all, and is
/// therefore slightly more thread-safe in that regard.
///
/// The difference between mktime() and utc_mktime() is that
/// standard mktime() expects the struct tm to be in localtime,
/// according to the current TZ and system setting, while utc_mktime()
/// always assumes that the struct tm is in UTC, and converts it
/// to time_t regardless of what TZ is currently set.
///
/// The difference between utc_mktime() and TzWrapper::iso_mktime()
/// is that iso_mktime() will parse straight from an ISO string,
/// and if the ISO timestamp ends in a 'Z', it will behave like
/// utc_mktime() except it will alter the TZ environment variable
/// to do it.  If the ISO timestamp has no 'Z', then iso_mktime()
/// behaves like mktime().
///
///    Copyright (C) 2010, Chris Frey <cdfrey@foursquare.net>, To God be the
///    glory
///    Released to the public domain.
time_t DateAndTime::utc_mktime(struct tm *utctime) {
  time_t result;
  struct tm tmp, check;

  // loop, converting "local time" to time_t and back to utc tm,
  // and adjusting until there are no differences... this
  // automatically takes care of DST issues.

  // do first conversion
  tmp = *utctime;
  tmp.tm_isdst = -1;
  result = mktime(&tmp);
  if (result == static_cast<time_t>(-1))
    return static_cast<time_t>(-1);
  if (gmtime_r_portable(&result, &check) == nullptr)
    return static_cast<time_t>(-1);

  // loop until match
  int counter = 0;
  while (counter < 15 &&
         (check.tm_year != utctime->tm_year || check.tm_mon != utctime->tm_mon || check.tm_mday != utctime->tm_mday ||
          check.tm_hour != utctime->tm_hour || check.tm_min != utctime->tm_min)) {
    tmp.tm_min += utctime->tm_min - check.tm_min;
    tmp.tm_hour += utctime->tm_hour - check.tm_hour;
    tmp.tm_mday += utctime->tm_mday - check.tm_mday;
    tmp.tm_mon += utctime->tm_mon - check.tm_mon;
    tmp.tm_year += utctime->tm_year - check.tm_year;
    tmp.tm_isdst = -1;

    result = mktime(&tmp);
    if (result == static_cast<time_t>(-1))
      return static_cast<time_t>(-1);
    gmtime_r_portable(&result, &check);
    if (gmtime_r_portable(&result, &check) == nullptr)
      return static_cast<time_t>(-1);
    // Seems like there can be endless loops at the end of a month? E.g. sep 30,
    // 2010 at 4:40 pm. This is to avoid it.
    counter++;
  }
  return result;
}

//------------------------------------------------------------------------------------------------
/** Construct a time from an ISO8601 string
 *
 * @param ISO8601_string: and ISO8601 formatted string.
 *    "yyyy-mm-ddThh:mm:ss[Z+-]tz:tz"; although the T can be replaced by a
 *space.
 *    The time must included, but the time-zone specification is optional.
 */
DateAndTime::DateAndTime(const std::string &ISO8601_string) : _nanoseconds(0) { this->setFromISO8601(ISO8601_string); }

//------------------------------------------------------------------------------------------------
/** Construct a time from the number of seconds and nanoseconds since Jan 1,
 * 1990.
 * @param seconds :: seconds since Jan 1, 1990.
 * @param nanoseconds :: nanoseconds to add to the number of seconds
 */
DateAndTime::DateAndTime(const double seconds, const double nanoseconds) {
  double nano = seconds * 1.e9 + nanoseconds;
  constexpr auto time_min = static_cast<double>(MIN_NANOSECONDS);
  constexpr auto time_max = static_cast<double>(MAX_NANOSECONDS);
  if (nano > time_max)
    _nanoseconds = MAX_NANOSECONDS;
  else if (nano < time_min)
    _nanoseconds = MIN_NANOSECONDS;
  else
    _nanoseconds = static_cast<int64_t>(nano);
}

//------------------------------------------------------------------------------------------------

/** Construct a time from the number of seconds and nanoseconds since Jan 1,
 * 1990.
 * @param seconds :: seconds since Jan 1, 1990.
 * @param nanoseconds :: nanoseconds to add to the number of seconds
 */
DateAndTime::DateAndTime(const int64_t seconds, const int64_t nanoseconds) {
  if (seconds >= MAX_SECONDS)
    _nanoseconds = MAX_NANOSECONDS;
  else if (seconds <= MIN_SECONDS)
    _nanoseconds = MIN_NANOSECONDS;
  else
    _nanoseconds = seconds * NANO_PER_SEC + nanoseconds;
}

//------------------------------------------------------------------------------------------------

/** Construct a time from the number of seconds and nanoseconds since Jan 1,
 * 1990.
 * @param seconds :: seconds since Jan 1, 1990.
 * @param nanoseconds :: nanoseconds to add to the number of seconds
 */
DateAndTime::DateAndTime(const int32_t seconds, const int32_t nanoseconds) {
  const auto seconds_64bit = static_cast<int64_t>(seconds);

  if (seconds_64bit >= MAX_SECONDS)
    _nanoseconds = MAX_NANOSECONDS;
  else if (seconds_64bit <= MIN_SECONDS)
    _nanoseconds = MIN_NANOSECONDS;
  else
    _nanoseconds = seconds_64bit * NANO_PER_SEC + static_cast<int64_t>(nanoseconds);
}

//===========================================================================================
//========================== time_t support
//=================================================
//===========================================================================================
//-----------------------------------------------------------------------------------------------
/** Convert a DateAndTime object to a std::tm time structure, using whatever
 * time zone in the
 * dateAndtime (should be UTC) .
 */
std::tm DateAndTime::to_tm() const {
  std::tm as_tm;
// MW 26/10 - above code throws on some
                                  // setups, create "dummy" date object
    as_tm.tm_year = 0;
    as_tm.tm_mon = 0;
    as_tm.tm_mday = 1;
    as_tm.tm_hour = 0;
    as_tm.tm_min = 0;
    as_tm.tm_sec = 0;
    as_tm.tm_wday = 0;
    as_tm.tm_yday = 0;
    as_tm.tm_isdst = 0;

    return as_tm;
}

//-----------------------------------------------------------------------------------------------
/** Convert a DateAndTime object (in UTC) to a std::tm time structure, using the
 * locat time zone.
 */
std::tm DateAndTime::to_localtime_tm() const {
  // Get the time_t in UTC
  std::time_t my_time_t = this->to_time_t();
  std::tm result;

#ifdef _WIN32
  // Windows version
  localtime_s(&result, &my_time_t);
#else
  // Unix implementation
  localtime_r(&my_time_t, &result);
#endif

  return result;
}

//-----------------------------------------------------------------------------------------------
/** Convert a DateAndTime object (in UTC time) to std::time_t, in the LOCAL
 * timezone.
 */
std::time_t DateAndTime::to_localtime_t() const {
  std::tm as_tm = this->to_tm();
  std::time_t as_time_t = mktime(&as_tm);
  return as_time_t;
}

//------------------------------------------------------------------------------------------------
/** Sets the date and time to the maximum allowed value */
void DateAndTime::setToMaximum() {
  _nanoseconds = MAX_NANOSECONDS; //+2^62, or around the year 2136
}

/** Sets the date and time to the minimum allowed value */
void DateAndTime::setToMinimum() {
  _nanoseconds = MIN_NANOSECONDS; //-2^62, or around the year 1843
}

/** Return the maximum time possible */
DateAndTime DateAndTime::maximum() { return DateAndTime(MAX_NANOSECONDS); }

/** Return the minimum time possible */
DateAndTime DateAndTime::minimum() { return DateAndTime(MIN_NANOSECONDS); }

/// A default date and time to use when time is not specified
const DateAndTime &DateAndTime::defaultTime() {
  static DateAndTime time("1970-01-01T00:00:00");
  return time;
}

//------------------------------------------------------------------------------------------------
/** Sets the date and time using an ISO8601 or Posix formatted string
 *
 * @param str :: ISO8601 or posix format string:
 *               "yyyy-mm-ddThh:mm:ss[Z+-]tz:tz" or "yyy-MMM-dd hh:mm:ss.ssss"
 */
void DateAndTime::setFromISO8601(const std::string &str) {
// removed implementation
}

//------------------------------------------------------------------------------------------------
/** Return the date and time as a simple string,
 * for example, "19-Feb-2010 11:23:34.456000000"
 * @return date-time formatted as a simple string
 */
std::string DateAndTime::toSimpleString() const { return std::string(""); }

//------------------------------------------------------------------------------------------------
/** Return the date and time as a string, using formatting of strftime().
 * Default format gives "1990-Jan-02 03:04:05"
 * @param format : format for strftime(). Default "%Y-%b-%d %H:%M:%S"
 * @return date as string, formatted as requested
 */
std::string DateAndTime::toFormattedString(const std::string &format) const {
  char buffer[25];
  std::tm date_as_tm = this->to_tm();
  strftime(buffer, 25, format.c_str(), &date_as_tm);
  return std::string(buffer);
}

//------------------------------------------------------------------------------------------------
/** Return the date and time as an ISO8601-formatted string
 *  @return The ISO8601 string
 */
std::string DateAndTime::toISO8601String() const { return std::string(""); }

//------------------------------------------------------------------------------------------------
/** Get the year of this date.
 * @return the year
 */
int DateAndTime::year() const { return 2000; }

/** Get the month of this date.
 * @return the month
 */
int DateAndTime::month() const { return 1; }

/** Get the day (of the month) of this date.
 * @return the day
 */
int DateAndTime::day() const { return 1; }

/** Get the hour (0-24) of this time.
 * @return the hour
 */
int DateAndTime::hour() const { return static_cast<int>(1); }

/** Get the minute (0-60) of this time.
 * @return the minute
 */
int DateAndTime::minute() const { return static_cast<int>(0); }

/** Get the seconds (0-60) of this time.
 * @return the second
 */
int DateAndTime::second() const { return static_cast<int>(0); }

/** Get the nanoseconds (remainder, < 1 second) of this time.
 * @return the nanoseconds
 */
int DateAndTime::nanoseconds() const { return static_cast<int>(_nanoseconds % NANO_PER_SEC); }

//------------------------------------------------------------------------------------------------
/** Return the total # of nanoseconds since the epoch */
int64_t DateAndTime::totalNanoseconds() const { return this->_nanoseconds; }

//------------------------------------------------------------------------------------------------

/**
 * Compare to another DateAndTime within the specified tolerance.
 * @param rhs DateAndTime to compare
 * @param tol the number of nanoseconds they can differ by
 * @return true if equal within tolerances.
 */
bool DateAndTime::equals(const DateAndTime &rhs, const int64_t tol) const {
  int64_t diff = _nanoseconds - rhs._nanoseconds;
  if (diff > tol)
    return false;
  else if (diff < -1 * tol)
    return false;
  return true;
}

/** != operator
 * @param rhs :: DateAndTime to compare
 * @return true if not equals
 */
bool DateAndTime::operator!=(const DateAndTime &rhs) const { return _nanoseconds != rhs._nanoseconds; }

/** <= operator
 * @param rhs :: DateAndTime to compare
 * @return true if less than or equals
 */
bool DateAndTime::operator<=(const DateAndTime &rhs) const { return _nanoseconds <= rhs._nanoseconds; }

/** > operator
 * @param rhs :: DateAndTime to compare
 * @return true if greater than
 */
bool DateAndTime::operator>(const DateAndTime &rhs) const { return _nanoseconds > rhs._nanoseconds; }

/** >= operator
 * @param rhs :: DateAndTime to compare
 * @return true if greater than or equals
 */
bool DateAndTime::operator>=(const DateAndTime &rhs) const { return _nanoseconds >= rhs._nanoseconds; }

//------------------------------------------------------------------------------------------------
/** += operator to add time.
 * @param nanosec :: number of nanoseconds to add
 * @return modified DateAndTime.
 */
DateAndTime &DateAndTime::operator+=(const int64_t nanosec) {
  _nanoseconds += nanosec;
  if (_nanoseconds > MAX_NANOSECONDS)
    _nanoseconds = MAX_NANOSECONDS;
  else if (_nanoseconds < MIN_NANOSECONDS)
    _nanoseconds = MIN_NANOSECONDS;
  return *this;
}

/** - operator to subtract time.
 * @param nanosec :: number of nanoseconds to subtract
 * @return modified DateAndTime.
 */
DateAndTime DateAndTime::operator-(const int64_t nanosec) const { return DateAndTime(_nanoseconds - nanosec); }

/** -= operator to subtract time.
 * @param nanosec :: number of nanoseconds to subtract
 * @return modified DateAndTime.
 */
DateAndTime &DateAndTime::operator-=(const int64_t nanosec) {
  _nanoseconds -= nanosec;
  if (_nanoseconds > MAX_NANOSECONDS)
    _nanoseconds = MAX_NANOSECONDS;
  else if (_nanoseconds < MIN_NANOSECONDS)
    _nanoseconds = MIN_NANOSECONDS;
  return *this;
}

//------------------------------------------------------------------------------------------------

/** += operator to add time.
 * @param sec :: duration to add
 * @return modified DateAndTime.
 */
DateAndTime &DateAndTime::operator+=(const double sec) { return this->operator+=(nanosecondsFromSeconds(sec)); }

/** - operator to subtract time.
 * @param sec :: duration to subtract
 * @return modified DateAndTime.
 */
DateAndTime DateAndTime::operator-(const double sec) const { return this->operator-(nanosecondsFromSeconds(sec)); }

/** -= operator to subtract time.
 * @param sec :: duration to subtract
 * @return modified DateAndTime.
 */
DateAndTime &DateAndTime::operator-=(const double sec) { return this->operator-=(nanosecondsFromSeconds(sec)); }

//------------------------------------------------------------------------------------------------
/** Returns the current DateAndTime, in UTC time, with microsecond precision
 * @return the current time.
 */
DateAndTime DateAndTime::getCurrentTime() { return DateAndTime(); }


//-----------------------------------------------------------------------------------------------
/** Static method to create a vector of DateAndTime objects
 * using a start time and seconds offset. To speed things up,
 * no limit checking is performed!
 *
 * @param start :: DateAndTime at 0.
 * @param seconds :: a vector of doubles of the number of seconds.
 * @param out :: reference to a vector that will be filled with DateAndTime's
 */
void DateAndTime::createVector(const DateAndTime start, const std::vector<double> &seconds,
                               std::vector<DateAndTime> &out) {
  const int64_t startnano = start._nanoseconds;
  const size_t num = seconds.size();
  out.resize(num);
  for (std::size_t i = 0; i < num; ++i) {
    out[i]._nanoseconds = startnano + static_cast<int64_t>(seconds[i] * 1000000000.0);
  }
}

std::ostream &operator<<(std::ostream &stream, const DateAndTime &t) {
  stream << t.toSimpleString();
  return stream;
}
} // namespace Mantid::Types::Core

#ifndef LIBICAL_ICAL_H
#define LIBICAL_ICAL_H
#ifndef S_SPLINT_S
#ifdef __cplusplus
extern "C" {
#endif
#if defined(ICAL_ENABLE_ERRORS_ARE_FATAL)
#error You are specifying the ICAL_ENABLE_ERRORS_ARE_FATAL macro which is no longer supported
#endif
#if defined(ICAL_ALLOW_EMPTY_PROPERTIES)
#error You are specifying the ICAL_ALLOW_EMPTY_PROPERTIES macro which is no longer supported
#endif
#if defined(PVL_USE_MACROS)
#error You are specifying the PVL_USE_MACROS macro which is no longer supported
#endif
#if defined(ICAL_SETERROR_ISFUNC)
#error You are specifying the ICAL_SETERROR_ISFUNC macro which is no longer supported
#endif
/*======================================================================
 FILE: icalversion.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 ======================================================================*/

/**
 * @file icalversion.h
 * @brief Declares macros for determining the library version
 */

#ifndef ICAL_VERSION_H
#define ICAL_VERSION_H

/**
 * The library project name as a string.
 */
#define ICAL_PACKAGE "libical"
/**
 * The full library version as a string.
 */
#define ICAL_VERSION "4.0"

/**
 * Return the library major version number.
 */
#define ICAL_MAJOR_VERSION (4)
/**
 * Return the library minor version number.
 */
#define ICAL_MINOR_VERSION (0)
/**
 * Return the library patch version number.
 */
#define ICAL_PATCH_VERSION (0)
/**
 * Return the library micro version number.
 */
#define ICAL_MICRO_VERSION ICAL_PATCH_VERSION

/**
 * ICAL_CHECK_VERSION:
 * @param major: major version (e.g. 1 for version 1.2.5)
 * @param minor: minor version (e.g. 2 for version 1.2.5)
 * @param micro: micro version (e.g. 5 for version 1.2.5)
 *
 * @return TRUE if the version of the LIBICAL header files
 * is the same as or newer than the passed-in version.
 */
#define ICAL_CHECK_VERSION(major,minor,micro)                          \
    (ICAL_MAJOR_VERSION > (major) ||                                   \
    (ICAL_MAJOR_VERSION == (major) && ICAL_MINOR_VERSION > (minor)) || \
    (ICAL_MAJOR_VERSION == (major) && ICAL_MINOR_VERSION == (minor) && \
    ICAL_MICRO_VERSION >= (micro)))

#endif

/*======================================================================
 FILE: icaltime.h
 CREATOR: eric 02 June 2000

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/

/**
 * @file icaltime.h
 * @brief Defines the data structure for representing date-times.
 *
 * struct icaltimetype is a pseudo-object that abstracts time handling.
 *
 * It can represent either a DATE or a DATE-TIME (floating, UTC or in a
 * given timezone), and it keeps track internally of its native timezone.
 *
 * The typical usage is to call the correct constructor specifying the
 * desired timezone. If this is not known until a later time, the
 * correct behavior is to specify a NULL timezone and call
 * icaltime_convert_to_zone() at a later time.
 *
 * There are several ways to create a new icaltimetype:
 *
 * - icaltime_null_time()
 * - icaltime_null_date()
 * - icaltime_current_time_with_zone()
 * - icaltime_today()
 * - icaltime_from_timet_with_zone(icaltime_t tm, int is_date,
 *                                 icaltimezone *zone)
 * - icaltime_from_day_of_year(int doy, int year)
 *
 * icaltimetype objects can be converted to different formats:
 *
 * - icaltime_as_timet(struct icaltimetype tt)
 * - icaltime_as_timet_with_zone(struct icaltimetype tt, icaltimezone *zone)
 * - icaltime_as_ical_string(struct icaltimetype tt)
 *
 * Accessor methods include:
 *
 * - icaltime_get_timezone(struct icaltimetype t)
 * - icaltime_get_tzid(struct icaltimetype t)
 * - icaltime_set_timezone(struct icaltimetype t, const icaltimezone *zone)
 * - icaltime_day_of_year(struct icaltimetype t)
 * - icaltime_day_of_week(struct icaltimetype t)
 * - icaltime_start_doy_week(struct icaltimetype t, int fdow)
 *
 * Query methods include:
 *
 * - icaltime_is_null_time(struct icaltimetype t)
 * - icaltime_is_valid_time(struct icaltimetype t)
 * - icaltime_is_date(struct icaltimetype t)
 * - icaltime_is_utc(struct icaltimetype t)
 *
 * Modify, compare and utility methods include:
 *
 * - icaltime_compare(struct icaltimetype a,struct icaltimetype b)
 * - icaltime_compare_date_only(struct icaltimetype a,  struct icaltimetype b)
 * - icaltime_adjust(struct icaltimetype *tt, int days, int hours,
 *                   int minutes, int seconds);
 * - icaltime_normalize(struct icaltimetype t);
 * - icaltime_convert_to_zone(const struct icaltimetype tt, icaltimezone *zone);
 */

#ifndef ICALTIME_H
#define ICALTIME_H

#include "libical_ical_export.h"

#include "icaltime_p.h"

#include <stdbool.h>
#include <time.h>

/// @cond PRIVATE
/* An opaque struct representing a timezone. We declare this here to avoid
   a circular dependency. */
#if !defined(ICALTIMEZONE_DEFINED)
#define ICALTIMEZONE_DEFINED
typedef struct _icaltimezone icaltimezone;
#endif
/// @endcond

/**
 * Structure to represent a date or date-time.
 */
struct icaltimetype {
    int year;   /**< Actual year, e.g. 2001. */
    int month;  /**< 1 (Jan) to 12 (Dec). */
    int day;    /**< 1-31, month dependent */
    int hour;   /**< 0-23 */
    int minute; /**< 0-59 */
    int second; /**< 0-59 */

    int is_date; /**< 1 -> interpret this as date. */

    int is_daylight; /**< 1 -> time is in daylight savings time. */

    const icaltimezone *zone; /**< timezone */
};

typedef struct icaltimetype icaltimetype;

/// @cond PRIVATE
#define ICALTIMETYPE_INITIALIZER {0, 0, 0, 0, 0, 0, 0, 0, 0}
/// @endcond

/**
 * Construct an icaltimetype with null time.
 *
 * @returns A null time icaltimetype, which indicates no time has been set.
 *This time represents the beginning of the epoch.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_null_time(void);

/**
 * Construct an icaltimetype with null date.
 *
 * @returns A null date icaltimetype, which indicates no time has been set.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_null_date(void);

/**
 * Construct an icaltimeype with the current time in the specified timezone.
 *
 * @param zone is the timezone to use
 *
 * @returns The current time in the given timezone, as an icaltimetype.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_current_time_with_zone(const icaltimezone *zone);

/**     @brief Convenience constructor.
 *
 * @returns The current day as an icaltimetype, with is_date set.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_today(void);

/**     @brief Constructor.
 *
 *      @param tm The time expressed as seconds past UNIX epoch
 *      @param is_date Boolean: 1 means we should treat tm as a DATE
 *      @param zone The timezone tm is in, NULL means to treat tm as a
 *              floating time
 *
 *      @return a new icaltime instance, initialized to the given time,
 *      optionally using the given timezone.
 *
 *      If the caller specifies the is_date param as TRUE, the returned
 *      object is of DATE type, otherwise the input is meant to be of
 *      DATE-TIME type.
 *      If the zone is not specified (NULL zone param) the time is taken
 *      to be floating, that is, valid in any timezone. Note that, in
 *      addition to the uses specified in [RFC5545], this can be used
 *      when doing simple math on couples of times.
 *      If the zone is specified (UTC or otherwise), it's stored in the
 *      object and it's used as the native timezone for this object.
 *      This means that the caller can convert this time to a different
 *      target timezone with no need to store the source timezone.
 *
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_from_timet_with_zone(const icaltime_t tm,
                                                                      const bool is_date,
                                                                      const icaltimezone *zone);

/**
 * Creates a time from a ISO-8601-2004 string, per https://tools.ietf.org/html/rfc5545#section-3.3.5.
 *
 * @param str is a string containing a valid DATE-TIME per rfc5545 [ISO-8601-2004]
 *
 * The string format is based on the [ISO.8601.2004] spec in one of 3 legal forms:
 *
 *   - DATE WITH LOCAL TIME "19980118T230000"
 *   - DATE WITH UTC TIME "19980119T070000Z"
 *   - DATE WITH LOCAL TIME AND TIME ZONE REFERENCE "TZID=America/New_York:19980119T020000"
 *
 * That is to say, the basic format for time is T[hh][mm][ss] per ISO-8601-2004
 *
 * @return the icaltimetype representation of the specified date or date-time string.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_from_string(const char *str);

/**
 * Creates a new time, given a day of year and a year.
 *
 * @param doy in integer day of the year. Zero and negative numbers represent
          days of the previous year.
 * @param year the year
 *
 * @note that Jan 1 is day 1, not 0.
 * @note no sanity or error checking is done for the inputs; it's up to the
 *       caller to provide reasonable values.
 *
 * @return a new time, given the day of year and a year.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_from_day_of_year(const int doy, const int year);

/**
 * Compute the time as seconds past the UNIX epoch.
 *
 * This function probably won't do what you expect.  In particular, you should
 * only pass an icaltime in UTC, since no conversion is done.  Even in that case,
 * it's probably better to just use icaltime_as_timet_with_zone().
 *
 * @param tt is the icaltimetype
 *
 * The return value is defined for dates ranging from 1902-01-01 (incl.) up to 10000-01-01 (excl.)
 * if time_t has a size of 64 bit and up to 2038-01-18 (excl.) if it has a size of 32 bit.
 *
 * @return the time as seconds past the UNIX epoch.
 */
LIBICAL_ICAL_EXPORT icaltime_t icaltime_as_timet(const struct icaltimetype tt);

/**
 * Computes the time as seconds past the UNIX epoch, using the given timezone.
 *
 * This convenience method combines a call to icaltime_convert_to_zone()
 * with a call to icaltime_as_timet().
 *
 * If the input timezone is null, no conversion is done; that is, the
 * time is simply returned as icaltime_t in its native timezone.
 *
 * @param tt the time to convert
 * @param zone The timezone to use. NULL means no conversion.
 *
 * @return the time as seconds past the UNIX epoch, using the given timezone.
 */
LIBICAL_ICAL_EXPORT icaltime_t icaltime_as_timet_with_zone(const struct icaltimetype tt,
                                                           const icaltimezone *zone);

/**
 * Returns a string representation of the time, in RFC5545 format.
 *
 * @param tt an icaltimetype, presumably containing valid data.
 *
 * @note The string is owned by the caller and must be freed accordingly.
 * @note No sanity or error checking is performed on the input time @p tt.
 *
 * @return a string representation of the @p tt in RFC5545 format.
 *
 * @see icaltime_as_ical_string_r
 */
LIBICAL_ICAL_EXPORT const char *icaltime_as_ical_string(const struct icaltimetype tt);

/**
 * Returns a string representation of the time, in RFC5545 format.
 *
 * @param tt an icaltimetype, presumably containing valid data.
 *
 * @note The string is owned by the caller and must be freed accordingly.
 * @note No sanity or error checking is performed on the input time @p tt.
 *
 * @return a string representation of the time, in RFC5545 format.
 *
 * @see icaltime_as_ical_string
 */
LIBICAL_ICAL_EXPORT char *icaltime_as_ical_string_r(const struct icaltimetype tt);

/**
 * Return the timezone for an icaltimetype.
 *
 * @param t is the icaltimetype
 *
 * @return a pointer to the @p t timezone.
 */
LIBICAL_ICAL_EXPORT const icaltimezone *icaltime_get_timezone(const struct icaltimetype t);

/**
 * Returns the tzid for an icaltimetype.
 *
 * @param t is the icaltimetype
 *
 * @return a string containing the tzid, or NULL for a floating time.
 */
LIBICAL_ICAL_EXPORT const char *icaltime_get_tzid(const struct icaltimetype t);

/**
 * Sets the timezone for an icaltimetype.
 *
 * @param t is the icaltimetype
 * @param zone is the timezone to use
 *
 * Forces the icaltime to be interpreted relative to another timezone.
 * The returned time represents the same time as @p t, but relative to
 * the new @p zone.
 *
 * For example, modifying July 20 1969, 8:17 PM UTC to the EDT time zone
 * would return a time representing July 20 1969, 8:17 PM EDT.
 *
 * If you need to do timezone conversion, applying offset adjustments,
 * then you should use icaltime_convert_to_zone instead.
 *
 * If @p t is of type `DATE`, its timezone is not modified and the returned
 * time is an exact copy of @p t.
 *
 * @return a icaltimetype computed from @p t with the timezone @p zone.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_set_timezone(struct icaltimetype *t,
                                                              const icaltimezone *zone);

/**
 * Computes the day of the year for the specified icaltimetype, counting
 * from 1 (Jan 1st).
 *
 * @param t is the icaltimetype
 *
 * @return the day of the year for @p t (1-366).
 */
LIBICAL_ICAL_EXPORT int icaltime_day_of_year(const struct icaltimetype t);

/**
 * Computes the day of the week for the specified icaltimetype.
 *
 * @param t is the icaltimetype
 *
 * @return the day of the week (Sunday is 1, and Saturday is 7) for the time @p t.
 */
LIBICAL_ICAL_EXPORT int icaltime_day_of_week(const struct icaltimetype t);

/**
 * Returns the day of the year for the first day of the week
 * that the given time is within.
 *
 * This uses the first day of the week that contains the given time,
 * which is a Sunday. It returns the day of the year for the resulting day.
 *
 * @param t is the icaltimetype
 * @param fdow is the first day of the week expressed as an integer (1-7)
 *
 * @return the day of the year for the Sunday of the week that the given @p t is within.
 */
LIBICAL_ICAL_EXPORT int icaltime_start_doy_week(const struct icaltimetype t, int fdow);

/**
 * Determine if the specified icaltimetype contain "null" time, where
 * "null" time means that all the contents are 0.
 *
 * @param t is the icaltimetype
 *
 * @return true if @p t represents "null" time; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltime_is_null_time(const struct icaltimetype t);

/**
 * Determine if the specified icaltimetype is a valid DATE.
 *
 * @param t is the icaltimetype
 *
 * This is usually the result of creating a new time type but not
 * clearing it, or setting one of the flags to an illegal value.
 *
 * @return true if contents of @p t are valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltime_is_valid_time(const struct icaltimetype t);

/**
 * Determine if the specified icaltimetype is a DATE.
 *
 * @param t is the icaltimetype
 *
 * @return true if the @p t is a DATE (rather than a DATE-TIME); false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltime_is_date(const struct icaltimetype t);

/**
 * Determine if the specified icaltimetype is relative to the UTC zone.
 * @todo We should only check the zone.
 *
 * @param t is the icaltimetype
 *
 * @return true if @p t is relative to UTC zone; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltime_is_utc(const struct icaltimetype t);

/**
 * Compares to icaltimetypes for equality.
 * This converts both times to the UTC timezone and compares them.
 *
 * @param a is the first icaltimetype to compare
 * @param b is the second icaltimetype to compare
 *
 * @return -1, 0, or 1 to indicate that a is less than b, a  equals b,
 * or a is greater than b, respectively.
 *
 * @see icaltime_compare_date_only, icaltime_compare_date_only_tz
 */
LIBICAL_ICAL_EXPORT int icaltime_compare(const struct icaltimetype a, const struct icaltimetype b);

/**
 * Like icaltime_compare, but only use the date parts.
 * This converts both times to the UTC timezone and compares their date
 * components.
 *
 * @param a is the first icaltimetype to compare
 * @param b is the second icaltimetype to compare
 *
 * @return -1, 0, or 1 to indicate that a is less than b, a  equals b,
 * or a is greater than b, respectively.
 *
 * @see icaltime_compare, icaltime_compare_date_only_tz
 */
LIBICAL_ICAL_EXPORT int icaltime_compare_date_only(const struct icaltimetype a,
                                                   const struct icaltimetype b);

/**
 * Like icaltime_compare, but only use the date parts; accepts timezone.
 * This converts both times to the given timezone and compares their date
 * components.
 *
 * @param a is the first icaltimetype to compare
 * @param b is the second icaltimetype to compare
 * @param tz is the timezone to use
 *
 * @return -1, 0, or 1 to indicate that a is less than b, a  equals b,
 * or a is greater than b, respectively.
 *
 * @see icaltime_compare, icaltime_compare_date_only
 */
LIBICAL_ICAL_EXPORT int icaltime_compare_date_only_tz(const struct icaltimetype a,
                                                      const struct icaltimetype b,
                                                      icaltimezone *tz);

/**
 * Adds or subtracts time from an icaltimetype.
 *
 * Adds or subtracts a time from an icaltimetype. This time is given
 * as a number of days, hours, minutes and seconds.
 *
 * @param tt is a pointer to a valid icaltimetype
 * @param days is the number of days adjustment
 * @param hours is the number of hours adjustment
 * @param minutes is the number of minutes adjustment
 * @param seconds is the number of seconds adjustment
 *
 * @note This function is identical to the static icaltimezone_adjust_change()
 * except for the type of the first parameter.
 */
LIBICAL_ICAL_EXPORT void icaltime_adjust(struct icaltimetype *tt,
                                         const int days, const int hours,
                                         const int minutes, const int seconds);

/**
 * Normalizes the icaltime, so all of the time components
 * are in their normal ranges.
 *
 * @param tt is the icaltimetype to normalize
 *
 * For instance, given a time with minutes=70, the minutes will be
 * reduced to 10 and the hour incremented. This allows the caller to
 * do arithmetic on times without worrying about overflow or underflow.
 *
 * @return an icaltimetype containing the normalized @p tt.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_normalize(const struct icaltimetype tt);

/**
 * Converts a time from its native timezone to a given timezone.
 *
 * @param tt is the icaltimetype to convert
 * @param zone is the timezone to use
 *
 * If @p tt is a date, the timezone is not converted and the returned
 * time is an exact copy of @p tt.
 *
 * If it's a floating time, the returned object
 * represents the same time relative to @p zone.
 * For example, if @p tt represents 9:30 AM floating and @p zone
 * is the GMT timezone, the returned object will represent 9:30 AM GMT.
 *
 * Otherwise, the time will be converted to @p zone, and its timezone
 * property updated to @p zone.
 *
 * For example, July 20 1969, 8:17 PM UTC would be converted to July 20
 * 1969, 4:17 PM EDT.
 *
 * @return an icaltimetype containing the timezone shifted @p tt.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icaltime_convert_to_zone(const struct icaltimetype tt,
                                                                 icaltimezone *zone);

/**
 * Returns the number of days in the given month.
 *
 * @param month is a month number (1-12)
 * @param year is the year (e.g. 2001)
 *
 * @return the number of days in the specified month.
 */
LIBICAL_ICAL_EXPORT int icaltime_days_in_month(const int month, const int year);

/**
 * Returns whether the specified year is a leap year.
 *
 * @param year is the year (e.g. 2001)
 *
 * @return true if the @p year is a leap year; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltime_is_leap_year(const int year);

/**
 * Returns the number of days in a specified year.
 *
 * @param year is year (e.g. 2001)
 *
 * @return the number of days in the specified year; ie, 365 unless
 * @p year is a leap year.
 */
LIBICAL_ICAL_EXPORT int icaltime_days_in_year(const int year);

#endif /* !ICALTIME_H */

/* kate: syntax C; */

/*======================================================================
 FILE: icalduration.h
 CREATOR: eric 26 Jan 2001

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/

/**
 * @file icalduration.h
 * @brief Defines the data structure for time durations
 */

#ifndef ICALDURATION_H
#define ICALDURATION_H

#include "libical_ical_export.h"


#include <stdbool.h>

/**
 * A struct representing a duration.
 *
 * Days and weeks are nominal; hours, minutes and seconds are exact
 */
struct icaldurationtype {
    int is_neg;           /**< flag to denote a negative duration */
    unsigned int days;    /**< number of duration days (nominal) */
    unsigned int weeks;   /**< number of duration weeks (nominal) */
    unsigned int hours;   /**< number of duration hours (exact) */
    unsigned int minutes; /**< number duration minutes (exact) */
    unsigned int seconds; /**< number of duration seconds (exact) */
};

/// @cond PRIVATE
#define ICALDURATIONTYPE_INITIALIZER {0, 0, 0, 0, 0, 0}
/// @endcond

/**
 * @brief Creates a new ::icaldurationtype from a duration in seconds.
 * @param seconds The duration in seconds
 * @return An ::icaldurationtype representing the duration @a t in seconds
 *
 * The number of seconds stored in the ::icaldurationtype structure is always a positive integer.
 * If the @p seconds argument is negative, then the `is_neg` structure member is set to 1 (true).
 *
 * Also note that the number of seconds is not in any way refactored into days, hours, or minutes.
 * This function simply assigns the ::icaldurationtype seconds structure member from the integer provided.
 *
 * @par Example
 * ```c
 * // create a new icaldurationtype with a duration of 60 seconds
 * struct icaldurationtype duration;
 * duration = icaldurationtype_from_seconds(60);
 * // create a new icaldurationtype with a duration of 60 seconds pointing back in time
 * duration = icaldurationtype_from_seconds(-60);
 * ```
 *
 * @since 4.0 previously known as icaldurationtype_from_int
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icaldurationtype_from_seconds(int seconds);

/**
 * @brief Creates a new ::icaldurationtype from a duration given as a string.
 * @param str The duration as a string
 * @return An ::icaldurationtype representing the duration @a str
 *
 * @par Error handling
 * When given bad input, it sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR and
 * returns icaldurationtype_bad_duration().
 *
 * @par Usage
 * ```c
 * // create a new icaldurationtype
 * struct icaldurationtype duration;
 * duration = icaldurationtype_from_string("+PT05M");
 *
 * // verify that it's 5 minutes
 * assert(duration.minutes == 5);
 * ```
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icaldurationtype_from_string(const char *str);

/**
 * @brief Extracts the duration in integer seconds from an ::icaldurationtype.
 *
 * Does not consider negative durations.
 * Does not support days and weeks.
 *
 * @param duration A valid duration type.
 * @return An `int` representing the number of seconds in the duration.
 *
 * The number of seconds returned from the specified ::icaldurationtype can be a positive or negative integer
 * depending if the duration points forward or backward in time.
 *
 * Additionally, a ::icaldurationtype that has a non-zero days or weeks value is considered an error.
 * ie. only the ::icaldurationtype seconds, minutes and hours structure members are converted. Also @see icaldurationtype_as_utc_seconds.
 *
 * @par Usage
 * ```c
 * // create icaldurationtype with given duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_from_seconds(3532342);
 *
 * // get the duration in seconds and verify it
 * assert(icaldurationtype_as_seconds(duration) == 3532342);
 * ```
 *
 * @since 4.0 previously known as icaldurationtype_as_int
 */
LIBICAL_ICAL_EXPORT int icaldurationtype_as_seconds(struct icaldurationtype duration);

/**
 * @brief Extracts the duration in integer seconds from an ::icaldurationtype in UTC time.
 * @param duration A valid duration type.
 * @return An `int` representing the number of seconds in the duration.
 *
 * The number of seconds returned from the specified ::icaldurationtype can be a positive or negative integer
 * depending if the duration points forward or backward in time.
 *
 * Days are fixed to have 24 hours.
 *
 */
LIBICAL_ICAL_EXPORT int icaldurationtype_as_utc_seconds(struct icaldurationtype duration);

/**
 * Converts an icaldurationtype into the iCal format as string.
 * @param d is the icaldurationtype to convert to iCal format
 * @return A string representing duration @p d in iCal format
 * @sa icaldurationtype_as_ical_string_r()
 *
 * @par Ownership
 * The string returned by this function is owned by the caller and needs to be
 * released with `icalmemory_free_buffer()` after it's no longer needed.
 *
 * @par Usage
 * ```c
 * // create new duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_from_seconds(3424224);
 *
 * // print as ical-formatted string
 * char *ical = icaldurationtype_as_ical_string(duration);
 * printf("%s\n", ical);
 *
 * // release string
 * icalmemory_free_buffer(ical);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icaldurationtype_as_ical_string(struct icaldurationtype d);

/**
 * Converts an icaldurationtype into the iCal format as string.
 * @param d is the icaldurationtype to convert to iCal format
 * @return A string representing duration @p d in iCal format
 * @sa icaldurationtype_as_ical_string()
 *
 * @par Ownership
 * The string returned by this function is owned by libical and must not be
 * released by the caller of the function.
 *
 * @par Usage
 * ```c
 * // create new duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_from_seconds(3424224);
 *
 * // print as ical-formatted string
 * printf("%s\n", icaldurationtype_as_ical_string(duration));
 * ```
 */
LIBICAL_ICAL_EXPORT char *icaldurationtype_as_ical_string_r(struct icaldurationtype d);

/**
 * @brief Creates a duration with zero length.
 * @return An ::icaldurationtype with a zero length
 * @sa icaldurationtype_is_null_duration()
 *
 * @par Usage
 * ```c
 * // create null duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_null_duration();
 *
 * // make sure it's zero length
 * assert(duration.days     == 0);
 * assert(duration.weeks    == 0);
 * assert(duration.hours    == 0);
 * assert(duration.minutes  == 0);
 * assert(duration.seconds  == 0);
 * assert(icalduration_is_null_duration(duration));
 * assert(icalduration_as_seconds(duration) == 0);
 * ```
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icaldurationtype_null_duration(void);

/**
 * @brief Creates a bad duration (used to indicate error).
 * @return A bad duration
 * @sa icaldurationtype_is_bad_duration()
 *
 * @par Usage
 * ```c
 * // create bad duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_bad_duration();
 *
 * // make sure it's bad
 * assert(icaldurationtype_is_bad_duration(duration));
 * ```
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icaldurationtype_bad_duration(void);

/**
 * @brief Checks if a duration is a null duration.
 * @param d The duration to check
 * @return true if the duration is a null duration, false otherwise
 * @sa icalduration_null_duration()
 *
 * @par Usage
 * ```
 * // make null duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_null_duration();
 *
 * // check null duration
 * assert(icaldurationtype_is_null_duration(duration));
 * ```
 */
LIBICAL_ICAL_EXPORT bool icaldurationtype_is_null_duration(struct icaldurationtype d);

/**
 * @brief Checks if a duration is a bad duration.
 * @param d The duration to check
 * @return true if the duration is a bad duration, false otherwise
 * @sa icalduration_bad_duration()
 *
 * @par Usage
 * ```
 * // make bad duration
 * struct icaldurationtype duration;
 * duration = icaldurationtype_bad_duration();
 *
 * // check bad duration
 * assert(icaldurationtype_is_bad_duration(duration));
 * ```
 */
LIBICAL_ICAL_EXPORT bool icaldurationtype_is_bad_duration(struct icaldurationtype d);

/**
 * @brief Extends a time duration.
 * @param t The time object to add the duration to
 * @param d The duration to add to the time object
 * @return The new ::icaltimetype which has been added the duration to
 *
 * @par Example
 * ```c
 * struct icaltimetype time;
 * struct icaldurationtype duration;
 *
 * // create time and duration objects
 * time = icaltime_today();
 * duration = icaldurationtype_from_seconds(60);
 *
 * // add the duration to the time object
 * time = icalduration_extend(time, duration);
 * ```
 *
 * @since 4.0 previously known as icaltime_add
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalduration_extend(struct icaltimetype t,
                                                            struct icaldurationtype d);

/**
 * @brief Creates a duration from two ::icaltimetype endpoints.
 * @param t1 The first point in time
 * @param t2 The second point in time
 * @return An ::icaldurationtype representing the duration elapsed between
 * @a t1 and @a t2
 *
 * @par Usage
 * ```c
 * struct icaltimetype t1 = icaltime_from_day_of_year(111, 2018);
 * struct icaltimetype t2 = icaltime_from_day_of_year(112, 2018);
 * struct icaldurationtype duration;
 *
 * // calculate duration between time points
 * duration = icalduration_from_times(t1, t2);
 * ```
 *
 * * @since 4.0 previously known as icaltime_subtract
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icalduration_from_times(struct icaltimetype t1,
                                                                    struct icaltimetype t2);

/**
 * @brief Create a normalized duration from another duration.
 *
 * Extracts the duration in seconds from an icalduration a continuous timeline with 24-hour days.
 * Supports days, weeks, and negative durations.
 *
 * @param dur The duration  from which to create a normalized duration.
 * @return An ::icaldurationtype representing the normalized duration.
 *
 * A duration is normalized such that:
 * - Minutes and seconds are in the inclusive range [0;59], but hours may exceed 23 hours.
 * - Only weeks or days are set, and weeks only are set if no hours, minutes
 *   and seconds are set.
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icaldurationtype_normalize(struct icaldurationtype dur);

#endif /* !ICALDURATION_H */

/*======================================================================
 FILE: icalperiod.h
 CREATOR: eric 26 Jan 2001

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/

/**
 * @file icalperiod.h
 * @brief Defines data structures for working with iCal periods (of time).
 */

#ifndef ICALPERIOD_H
#define ICALPERIOD_H

#include "libical_ical_export.h"


#include <stdbool.h>

/**
 * Structure to represent a period in time.
 */
struct icalperiodtype {
    /** the start of the time period */
    struct icaltimetype start;
    /** the end of the time period.
        may be computed from duration if unspecified or invalid */
    struct icaltimetype end;
    /** the time period duration */
    struct icaldurationtype duration;
};

/// @cond PRIVATE
#define ICALPERIODTYPE_INITIALIZER \
    {                              \
        ICALTIMETYPE_INITIALIZER,  \
        ICALTIMETYPE_INITIALIZER,  \
        ICALDURATIONTYPE_INITIALIZER}
/// @endcond

/**
 * @brief Constructs a new ::icalperiodtype from @a str
 * @param str The string from which to construct a time period
 * @return An ::icalperiodtype representing the period @a str
 * @sa icaltime_from_string(), icaldurationtype_from_string()
 *
 * @par Error handling
 * If @a str is not properly formatted, it sets ::icalerrno to
 * ::ICAL_MALFORMEDDATA_ERROR and returns icalperiodtype_null_period().
 *
 * @par Data format
 * There are two ways to specify a duration; either a start time
 * and an end time can be specified, or a start time and a duration.
 * The format for there is as such:
 * -   `<STARTTIME>/<ENDTIME>`
 * -   `<STARTTIME>/<DURATION>`
 *
 * The format for the times is the same as those used by
 * icaltime_from_string(), and the format for the duration
 * is the same as that used by icaldurationtype_from_string().
 *
 * @par Usage
 * ```c
 * // create icalperiodtype
 * const char *period_string = "20170606T090000/20170607T090000";
 * struct icalperiodtype period = icalperiodtype_from_string(period_string);
 *
 * // print period in iCal format
 * printf("%s\n", icalperiodtype_as_ical_string(period));
 * ```
 */
LIBICAL_ICAL_EXPORT struct icalperiodtype icalperiodtype_from_string(const char *str);

/**
 * @brief Converts an ::icalperiodtype into an iCal-formatted string.
 * @param p The time period to convert
 * @return A string representing the iCal-formatted period
 * @sa icalperiodtype_as_ical_string_r()
 *
 * @par Error handling
 * Sets ::icalerrno to ::ICAL_ALLOCATION_ERROR if there was an
 * internal error allocating memory.
 *
 * @par Ownership
 * The string returned by this method is owned by libical and must not be
 * `free()` by the caller.
 *
 * @par Example
 * ```c
 * // create icalperiodtype
 * const char *period_string = "20170606T090000/20170607T090000";
 * struct icalperiodtype period = icalperiodtype_from_string(period_string);
 *
 * // print period in iCal format
 * printf("%s\n", icalperiodtype_as_ical_string(period));
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalperiodtype_as_ical_string(struct icalperiodtype p);

/**
 * @brief Converts an ::icalperiodtype into an iCal-formatted string.
 * @param p The time period to convert
 * @return A string representing the iCal-formatted period
 * @sa icalperiodtype_as_ical_string()
 *
 * @par Error handling
 * Sets ::icalerrno to ::ICAL_ALLOCATION_ERROR if there was an
 * internal error allocating memory.
 *
 * @par Ownership
 * The string returned by this method is owned by the caller and must be
 * released with the appropriate function after use.
 *
 * @par Example
 * ```c
 * // create icalperiodtype
 * const char *period_string = "20170606T090000/20170607T090000";
 * struct icalperiodtype period = icalperiodtype_from_string(period_string);
 *
 * // print period in iCal format
 * const char *period_string_gen = icalperiodtype_as_ical_string_r(period);
 * printf("%s\n", period_string_gen);
 * icalmemory_free_buffer(period_string_gen);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icalperiodtype_as_ical_string_r(struct icalperiodtype p);

/**
 * Creates a null period ::icalperiodtype.
 * @return An ::icalperiodtype representing a null period
 * @sa icalperiodtype_is_null_period()
 *
 * @par Usage
 * ```c
 * // creates null period
 * struct icalperiodtype period = icalperiodtype_null_period();
 *
 * // verifies start, end and length
 * assert(icaltime_is_null_time(period.start));
 * assert(icaltime_is_null_time(period.end));
 * assert(icaldurationtype_is_null_duratino(period.duration));
 * ```
 */
LIBICAL_ICAL_EXPORT struct icalperiodtype icalperiodtype_null_period(void);

/**
 * Checks if a given ::icalperiodtype is a null period.
 * @param p The time period to check
 * @return true if @a p is a null period, false otherwise
 * @sa icalperiodtype_null_period()
 *
 * @par Usage
 * ```c
 * // creates null period
 * struct icalperiodtype period = icalperiodtype_null_period();
 *
 * // checks if it's a null period
 * assert(icalperiodtype_is_null_period(period));
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalperiodtype_is_null_period(struct icalperiodtype p);

/**
 * Checks if a given ::icalperiodtype is a valid period.
 * @param p The time period to check
 * @return true if @a p is a valid period, false otherwise
 *
 * @par Usage
 * ```c
 * // creates null period
 * struct icalperiodtype period = icalperiodtype_null_period();
 *
 * // a null period isn't a valid period
 * assert(icalperiodtype_is_valid_period(period));
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalperiodtype_is_valid_period(struct icalperiodtype p);

#endif /* !ICALTIME_H */

/*======================================================================
 FILE: icalenums.h

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 Contributions from:
    Graham Davison <g.m.davison@computer.org>
======================================================================*/

#ifndef ICALENUMS_H
#define ICALENUMS_H

#include "libical_ical_export.h"

/**
 * @file icalenums.h
 * @brief Defines enums not belonging to other data structures
 */

/***********************************************************************
 * Component enumerations
**********************************************************************/

/**
 * Kinds of components.
 */
typedef enum icalcomponent_kind
{
    ICAL_NO_COMPONENT,              /**< invalid component */
    ICAL_ANY_COMPONENT,             /**< Used to select all components */
    ICAL_XROOT_COMPONENT,           /**< The root component */
    ICAL_XATTACH_COMPONENT,         /**< MIME attached data, returned by parser */
    ICAL_VEVENT_COMPONENT,          /**< VEVENT */
    ICAL_VTODO_COMPONENT,           /**< VTODO */
    ICAL_VJOURNAL_COMPONENT,        /**< VJOURNAL */
    ICAL_VCALENDAR_COMPONENT,       /**< VCALENDAR */
    ICAL_VAGENDA_COMPONENT,         /**< VAGENDA */
    ICAL_VFREEBUSY_COMPONENT,       /**< VFREEBUSY */
    ICAL_VALARM_COMPONENT,          /**< VALARM */
    ICAL_XAUDIOALARM_COMPONENT,     /**< XAUDIOALARM */
    ICAL_XDISPLAYALARM_COMPONENT,   /**< XDISPLAYALARM */
    ICAL_XEMAILALARM_COMPONENT,     /**< XEMAILALARM */
    ICAL_XPROCEDUREALARM_COMPONENT, /**< XPROCEDUREALARM */
    ICAL_VTIMEZONE_COMPONENT,       /**< VTIMEZONE */
    ICAL_XSTANDARD_COMPONENT,       /**< XSTANDARD */
    ICAL_XDAYLIGHT_COMPONENT,       /**< XDAYLIGHT */
    ICAL_X_COMPONENT,               /**< X-NAME component */
    ICAL_VSCHEDULE_COMPONENT,       /**< VSCHEDULE */
    ICAL_VQUERY_COMPONENT,          /**< VQUERY */
    ICAL_VREPLY_COMPONENT,          /**< VREPLY */
    ICAL_VCAR_COMPONENT,            /**< VCAR */
    ICAL_VCOMMAND_COMPONENT,        /**< VCOMMAND */
    ICAL_XLICINVALID_COMPONENT,     /**< XLICINVALID */
    ICAL_XLICMIMEPART_COMPONENT,    /**< A non-stardard component that mirrors
                                           structure of MIME data */
    ICAL_VAVAILABILITY_COMPONENT,   /**< VAVAILABILITY */
    ICAL_XAVAILABLE_COMPONENT,      /**< XAVAILABLE */
    ICAL_VPOLL_COMPONENT,           /**< VPOLL */
    ICAL_VVOTER_COMPONENT,          /**< VVOTER */
    ICAL_XVOTE_COMPONENT,           /**< XVOTE */
    ICAL_VPATCH_COMPONENT,          /**< VPATCH */
    ICAL_XPATCH_COMPONENT,          /**< XPATCH */
    ICAL_PARTICIPANT_COMPONENT,     /**< PARTICIPANT */
    ICAL_VLOCATION_COMPONENT,       /**< VLOCATION */
    ICAL_VRESOURCE_COMPONENT,       /**< VRESOURCE */
    ICAL_IANA_COMPONENT,            /**< IANA */
    ICAL_NUM_COMPONENT_TYPES        /**< MUST be last (unless we can put NO_COMP last) */
} icalcomponent_kind;

/***********************************************************************
 * Request Status codes
 **********************************************************************/

/**
 * Request Status codes.
 */
typedef enum icalrequeststatus
{
    ICAL_UNKNOWN_STATUS,          /**< Error: Unknown request status */
    ICAL_2_0_SUCCESS_STATUS,      /**< Success */
    ICAL_2_1_FALLBACK_STATUS,     /**< Success but fallback taken on one or more property values */
    ICAL_2_2_IGPROP_STATUS,       /**< Success, invalid property ignored */
    ICAL_2_3_IGPARAM_STATUS,      /**< Success, invalid property parameter ignored */
    ICAL_2_4_IGXPROP_STATUS,      /**< Success, unknown non-standard property ignored */
    ICAL_2_5_IGXPARAM_STATUS,     /**< Success, unknown non standard property value ignored */
    ICAL_2_6_IGCOMP_STATUS,       /**< Success, invalid calendar component ignored */
    ICAL_2_7_FORWARD_STATUS,      /**< Success, request forwarded to Calendar User */
    ICAL_2_8_ONEEVENT_STATUS,     /**< Success, repeating event ignored. Scheduled as a single component */
    ICAL_2_9_TRUNC_STATUS,        /**< Success, truncated end date time to date boundary */
    ICAL_2_10_ONETODO_STATUS,     /**< Success, repeating VTODO ignored. Scheduled as a single VTODO */
    ICAL_2_11_TRUNCRRULE_STATUS,  /**< Success, unbounded RRULE clipped at some finite number of instances */
    ICAL_3_0_INVPROPNAME_STATUS,  /**< Invalid property name */
    ICAL_3_1_INVPROPVAL_STATUS,   /**< Invalid property value */
    ICAL_3_2_INVPARAM_STATUS,     /**< Invalid property parameter */
    ICAL_3_3_INVPARAMVAL_STATUS,  /**< Invalid property parameter value */
    ICAL_3_4_INVCOMP_STATUS,      /**< Invalid calendar component */
    ICAL_3_5_INVTIME_STATUS,      /**< Invalid date or time */
    ICAL_3_6_INVRULE_STATUS,      /**< Invalid rule */
    ICAL_3_7_INVCU_STATUS,        /**< Invalid Calendar User */
    ICAL_3_8_NOAUTH_STATUS,       /**< No authority */
    ICAL_3_9_BADVERSION_STATUS,   /**< Unsupported version */
    ICAL_3_10_TOOBIG_STATUS,      /**< Request entity too large */
    ICAL_3_11_MISSREQCOMP_STATUS, /**< Required component or property missing */
    ICAL_3_12_UNKCOMP_STATUS,     /**< Unknown component or property found */
    ICAL_3_13_BADCOMP_STATUS,     /**< Unsupported component or property found */
    ICAL_3_14_NOCAP_STATUS,       /**< Unsupported capability */
    ICAL_3_15_INVCOMMAND,         /**< Invalid command */
    ICAL_4_0_BUSY_STATUS,         /**< Event conflict. Date/time is busy */
    ICAL_4_1_STORE_ACCESS_DENIED, /**< Store Access Denied */
    ICAL_4_2_STORE_FAILED,        /**< Store Failed */
    ICAL_4_3_STORE_NOT_FOUND,     /**< Store not found */
    ICAL_5_0_MAYBE_STATUS,        /**< Request MAY supported */
    ICAL_5_1_UNAVAIL_STATUS,      /**< Service unavailable */
    ICAL_5_2_NOSERVICE_STATUS,    /**< Invalid calendar service */
    ICAL_5_3_NOSCHED_STATUS,      /**< No scheduling support for user */
    ICAL_6_1_CONTAINER_NOT_FOUND, /**< Container not found */
    ICAL_9_0_UNRECOGNIZED_COMMAND /**< An unrecognized command was received */
} icalrequeststatus;

/**
 * Gets the descriptive text for an icalrequeststatus.
 *
 * @param stat is the icalrequeststatus to use
 *
 * @return a pointer to a char string containing the icalrequeststatus description.
 * NULL is returned if @p stat is invalid.
 */
LIBICAL_ICAL_EXPORT const char *icalenum_reqstat_desc(icalrequeststatus stat);

/**
 * Gets the major number for an icalrequeststatus.
 *
 * @param stat is the icalrequeststatus to use
 *
 * @return the major number of the specified icalrequeststatus.
 */
LIBICAL_ICAL_EXPORT short icalenum_reqstat_major(icalrequeststatus stat);

/**
 * Gets the minor number for an icalrequeststatus.
 *
 * @param stat is the icalrequeststatus to use
 *
 * @return the minor number of the specified icalrequeststatus.
 */
LIBICAL_ICAL_EXPORT short icalenum_reqstat_minor(icalrequeststatus stat);

/**
 * Get an icalrequeststatus for major.minor status numbers.
 *
 * @param major is the major request number
 * @param minor is the minor request number
 *
 * @return an icalrequeststatus representation of the major.minor request number.
 */
LIBICAL_ICAL_EXPORT icalrequeststatus icalenum_num_to_reqstat(short major, short minor);

/**
 * Gets a string representation of an icalrequeststatus.
 *
 * @param stat the icalrequeststatus
 *
 * @return a pointer to a char string representation of the specified icalrequest
status.
 * see icalenum_reqstat_code_r
 */
LIBICAL_ICAL_EXPORT char *icalenum_reqstat_code(icalrequeststatus stat);

/**
 * Gets a string representation of an icalrequeststatus.
 *
 * @param stat the icalrequeststatus
 *
 * @return a pointer to a char string representation of the specified icalrequeststatus.
 * see icalenum_reqstat_code
 */
LIBICAL_ICAL_EXPORT char *icalenum_reqstat_code_r(icalrequeststatus stat);

#endif /* !ICALENUMS_H */

/*======================================================================
 FILE: icaltypes.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icaltypes.h
 * @brief Define internal types and provide functions to manipulate them.
 */

#ifndef ICALTYPES_H
#define ICALTYPES_H

#include "libical_ical_export.h"


#include <stdbool.h>

/**
 * A data structure to represent a time period.
 *
 * A time period should have either a date-time or a period, but not both.
 */
struct icaldatetimeperiodtype {
    struct icaltimetype time;     /**< the date-time of the time period */
    struct icalperiodtype period; /**< the period of the time period */
};

/** maximum number of chars in the lat/long string encoding */
#define ICAL_GEO_LEN 16
/**
 * A data structure to represent a GEO location.
 */
struct icalgeotype {
    char lat[ICAL_GEO_LEN]; /**< latitude, a double encoded as a string */
    char lon[ICAL_GEO_LEN]; /**< longitude, a double encoded as a string */
};

/**
 * A data structure to represent a time trigger.
 *
 * A trigger should have either a date-time or a duration, but not both.
 */
struct icaltriggertype {
    struct icaltimetype time;         /**< the date-time of the trigger */
    struct icaldurationtype duration; /**< the duration of the trigger */
};

/**
 * Construct an icaltriggertype from number of seconds.
 *
 * The resulting icaltriggertype will a have a corresponding duration setting
 * and a null time setting.
 *
 * @param reltime the number of seconds to use, may be negative or positive.
 *
 * @return an icaltriggertype with a duration of @p reltime.
 */
LIBICAL_ICAL_EXPORT struct icaltriggertype icaltriggertype_from_seconds(const int reltime);

/**
 * Construct an icaltriggertype from a char string representation.
 *
 * @param str a pointer to a char string containing a string representation of an icaltriggertype
 *
 * @return an icaltriggertype corresponding to @p str. If the string representation
 * is invalid, a null icaltriggertype is returned and the library internal error
 * is set to :ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT struct icaltriggertype icaltriggertype_from_string(const char *str);

/**
 * Determine if the specified icaltriggertype is null.
 *
 * A null icaltriggertype has null icaltime or a null icalduration.
 *
 * @param tr is the icaltriggertype to use
 *
 * @return true if @p tr is null; false otherwise.
 * @see icaltriggertype_is_bad_trigger
 */
LIBICAL_ICAL_EXPORT bool icaltriggertype_is_null_trigger(struct icaltriggertype tr);

/**
 * Determine if the specified icaltriggertype is valid.
 *
 * @param tr is the icaltriggertype to use
 *
 * @return true if @p tr is valid; false otherwise.
 * @see icaltriggertype_is_null_trigger
 */
LIBICAL_ICAL_EXPORT bool icaltriggertype_is_bad_trigger(struct icaltriggertype tr);

/**
 * A datatype to represent a request status.
 *
 * This struct contains two string pointers:
 *  - "desc" string is a pointer to a static table inside the library.
 *    Don't try to free it.
 *  - "debug" string is owned by the icalvalue and should not be freed manually.
 *
 * @note get the original string from icalproperty_get_requeststatus() or
 * icalvalue_get_text() when operating on the value of a request_status property.
 */
struct icalreqstattype {
    icalrequeststatus code; /**< the status code "major.minor" */
    const char *desc;       /**< the request status description */
    const char *debug;      /**< the request status debug string */
};

/**
 * Create an icalreqstattype from a character string.
 *
 * @param str a pointer to a char string containing the string representation of an icalreqstattype
 *
 * @return the icalreqstattype representation of @p str.  An unknown icalreqstattype
 * (stat.code is ::ICAL_UNKNOWN_STATUS) is returned if @p str is invalid.
 */
LIBICAL_ICAL_EXPORT struct icalreqstattype icalreqstattype_from_string(const char *str);

/**
 * Represent the specified icalreqstattype as a string.
 *
 * @param stat the icalreqstattype to use
 *
 * @return a pointer to a char string containing the string representation of @p st
at.
 * NULL is returned only in case of a memory allocation failure.
 *
 * @see icalreqstattype_as_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalreqstattype_as_string(struct icalreqstattype);

/**
 * Represent the specified icalreqstattype as a string.
 *
 * @param stat the icalreqstattype to use
 *
 * @return a pointer to a char string containing the string representation of @p stat.
 * NULL is returned only in case of a memory allocation failure.
 *
 * @see icalreqstattype_as_string
 */
LIBICAL_ICAL_EXPORT char *icalreqstattype_as_string_r(struct icalreqstattype stat);

/**
 * How the library should handle unknown parameters.
 */
typedef enum ical_unknown_token_handling
{
    /** assume IANA (currently unused) */
    ICAL_ASSUME_IANA_TOKEN = 1,
    /** discard and continue normally */
    ICAL_DISCARD_TOKEN = 2,
    /** treat as a error; the internal icalerror to :ICAL_MALFORMEDDATA_ERROR */
    ICAL_TREAT_AS_ERROR = 3
} ical_unknown_token_handling;

/**
 * Gets how the library handles unknown tokens.
 *
 * The default library setting is ::ICAL_TREAT_AS_ERROR.
 *
 * @return the library's current ical_unknown_token_handling setting.
 * @see ical_set_unknown_token_handling_setting
 */
LIBICAL_ICAL_EXPORT ical_unknown_token_handling ical_get_unknown_token_handling_setting(void);

/**
 * Sets how the library handles unknown tokens.
 *
 * @param newSetting is the ical_unknown_token_handling to use
 *
 * @see ical_get_unknown_token_handling_setting
 */
LIBICAL_ICAL_EXPORT void ical_set_unknown_token_handling_setting(
    ical_unknown_token_handling newSetting);

#endif /* !ICALTYPES_H */

/*======================================================================
 FILE: icalarray.h
 CREATOR: Damon Chaplin 07 March 2001

 SPDX-FileCopyrightText: 2001, Ximian, Inc.
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalarray.h
 *
 * @brief An array of arbitrarily-sized elements which grows
 * dynamically as elements are added.
 */

#ifndef ICALARRAY_H
#define ICALARRAY_H

#include "libical_ical_export.h"

#include <stddef.h>

/// @cond PRIVATE
/**
 * A struct representing an icalarray object.
 */
typedef struct _icalarray icalarray;
struct _icalarray {
    size_t element_size;
    size_t increment_size;
    size_t num_elements;
    size_t space_allocated;
    void **chunks;
};
/// @endcond

/**
 * Creates a new icalarray object.
 *
 * @param element_size The size of the elements to be held by the array
 * @param increment_size How many extra elements worth of space to allocate on expansion
 * @return The new icalarray object
 * @sa icalarray_free()
 *
 * Creates a new icalarray object. The parameter @a element_size determines
 * the size of the elements that the array will hold (in bytes). The parameter
 * @a increment_size determines how many extra elements to be allocated when
 * expanding the array for performance reasons (expansions are expensive, since
 * it involves copying all existing elements). If increment_size is zero, then
 * the default increment size specified during libical build time is chosen.
 *
 * @par Error handling
 * If @a element_size is not at least 1, using the icalarray object results in
 * undefined behaviour. If there is an error while creating the
 * object, it returns `NULL` and sets ::icalerrno to ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * The returned icalarray object is owned by the caller of the function,
 * and needs to be released properly after it's no longer needed with
 * icalarray_free().
 *
 * @par Usage
 * ```c
 * // create new array
 * icalarray *array = icalarray_new(sizeof(int), 1);
 *
 * // use array
 * int a = 4;
 * icalarray_append(array, &a);
 * assert(*icalarray_element_at(array, 0) == a);
 *
 * // release memory
 * icalarray_free(array);
 * ```
 */
LIBICAL_ICAL_EXPORT icalarray *icalarray_new(size_t element_size, size_t increment_size);

/**
 * Copies an existing icalarray and its elements, creating a new one.
 *
 * @param array The array to copy
 * @return A new array, holding all the elements of @a array
 *
 * Creates a new icalarray object, copying all the existing elements from
 * @a array as well as its properties (such as @a element_size and
 * @a increment_size) over.
 *
 * @par Error handling
 * If @a array is `NULL`, this method will return `NULL`. If there was an error
 * allocating memory while creating the copy, it will set ::icalerrno
 * to ::ICAL_ALLOCATION_ERROR.
 *
 * @par Ownership
 * The created copy is owned by the caller of the function, and needs to
 * be released with icalarray_free() after it's no longer being used.
 *
 * @par Usage
 * ```c
 * // create new array
 * icalarray *array = icalarray_new(sizeof(int), 1);
 *
 * // fill array
 * int a = 4;
 * icalarray_append(array, &a);
 *
 * // create copy of array
 * icalarray *copy = icalarray_copy(array);
 * assert(*icalarray_element_at(copy, 0) == a);
 *
 * // release arrays
 * icalarray_free(array);
 * icalarray_free(copy);
 * ```
 */
LIBICAL_ICAL_EXPORT icalarray *icalarray_copy(const icalarray *array);

/**
 * Frees an array object and everything that it contains.
 *
 * @param array The array to release
 *
 * @par Example
 * ```c
 * // creating an array
 * icalarray *array = icalarray_new(sizeof(int), 1);
 *
 * // releasing it
 * icalarray_free(array);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalarray_free(icalarray *array);

/**
 * @brief Appends an element to an array.
 * @param array The array to append the element to
 * @param element The element to append
 *
 * Appends the given @a element to the @a array, reallocating
 * and expanding the array as needed.
 *
 * @par Error handling
 * If @a array or @a element is `NULL`, using this function results
 * in undefined behaviour (most likely a segfault).
 *
 * @par Ownership
 * The @a element does not get consumed by the method, since it creates
 * a copy of it
 *
 * @par Usage
 * ```c
 * // create new array
 * icalarray *array = icalarray_new(sizeof(int), 1);
 *
 * // append data to it
 * int data = 42;
 * icalarray_append(array, &data);
 *
 * // release array
 * icalarray_free(array);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalarray_append(icalarray *array, const void *element);

/**
 * @brief Removes a given element from an array.
 * @param array The array from which to remove the element
 * @param position The position of the element to remove
 *
 * Removes the element at the given position from the array.
 *
 * @par Error handling
 * If @a array is `NULL`, using this function results in undefined behaviour.
 * If the array is empty, using this function results in undefined behaviour.
 * If the @a position is non-existent, it removes the last element.
 *
 * @par Usage
 * ```c
 * // create new array
 * icalarray *array = icalarray_new(sizeof(int), 2);
 *
 * // fill array
 * int data;
 * data = 4;
 * icalarray_append(array, &a);
 * data = 9;
 * icalarray_append(array, &a);
 * data = 7;
 * icalarray_append(array, &a);
 * data = 10;
 * icalarray_append(array, &a);
 *
 * // check array
 * assert(*icalarray_element_at(array, 0) == 4);
 * assert(*icalarray_element_at(array, 1) == 9);
 * assert(*icalarray_element_at(array, 2) == 7);
 * assert(*icalarray_element_at(array, 3) == 10);
 *
 * // remove the second element
 * icalarray_remove_element_at(array, 1);
 *
 * // check array
 * assert(*icalarray_element_at(array, 0) == 4);
 * assert(*icalarray_element_at(array, 1) == 7);
 * assert(*icalarray_element_at(array, 2) == 10);
 *
 * // release array
 * icalarray_free(array);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalarray_remove_element_at(icalarray *array, size_t position);

/**
 * @brief Access an array element
 * @param array The array object in which the element is stored
 * @param position The position of the element to access in the array
 * @return A pointer to the element inside the array
 *
 * Accesses an array element by returning a pointer to it, given an
 * @a array and a valid element @a position.
 *
 * @par Error handling
 * If @a array is `NULL`, using this function results in undefined behaviour.
 * If @a position is not a valid position in the array, using this function
 * results in undefined behaviour.
 *
 * @par Ownership
 * The element is owned by the icalarray, it must not be freed by
 * the user.
 *
 * @par Usage
 * ```c
 * // create new array
 * icalarray *array = icalarray_new(sizeof(int), 1);
 *
 * // fill array
 * int a = 4;
 * icalarray_append(array, &a);
 *
 * // access array element
 * int *element = icalarray_element_at(array, 0);
 * assert(element != NULL);
 * assert(*element == a);
 *
 * // change array element
 * *element = 14;
 * assert(*icalarray_element(array) == 14);
 *
 * // release memory
 * icalarray_free(array);
 * ```
 */
LIBICAL_ICAL_EXPORT void *icalarray_element_at(icalarray *array, size_t position);

/**
 * @brief Overwrites an existing element in an array with a new value.
 * @param array The array to overwrite the element in
 * @param element The element to set as the new value
 * @param position The position of the element to overwrite
 *
 * Sets the given @a element at the @a position in the @a array,
 * overwriting the current element at that position.
 *
 * @par Error handling
 * If @a array or @a element is `NULL` or @a position is higher than
 * the last position in the array, using this function results
 * in undefined behaviour (most likely a segfault).
 *
 * @par Ownership
 * The @a element does not get consumed by the method, since it creates
 * a copy of it. The existing element gets overwritten, callers are
 * responsible to free any heap-allocated values of the element.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalarray_set_element_at(icalarray *array, const void *element, size_t position);

/**
 * @brief Sorts the elements of an icalarray using the given comparison function.
 * @param array The array to sort
 * @param compare The comparison function to use
 *
 * @par Error handling
 * Passing `NULL` as either @a array or @a compare results in undefined
 * behaviour.
 *
 * @par Usage
 * ```c
 * int compare_ints(const void *a, const void *b) {
 *     return *((int*)a) - *((int*)b);
 * }
 *
 * int main(int argc, char *argv[]) {
 *     int numbers[] = {5, 2, 7, 4, 3, 1, 0, 8, 6, 9};
 *
 *     icalarray *array = icalarray_new(sizeof(int), 3);
 *
 *     // fill array
 *     for(int i = 0; i < 10; i++) {
 *         icalarray_append(array, &numbers[i]);
 *     }
 *
 *     // sort array
 *     icalarray_sort(array, compare_ints);
 *
 *     // print numbers
 *     for(int i = 0; i < 10; i++) {
 *         printf("%i\n", *((int*)icalarray_element_at(array, i)));
 *     }
 *
 *     return 0;
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT void icalarray_sort(icalarray *array,
                                        int (*compare)(const void *, const void *));

#endif /* ICALARRAY_H */

/*======================================================================
 FILE: icalenumarray.h
 CREATOR: Ken Murchison 24 Aug 2022 <murch@fastmailteam.com>

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 ======================================================================*/

/**
 * @file icalenumarray.h
 * @brief Defines the data structure for handling arrays of enums.
 */

#ifndef ICALENUMARRAY_H
#define ICALENUMARRAY_H

#include "libical_ical_export.h"


#include <stdlib.h>

/// @cond PRIVATE
/* An icalenumarray is just an icalarray in disguise. */
typedef icalarray icalenumarray;
/// @endcond

/**
 * A data structure to hold an enum array element
 */
typedef struct {
    int val;            /**< the enum value */
    const char *xvalue; /**< pointer to the associated optional X value */
} icalenumarray_element;

/**
 * Creates a new icalenumarray object.
 *
 * @param increment_size How many slots to allocate on array expansion
 * @return The new icalenumarray object
 * @sa icalenumarray_free()
 *
 * Creates a new icalenumarray object. The parameter @a increment_size determines
 * how many slots to allocate when expanding the array. If zero, then the
 * default increment size specified when libical was built is chosen.
 *
 * @par Error handling
 * If there is an error while creating the object, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * The returned icalenumarray object is owned by the caller of the function,
 * and needs to be released properly after it's no longer needed with
 * icalenumarray_free().
 *
 */
#define icalenumarray_new(increment_size) \
    icalarray_new(sizeof(icalenumarray_element), increment_size)

/**
 * @brief Accesses an element stored in the array.
 * @param array The array object in which the element is stored
 * @param position The slot position of the element in the array
 * @return A pointer to the element
 *
 * Accesses an element by returning a pointer to it, given an @a array and a
 * valid slot @a position.
 *
 * @par Error handling
 * If @a array is `NULL` or @a position is not set in the array, then the
 * return value is `NULL`.
 *
 * @par Ownership
 * The element is owned by the icalenumarray, it must not be freed by
 * the user.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT const icalenumarray_element *icalenumarray_element_at(icalenumarray *array, size_t position);

/**
 * @brief Indicates the count of elements stored in the array.
 * @param array The array object in which the element is stored
 * @return the count of elements
 *
 * Returns the count of elements stored in the @a array.
 *
 * @par Error handling
 * If @a array is `NULL` then the return value is zero.
 *
 * @since 4.0
 *
 */
LIBICAL_ICAL_EXPORT size_t icalenumarray_size(const icalenumarray *array);

/**
 * @brief Finds an element in the array.
 * @param array The array object in which to search for the element
 * @param needle The element to search for
 * @return the slot position of the element in the array, or icalenumarray_size()
 *
 * Looks for element @a needle in the @a array, comparing the numeric value for
 * equality and the optional xvalue for byte-equality. The position of the first
 * occurrence is returned if the element is found. If the element is not found,
 * then the count of elements in the array is returned.
 *
 * @par Error handling
 * If @a array or @a needle is `NULL`, then the return value is the same
 * as if the value is not found.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT size_t icalenumarray_find(icalenumarray *array,
                                              const icalenumarray_element *needle);

/**
 * @brief Appends an element to the array.
 * @param array The array object to which the element append to
 * @param elem The element to append
 *
 * Appends element @p elem to @a array, not checking for duplicates.
 * Use icalenumarray_add() to only add elements that are not present
 * already in the array.
 *
 * @par Error handling
 * If @a array or @a elem is `NULL` then this function is a noop.
 *
 * @since 4.0
 *
 */
LIBICAL_ICAL_EXPORT void icalenumarray_append(icalenumarray *array,
                                              const icalenumarray_element *elem);

/**
 * @brief Appends an element to the array, omitting duplicates.
 * @param array The array object to which the element append to
 * @param elem The element to append
 *
 * Appends element @p elem to @a array unless a byte-equal string
 * already is present in the array.
 *
 * @par Error handling
 * If @a array or @a elem is `NULL` then this function is a noop.
 *
 * @since 4.0
 *
 */
LIBICAL_ICAL_EXPORT void icalenumarray_add(icalenumarray *array,
                                           const icalenumarray_element *elem);

/**
 * @brief Removes the element at an array position.
 * @param array The array object from which to remove the element
 * @param position The array position of the element to remove
 *
 * Removes the element at @a position in the @a array.
 *
 * @par Error handling
 * If @a array is `NULL` or @a position is higher or equal to the
 * count of elements, this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalenumarray_remove_element_at(icalenumarray *array,
                                                         size_t position);

/**
 * @brief Removes all occurrences of an element.
 * @param array The array object from which to remove the element
 * @param del The element to remove from the array
 *
 * Removes all occurrences of the element @a del from @a array.
 *
 * @par Error handling
 * If @a array or @a del is `NULL`, then this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalenumarray_remove(icalenumarray *array,
                                              const icalenumarray_element *del);

/**
 * @brief Frees this array's memory and all its elements.
 * @param array The array object to free
 *
 * Frees the array.
 *
 * @par Error handling
 * If @a array is `NULL`, this is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalenumarray_free(icalenumarray *array);

/**
 * @brief Sorts the elements in the array in ascending order.
 * @param array The array object to sort.
 *
 * Sorts the array such that all element elements occur in
 * ascending order, comparing the elements as bytes.
 *
 * @par Error handling
 * If @a array is `NULL`, this is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalenumarray_sort(icalenumarray *array);

/**
 * @brief Clones the array and all its elements.
 * @param array The array object to clone.
 * @return the cloned array
 *
 * Creates an independent copy of the @a array and all its elements.
 *
 * @par Error handling
 * If @a array is `NULL` then the return value is `NULL`.
 *
 * @since 4.0
 *
 */
LIBICAL_ICAL_EXPORT icalenumarray *icalenumarray_clone(icalenumarray *array);

#endif /* ICALENUMARRAY_H */

/*======================================================================
 FILE: icalstrarray.h
 CREATOR: Ken Murchison 24 Aug 2022

 SPDX-FileCopyrightText: 2022, Fastmail Pty. Ltd. (https://fastmail.com)
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 ======================================================================*/

/**
 * @file icalstrarray.h
 * @brief Defines the data structure for handling string arrays.
 */

#ifndef ICALSTRARRAY_H
#define ICALSTRARRAY_H

#include "libical_ical_export.h"


#include <stdlib.h>

/// @cond PRIVATE
/* An icalstrarray is just an icalarray in disguise. */
typedef icalarray icalstrarray;
/// @endcond

/**
 * @brief Creates a new icalstrarray object.
 * @param increment_size How many slots to allocate on array expansion
 * @return The new icalstrarray object
 * @sa icalstrarray_free()
 *
 * Creates a new icalstrarray object. The parameter @a increment_size determines
 * how many slots to allocate when expanding the array. If zero, then the
 * default increment size specified when libical was built is chosen.
 *
 * @par Error handling
 * If there is an error while creating the object, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * The returned icalstrarray object is owned by the caller of the function,
 * and needs to be released properly after it's no longer needed with
 * icalstrarray_free().
 *
 */
#define icalstrarray_new(increment_size) \
    (icalarray_new(sizeof(char *), increment_size))

/**
 * @brief Accesses a string stored in the array.
 * @param array The array object in which the string is stored
 * @param position The slot position of the string in the array
 * @return A pointer to the string
 *
 * Accesses a string by returning a pointer to it, given an @a array and a
 * valid slot @a position.
 *
 * @par Error handling
 * If @a array is `NULL` or @a position is not set in the array, then the
 * return value is `NULL`.
 *
 * @par Ownership
 * The string is owned by the icalstrarray, it must not be freed by
 * the user.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT const char *icalstrarray_element_at(icalstrarray *array, size_t position);

/**
 * @brief Indicates the count of strings stored in the array.
 * @param array The array object in which the string is stored
 * @return the count of strings
 *
 * Returns the count of strings stored in the @a array.
 *
 * @par Error handling
 * If @a array is `NULL` then the return value is zero.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT size_t icalstrarray_size(const icalstrarray *array);

/**
 * @brief Finds a string in the array.
 * @param array The array object in which to search for the string
 * @param needle The string to search for
 * @return the slot position of the string in the array, or icalstrarray_size()
 *
 * Looks for string @a needle in the @a array, comparing strings for
 * byte-equality. The position of the first occurrence is returned if
 * the string is found. If the string is not found, then the count of
 * elements in the array is returned.
 *
 * @par Error handling
 * If @a array or @a needle is `NULL`, then the return value is the same
 * as if the value is not found.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT size_t icalstrarray_find(icalstrarray *array,
                                             const char *needle);

/**
 * @brief Appends a string to the array.
 * @param array The array object to which the string append to
 * @param elem The string to append
 *
 * Appends string @p elem to @a array, not checking for duplicates.
 * Use icalstrarray_add() to only add strings that are not present
 * already in the array.
 *
 * @par Error handling
 * If @a array or @a elem is `NULL` then this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_append(icalstrarray *array,
                                             const char *elem);

/**
 * @brief Appends a string to the array, omitting duplicates.
 * @param array The array object to which the string append to
 * @param elem The string to append
 *
 * Appends string @p elem to @a array unless a byte-equal string
 * already is present in the array.
 *
 * @par Error handling
 * If @a array or @a elem is `NULL` then this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_add(icalstrarray *array,
                                          const char *elem);

/**
 * @brief Removes the string at an array position.
 * @param array The array object from which to remove the string
 * @param position The array position of the string to remove
 *
 * Removes the string at @a position in the @a array.
 *
 * @par Error handling
 * If @a array is `NULL` or @a position is higher or equal to the
 * count of strings, this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_remove_element_at(icalstrarray *array,
                                                        size_t position);

/**
 * @brief Removes all occurrences of a string.
 * @param array The array object from which to remove the string
 * @param del The string to remove from the array
 *
 * Removes all occurrences of the string @a del from @a array.
 *
 * @par Error handling
 * If @a array or @a del is `NULL`, then this function is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_remove(icalstrarray *array,
                                             const char *del);

/**
 * @brief Frees this array's memory and all its elements.
 * @param array The array object to free
 *
 * Frees the array.
 *
 * @par Error handling
 * If @a array is `NULL`, this is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_free(icalstrarray *array);

/**
 * @brief Sorts the strings in the array in ascending order.
 * @param array The array object to sort.
 *
 * Sorts the array such that all string elements occur in
 * ascending order, comparing the strings as bytes.
 *
 * @par Error handling
 * If @a array is `NULL`, this is a noop.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalstrarray_sort(icalstrarray *array);

/**
 * @brief Clones the array and all its elements.
 * @param array The array object to clone.
 * @return the cloned array
 *
 * Creates an independent copy of the @a array and all its string
 * elements.
 *
 * @par Error handling
 * If @a array is `NULL` then the return value is `NULL`.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalstrarray *icalstrarray_clone(icalstrarray *array);

#endif /* ICALSTRARRAY_H */

/*======================================================================
 FILE: icalrecur.h
 CREATOR: eric 20 March 2000

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
========================================================================*/

/**
@file icalrecur.h
@brief Routines for dealing with recurring time

How to use:

1) Get a rule and a start time from a component

@code
        icalproperty rrule;
        struct icalrecurrencetype *recur;
        struct icaltimetype dtstart;

        rrule = icalcomponent_get_first_property(comp,ICAL_RRULE_PROPERTY);
        recur = icalproperty_get_rrule(rrule);
        start = icalproperty_get_dtstart(dtstart);
@endcode

Or, just make them up:

@code
        recur = icalrecurrencetype_new_from_string("FREQ=YEARLY;BYDAY=SU,WE");
        dtstart = icaltime_from_string("19970101T123000")
@endcode

2) Create an iterator

@code
        icalrecur_iterator *ritr;
        ritr = icalrecur_iterator_new(recur, start);
@endcode

3) Iterator over the occurrences

@code
        struct icaltimetype next;
        next = icalrecur_iterator_next(ritr);
        while (!icaltime_is_null_time(next)){
                // Do something with next
                next = icalrecur_iterator_next(ritr);
        }
@endcode

Note that the time returned by icalrecur_iterator_next is in
whatever timezone that dtstart is in.

4) Deallocate a rule

@code
        icalrecurrencetype_unref(recur);
@endcode

The icalrecurrencetype object is reference counted. It will automatically be deallocated when the
reference count goes to zero.
*/

#ifndef ICALRECUR_H
#define ICALRECUR_H

#include "libical_ical_export.h"


#include <stdbool.h>

/*
 * Recurrence enumerations
 */

/**
 * Recurrence frequencies.
 *
 * @note These enums are used to index an array, so don't change the
 * order or the integers
 */
typedef enum icalrecurrencetype_frequency
{
    ICAL_SECONDLY_RECURRENCE = 0, /**< recurs on the second */
    ICAL_MINUTELY_RECURRENCE = 1, /**< recurs on the minute */
    ICAL_HOURLY_RECURRENCE = 2,   /**< recurs on the hour */
    ICAL_DAILY_RECURRENCE = 3,    /**< recurs daily */
    ICAL_WEEKLY_RECURRENCE = 4,   /**< recurs weekly */
    ICAL_MONTHLY_RECURRENCE = 5,  /**< recurs monthly */
    ICAL_YEARLY_RECURRENCE = 6,   /**< recurs yearly */
    ICAL_NO_RECURRENCE = 7        /**< does not recur */
} icalrecurrencetype_frequency;

/**
 * Weekly recurrences days.
 */
typedef enum icalrecurrencetype_weekday
{
    ICAL_NO_WEEKDAY,        /**< does not recur on a weekday */
    ICAL_SUNDAY_WEEKDAY,    /**< recurs on Sunday */
    ICAL_MONDAY_WEEKDAY,    /**< recurs on Monday */
    ICAL_TUESDAY_WEEKDAY,   /**< recurs on Tuesday */
    ICAL_WEDNESDAY_WEEKDAY, /**< recurs on Wednesday */
    ICAL_THURSDAY_WEEKDAY,  /**< recurs on Thursday */
    ICAL_FRIDAY_WEEKDAY,    /**< recurs on Friday */
    ICAL_SATURDAY_WEEKDAY   /**< recurs on Saturday */
} icalrecurrencetype_weekday;

/**
 * Recurrence skip types.
 */
typedef enum icalrecurrencetype_skip
{
    ICAL_SKIP_BACKWARD = 0, /**< skip backward to the previous recurrence */
    ICAL_SKIP_FORWARD,      /**< skip forward to the next recurrence */
    ICAL_SKIP_OMIT,         /**< omit this recurrence */
    ICAL_SKIP_UNDEFINED     /**< recurrence skip type is not defined */
} icalrecurrencetype_skip;

/**
 * Recurrence byrule types.
 */
typedef enum icalrecurrencetype_byrule
{
    ICAL_BYRULE_NO_CONTRACTION = -1, /**< indicates the end of byrule */
    ICAL_BY_MONTH = 0,               /**< recur by months */
    ICAL_BY_WEEK_NO = 1,             /**< recur by weeks */
    ICAL_BY_YEAR_DAY = 2,            /**< recur by year days */
    ICAL_BY_MONTH_DAY = 3,           /**< recur by month days */
    ICAL_BY_DAY = 4,                 /**< recur by days */
    ICAL_BY_HOUR = 5,                /**< recur by hours */
    ICAL_BY_MINUTE = 6,              /**< recur by minutes */
    ICAL_BY_SECOND = 7,              /**< recur by seconds */
    ICAL_BY_SET_POS = 8,             /**< recur by a set position */

    ICAL_BY_NUM_PARTS = 9 /**< length of the bydata array */
} icalrecurrencetype_byrule;

/*
 * Recurrence enumerations conversion routines.
 */

/**
 * Converts a char string into a icalrecurrencetype_frequency.
 *
 * @param str a pointer to a char string containing the string representation of
 * an icalrecurrencetype_frequency.
 *
 * @return the icalrecurrencetype_frequency version of @p str.
 * If @p str is invalid then ::ICAL_NO_RECURRENCE is returned.
 *
 * @see icalrecur_freq_to_string
 */
LIBICAL_ICAL_EXPORT icalrecurrencetype_frequency icalrecur_string_to_freq(const char *str);

/**
 * Stringifies a icalrecurrencetype_frequency.
 *
 * @param kind a icalrecurrencetype_frequency to convert
 *
 * @return a pointer to char string version of @p kind.
 * If @p kind is invalid then NULL is returned.
 *
 * @see icalrecur_string_to_freq
 */
LIBICAL_ICAL_EXPORT const char *icalrecur_freq_to_string(icalrecurrencetype_frequency kind);

/**
 * Converts a char string into a icalrecurrencetype_skip.
 *
 * @param str a pointer t a char string containing the string representation of
 * an icalrecurrencetype_skip.
 *
 * @return the icalrecurrencetype_skip version of @p str.
 * If @p str is invalid then ::ICAL_SKIP_UNDEFINED is returned.
 *
 * @see icalrecur_skip_to_string
 */
LIBICAL_ICAL_EXPORT icalrecurrencetype_skip icalrecur_string_to_skip(const char *str);

/**
 * Stringifies a icalrecurrencetype_skip.
 *
 * @param kind a icalrecurrencetype_skip to convert
 *
 * @return a pointer to char string version of @p kind.
 * If @p kind is invalid then NULL is returned.
 *
 * @see icalrecur_string_to_skip
 */
LIBICAL_ICAL_EXPORT const char *icalrecur_skip_to_string(icalrecurrencetype_skip kind);

/**
 * Stringifies a icalrecurrencetype_weekday.
 *
 * @param kind a icalrecurrencetype_weekday to convert
 *
 * @return a pointer to char string version of @p kind.
 * If @p kind is invalid then NULL is returned.
 *
 * @see icalrecur_string_to_weekday
 */
LIBICAL_ICAL_EXPORT const char *icalrecur_weekday_to_string(icalrecurrencetype_weekday kind);

/**
 * Converts a char string into a icalrecurrencetype_weekday.
 *
 * @param str a pointer to a char string containing the string representation
 * of a icalrecurrencetype_weekday
 *
 * @return the icalrecurrencetype_weekday version of @p str.
 * If @p str is invalid then :: ICAL_NO_WEEKDAY is returned.
 *
 * @see icalrecur_weekday_to_string
 */
LIBICAL_ICAL_EXPORT icalrecurrencetype_weekday icalrecur_string_to_weekday(const char *str);

/**
 * Recurrence type routines
 */

//@cond PRIVATE
/* See RFC 5545 Section 3.3.10, RECUR Value, and RFC 7529
 * for an explanation of the values and fields in struct icalrecurrencetype.
 *
 * The maximums below are based on lunisolar leap years (13 months)
 */
#define ICAL_BY_SECOND_SIZE 62                               /* 0 to 60 */
#define ICAL_BY_MINUTE_SIZE 61                               /* 0 to 59 */
#define ICAL_BY_HOUR_SIZE 25                                 /* 0 to 23 */
#define ICAL_BY_MONTH_SIZE 14                                /* 1 to 13 */
#define ICAL_BY_MONTHDAY_SIZE 32                             /* 1 to 31 */
#define ICAL_BY_WEEKNO_SIZE 56                               /* 1 to 55 */
#define ICAL_BY_YEARDAY_SIZE 386                             /* 1 to 385 */
#define ICAL_BY_SETPOS_SIZE ICAL_BY_YEARDAY_SIZE             /* 1 to N */
#define ICAL_BY_DAY_SIZE (7 * (ICAL_BY_WEEKNO_SIZE - 1) + 1) /* 1 to N */

typedef struct {
    short *data;
    short size;
} icalrecurrence_by_data;
//@endcond

/**
 * Data structure for holding digested recurrence rules.
 * @note ::until and ::count are mutually exclusive.
 */
struct icalrecurrencetype {
    /** Reference count */
    int refcount;

    /** the frequency of the recurrence */
    icalrecurrencetype_frequency freq;

    /** recur until this date-time, mutually exclusive with ::count */
    struct icaltimetype until;

    /** number of times to recur, mutually exclusive with ::until */
    int count;

    /** interval between recurrences */
    short interval;

    /** week day start, for weekday recurrences */
    icalrecurrencetype_weekday week_start;

    /**
     * Encoded value
     *
     * The 'day' element of the ICAL_BY_DAY array is encoded to allow
     * representation of both the day of the week ( Monday, Tuesday), but
     * also the Nth day of the week (first Tuesday of the month, last
     * Thursday of the year).
     *
     * These values are decoded by icalrecurrencetype_day_day_of_week() and
     * icalrecurrencetype_day_position().
     *
     * The 'month' element of the ICAL_BY_MONTH array is encoded to allow
     * representation of the "L" leap suffix (RFC 7529).
     *
     * These values are decoded by icalrecurrencetype_month_is_leap()
     * and icalrecurrencetype_month_month().
     */
    icalrecurrence_by_data by[ICAL_BY_NUM_PARTS];

    /** For RSCALE extension (RFC 7529) */
    char *rscale;

    /** recurrence skip (forward, backward, omit) */
    icalrecurrencetype_skip skip;
};

/**
 * Constructs a new instance of icalrecurrencetype.
 *
 * The new instance is initialized with a refcount of 1.
 *
 * @return A pointer to the new instance, or NULL if memory allocation failed.
 */
LIBICAL_ICAL_EXPORT struct icalrecurrencetype *icalrecurrencetype_new(void);

/**
 * Increases the icalrecurrencetype reference counter by 1.
 *
 * @param recur is a pointer to a valid icalrecurrencetype
 */
LIBICAL_ICAL_EXPORT void icalrecurrencetype_ref(struct icalrecurrencetype *recur);

/**
 * Decreases the icalrecurrencetype reference counter by 1.
 *
 * If the counter reaches 0, the instance  and all referenced memory
 * (i.e. rscale and 'by' arrays) are deallocated.
 *
 * @param recur a pointer to a valid icalrecurrencetype
 */
LIBICAL_ICAL_EXPORT void icalrecurrencetype_unref(struct icalrecurrencetype *recur);

/**
 * Return an array of RSCALE supported calendars.
 *
 * @return a pointer to an icalarray of a list of RSCALE supported calendars.
 * Currently returns list containing "GREGORIAN" only.
 */
LIBICAL_ICAL_EXPORT icalarray *icalrecurrencetype_rscale_supported_calendars(void);

/**
 * Creates a deep copy of the given icalrecurrencetype.
 *
 * The new instance is returned with a refcount of 1.
 *
 * @param r is a pointer to a valid icalrecurrencetype
 *
 * @return a pointer to the cloned memory.
 */
LIBICAL_ICAL_EXPORT struct icalrecurrencetype *icalrecurrencetype_clone(struct icalrecurrencetype *r);

/**
 * Resizes the buffer backing the 'by' array to the specified size, if different.
 *
 * Frees the buffer if the new size is 0.
 *
 * @param by is a pointer to valid icalrecurrence_by_data to use
 * @param size is the new size for the array
 *
 * @return true on success, false on failure.
 */
LIBICAL_ICAL_EXPORT bool icalrecur_resize_by(icalrecurrence_by_data *by, short size);

/*
 * Routines to decode the day values of the by[ICAL_BY_DAY] array
 */

/**
 * Decode the weekday from a "weekday:pos" form.
 *
 * @param day is the "weekday:pos" to decode (as created by icalrecurrencetype_encode_day())
 *
 * @returns The decoded day of the week from the "weekday:pos".
 * 1 is Monday, 2 is Tuesday, etc.
 *
 * @see icalrecurrencetype_encode_day and icalrecurrencetype_day_position().
 */
LIBICAL_ICAL_EXPORT enum icalrecurrencetype_weekday icalrecurrencetype_day_day_of_week(short day);

/**
 * Decodes a the position from a "weekday:pos" form.
 *
 * @param day is the "weekday:pos" to decode (as created by icalrecurrencetype_encode_day()).
 *
 * @return The position of the day in the week, where:
 * 0 == any of day of week. 1 == first, 2 = second, -2 == second to last, etc.
 * 0 means 'any' or 'every'.
 */
LIBICAL_ICAL_EXPORT int icalrecurrencetype_day_position(short day);

/**
 * Encode a weekday and position into a form which can be stored into a
 * `icalrecurrencetype::by[ICAL_BY_DAY]` array.
 *
 * The 'day' element of icalrecurrencetype_weekday is encoded to
 * allow representation of both the day of the week ( Monday, Tuesday),
 * but also the Nth day of the week (First tuesday of the month, last
 * thursday of the year) These routines decode the day values.
 *
 * The day's position in the period (Nth-ness) and the numerical
 * value of the day are encoded together as: pos*7 + dow.
 *
 * A position of 0 means 'any' or 'every'.
 *
 * Use icalrecurrencetype_day_day_of_week() and icalrecurrencetype_day_position()
 * to split the encoded value back into the parts.
 *
 * @param weekday is the weekday to use
 * @param position is the positiog to use
 *
 * @return the encoded "weekday:pos", which can later be decoded back using
 * icalrecurrencetype_day_day_of_week() and icalrecurrencetype_day_position().
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT short icalrecurrencetype_encode_day(enum icalrecurrencetype_weekday weekday,
                                                        int position);

/**
 * Decode the is_leap from a month:leap_year form.
 *
 * @param month is the month:leap_year to decode (as created by icalrecurrencetype_encode_month())
 *
 * @return the is_leap portion of the month:leap_year
 *
 * @see icalrecurrencetype_encode_month, icalrecurrencetype_month_month
 */
LIBICAL_ICAL_EXPORT bool icalrecurrencetype_month_is_leap(short month);

/**
 * Decode the month from a month:leap_year form.
 *
 * @param month is the month:leap_year to decode (as created by icalrecurrencetype_encode_month())
 *
 * @return the month portion of the month:leap_year
 *
 * @see icalrecurrencetype_encode_month, icalrecurrencetype_month_is_leap
 */
LIBICAL_ICAL_EXPORT int icalrecurrencetype_month_month(short month);

/**
 * Encodes a month and leap year indicator into a form which can be stored
 * into a `icalrecurrencetype::by[ICAL_BY_MONTH]` array.
 *
 * The month element of the `by[ICAL_BY_MONTH]` array is encoded to allow
 * representation of the "L" leap suffix (RFC 7529).
 * The "L" suffix is encoded by setting a high-order bit.
 *
 * Use icalrecurrencetype_month_is_leap() and icalrecurrencetype_month_month()
 * to split the encoded value back into the parts.
 *
 * @param month is the month to use (1-12)
 * @param is_leap is a bool indicating if leap year is to be considered
 *
 * @return the encoded "month:leap_year", which can later be decoded back using
 * icalrecurrencetype_month_is_leap() and icalrecurrencetype_month_month().
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT short icalrecurrencetype_encode_month(int month, bool is_leap);

/*
 * Recurrence rule parser
 */

/**
 * Create a new icalrecurrencetype from a string.
 *
 * @param str a pointer to a char string containing string version of the recurrence.
 *
 * @return a pointer to the new icalrecurrencetype or NULL if the string
 * contained an invalid representation.
 */
LIBICAL_ICAL_EXPORT struct icalrecurrencetype *icalrecurrencetype_new_from_string(const char *str);

/**
 * Represent an icalrecurrencetype as a string.
 *
 * @param recur a pointer to a valid icalrecurrencetype
 *
 * @return a pointer to a char string containing the string representation
 * of @p recur. Returns NULL if the conversion was unsuccessful.
 *
 * @see icalrecurrencetype_as_string_r
 */
LIBICAL_ICAL_EXPORT char *icalrecurrencetype_as_string(struct icalrecurrencetype *recur);

/**
 * Represent an icalrecurrencetype as a string.
 *
 * @param recur a pointer to a valid icalrecurrencetype
 *
 * @return a pointer to a char string containing the string representation
 * of @p recur. Returns NULL if the conversion was unsuccessful.
 *
 * @see icalrecurrencetype_as_string
 */
LIBICAL_ICAL_EXPORT char *icalrecurrencetype_as_string_r(struct icalrecurrencetype *recur);

/*
 * Recurrence iteration routines
 */

typedef struct icalrecur_iterator_impl icalrecur_iterator;

/**
 * Creates a new recurrence rule iterator starting at DTSTART.
 *
 * @param rule a pointer to a valid icalrecurrencetype
 * @param dtstart a valid icaltimetype to use for the DTSART
 *
 * @note The new iterator may keep a reference to the passed rule.
 * It must not be modified as long as the iterator is in use.
 *
 * @return a pointer to the new icalrecur_iterator.
 */
LIBICAL_ICAL_EXPORT icalrecur_iterator *icalrecur_iterator_new(struct icalrecurrencetype *rule,
                                                               struct icaltimetype dtstart);

/**
 * Sets the date-time at which the iterator will start,
 *
 * @note CAN NOT be used with RRULEs that contain COUNT.
 *
 * @param impl is a pointer to a valid icalrecur_iterator
 * @param start is the starting icaltimetype that must be between DTSTART and UNTIL.
 *
 * @return if the start was successfully set; false otherwise.
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT bool icalrecur_iterator_set_start(icalrecur_iterator *impl,
                                                      struct icaltimetype start);

/**
 * Sets the date-time at which the iterator will stop at the latest.
 *
 * @param impl is a pointer to a valid icalrecur_iterator
 * @param end is the ending icaltimetype
 *
 * Values equal to or greater than end will not be returned by the iterator.
 *
 * @return if the end was successfully set; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalrecur_iterator_set_end(icalrecur_iterator *impl,
                                                    struct icaltimetype end);

/**
 * Sets the date-times over which the iterator will run,
 *
 * @param impl is a pointer to a valid icalrecur_iterator
 * @param to is the starting icaltimetype
 * @param from is the ending icaltimetype that must be between DSTART and UNTIL
 *
 * If @p to is null time, the forward iterator will return values
 * up to and including UNTIL (if present), otherwise up to the year 2582.
 *
 * if @p to is non-null time and later than @p from,
 * the forward iterator will return values up to and including 'to'.
 *
 * If @p to is non-null time and earlier than @p from,
 * the reverse iterator will be set to start at @p from
 * and will return values down to and including @p to.
 *
 * NOTE: CAN NOT be used with RRULEs that contain COUNT.
 *
 * @return true if the range was successfully set; false otherwise.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT bool icalrecur_iterator_set_range(icalrecur_iterator *impl,
                                                      struct icaltimetype from,
                                                      struct icaltimetype to);

/**
 * Gets the next occurrence from an icalrecur_iterator.
 *
 * @param impl a pointer to a valid icalrecur_iterator
 *
 * @return an icaltimetype for the next occurrence.
 *
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalrecur_iterator_next(icalrecur_iterator *);

/**
 * Gets the previous occurrence from an icalrecur_iterator.
 *
 * @param impl a pointer to a valid icalrecur_iterator
 *
 * @return an icaltimetype for the previous occurrence.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalrecur_iterator_prev(icalrecur_iterator *impl);

/**
 * Frees the specified icalrecur_iterator.
 *
 * @param impl a pointer to a valid icalrecur_iterator
 */
LIBICAL_ICAL_EXPORT void icalrecur_iterator_free(icalrecur_iterator *impl);

/**
 * Fills an array with the 'count' number of occurrences generated by the rrule.
 *
 * Specifically, this fills an array up with at most 'count' icaltime_t values,
 * each representing an occurrence time in seconds past the POSIX epoch.
 *
 * @note The times are returned in UTC, but the times are calculated in
 * local time. You will have to convert the results back into local time
 * before using them.
 *
 * @param rule a pointer to a char string containing the RRULE to use
 * @param start a valid starting date-time
 * @param count the length of the provided icalarray
 * @param array a pointer to an array of @p count icaltime_t values
 * resulting from expanding the specified RRULE @p rule.
 *
 * @return true if the @p rule could be converted to a string; false otherwise.
 *
 */
LIBICAL_ICAL_EXPORT bool icalrecur_expand_recurrence(const char *rule, icaltime_t start,
                                                     int count, icaltime_t *array);

/**
 * How the library handles  RRULEs with invalid BYxxx part combos.
 */
typedef enum ical_invalid_rrule_handling
{
    /** treat as a error; the internal icalerror to :ICAL_MALFORMEDDATA_ERROR */
    ICAL_RRULE_TREAT_AS_ERROR = 0,
    /** discard and continue normally */
    ICAL_RRULE_IGNORE_INVALID = 1
} ical_invalid_rrule_handling;

/**
 * Gets how the library should handle invalid RRULEs.
 *
 * The default library setting is ::ICAL_RRULE_TREAT_AS_ERROR.
 *
 * @return the library's current cal_invalid_rrule_handling setting.
 * @see ical_set_invalid_rrule_handling_setting
 */
LIBICAL_ICAL_EXPORT ical_invalid_rrule_handling ical_get_invalid_rrule_handling_setting(void);

/**
 * Sets how the library should handle invalid RRULEs.
 *
 * @param newSetting the ical_invalid_rrule_handling to use.
 * @see ical_get_invalid_rrule_handling_setting
 */
LIBICAL_ICAL_EXPORT void ical_set_invalid_rrule_handling_setting(
    ical_invalid_rrule_handling newSetting);

#endif /* ICALRECUR_H */

/*======================================================================
 FILE: icalattach.h
 CREATOR: acampi 28 May 02

 SPDX-FileCopyrightText: 2002, Andrea Campi <a.campi@inet.it>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalattach.h
 * @brief Defines the data structure for iCalendar attachments.
 *
 * With the `ATTACH` property, the iCal standard defines a way to
 * associate a document object with a calendar component.
 *
 * These are represented with icalattach objects in libical.
 * This file contains functions to create and work with these
 * objects.
 */

#ifndef ICALATTACH_H
#define ICALATTACH_H

#include "libical_ical_export.h"

#include <stdbool.h>

/**
 * @typedef icalattach
 * @brief An iCal attach object representing a link to a document object.
 *
 * Represents an association with a document object. icalattach objects
 * are reference counted, meaning that if the last reference to them is
 * removed (with icalattach_unref()), they are destroyed.
 */
typedef struct icalattach_impl icalattach;

/**
 * @typedef icalattach_free_fn_t
 * Function to be called to free the data of an ::icalattach object.
 * @warning Currently not used
 *
 * This function type is used to free the data from an ::icalattach object created
 * with icalattach_new_from_data().
 */
typedef void (*icalattach_free_fn_t)(char *data, void *user_data);

/**
 * @brief Creates new icalattach object from a URL.
 * @param url The URL to create the object from
 * @return An icalattach object with the given URL as association
 * @sa icalattach_unref()
 *
 * @par Error handling
 * If @a url is `NULL`, it returns `NULL` and sets ::icalerrno to
 * ::ICAL_BADARG_ERROR. If there was an error allocating memory, it
 * returns `NULL` and sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The returned icalattach object is owned by the caller of the function.
 * icalattach objects are reference counted, which means that after
 * use, icalattach_unref() needs to be called to signal that they are
 * not used anymore.
 *
 * @par Usage
 * ```c
 * // creates new
 * icalattach *attach = icalattach_new_from_url("http://example.com");
 *
 * // checks it
 * assert(icalattach_get_is_url(attach));
 * assert(0 == strcmp(icalattach_get_url(attach), "http://example.com"));
 *
 * // release it
 * icalattach_unref(attach);
 * ```
 */
LIBICAL_ICAL_EXPORT icalattach *icalattach_new_from_url(const char *url);

/**
 * @brief Creates new icalattach object from data.
 * @param data The data to create the icalattach from
 * @param free_fn The function to free the data
 * @param free_fn_data Data to pass to the @a free_fn
 * @return An icalattach object with the given data
 * @sa icalattach_unref()
 *
 * @par Error handling
 * If @a url is `NULL`, it returns `NULL` and sets ::icalerrno to
 * ::ICAL_BADARG_ERROR. If there was an error allocating memory, it
 * returns `NULL` and sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The returned icalattach object is owned by the caller of the function.
 * icalattach objects are reference counted, which means that after
 * use, icalattach_unref() needs to be called to signal that they are
 * not used anymore.
 */
LIBICAL_ICAL_EXPORT icalattach *icalattach_new_from_data(const char *data,
                                                         icalattach_free_fn_t free_fn,
                                                         void *free_fn_data);

/**
 * @brief Increments reference count of the icalattach.
 * @param attach The object to increase the reference count of
 * @sa icalattach_unref()
 *
 * @par Error handling
 * If @a attach is `NULL`, or the reference count is smaller than 0,
 * it sets ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * By increasing the refcount of @a attach, you are signaling that
 * you are using it, and it is the owner's responsibility to call
 * icalattach_unref() after it's no longer used.
 */
LIBICAL_ICAL_EXPORT void icalattach_ref(icalattach *attach);

/**
 * @brief Decrements reference count of the icalattach.
 * @param attach The object to decrease the reference count of
 * @sa icalattach_ref()
 *
 * Decreases the reference count of @a attach. If this was the
 * last user of the object, it is freed.
 *
 * @par Error handling
 * If @a attach is `NULL`, or the reference count is smaller than 0,
 * it sets ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * Calling this function releases the icalattach back to the library,
 * and it must not be used afterwards.
 *
 * @par Usage
 * ```c
 * // creates new
 * icalattach *attach = icalattach_new_from_url("http://example.com");
 *
 * // release it
 * icalattach_unref(attach);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalattach_unref(icalattach *attach);

/**
 * @brief Determines if @a attach is an URL.
 * @param attach the icalattach object to check
 * @sa icalattach_get_url()
 *
 * Errors if @p attach is `NULL`.
 *
 * @par Usage
 * ```c
 * // creates new
 * icalattach *attach = icalattach_new_from_url("http://example.com");
 *
 * // checks if it is a URL
 * assert(icalattach_get_is_url(attach));
 *
 * // release it
 * icalattach_unref(attach);
 * ```
 *
 * @return true if the specified icalattach is a URL; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalattach_get_is_url(const icalattach *attach);

/**
 * @brief Returns the URL of the icalattach object.
 * @param attach The object from which to return the URL
 * @return The URL of the object
 * @sa icalattach_get_is_url()
 *
 * Returns the URL of the icalattach object.
 *
 * @par Error handling
 * Returns `NULL` and set ::icalerrno to ::ICAL_BADARG_ERROR if
 * @a attach is `NULL`. Undefined behaviour if the object is not
 * a URL (check with icalattach_get_is_url()).
 *
 * @par Ownership
 * The string returned is owned by libical and must not be freed
 * by the caller.
 *
 * @par Usage
 * ```c
 * // creates new
 * icalattach *attach = icalattach_new_from_url("http://example.com");
 *
 * // checks it
 * assert(icalattach_get_is_url(attach));
 * assert(0 == strcmp(icalattach_get_url(attach), "http://example.com"));
 *
 * // release it
 * icalattach_unref(attach);
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalattach_get_url(icalattach *attach);

/**
 * @brief Returns the data of the icalattach object.
 * @param attach The object from which to return the data
 * @return The data of the object
 * @sa icalattach_get_is_url()
 *
 * Returns the URL of the icalattach object.
 *
 * @par Error handling
 * Returns `NULL` and set ::icalerrno to ::ICAL_BADARG_ERROR if
 * @a attach is `NULL`. Undefined behaviour if the object is
 * a URL (check with icalattach_get_is_url()).
 *
 * @par Ownership
 * The string returned is owned by libical and must not be freed
 * by the caller.
 */
LIBICAL_ICAL_EXPORT unsigned char *icalattach_get_data(icalattach *attach);

#endif /* !ICALATTACH_H */

/*======================================================================
 FILE: icalderivedvalue.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 1999, Eric Busboom  <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalderivedvalue.h
 * @brief ICalendar values.
 */

#ifndef ICALDERIVEDVALUE_H
#define ICALDERIVEDVALUE_H

#include "libical_ical_export.h"


typedef struct icalvalue_impl icalvalue;

LIBICAL_ICAL_EXPORT void icalvalue_set_x(icalvalue *value, const char *v);
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_x(const char *v);
LIBICAL_ICAL_EXPORT const char *icalvalue_get_x(const icalvalue *value);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_recur(struct icalrecurrencetype *recur);
LIBICAL_ICAL_EXPORT void icalvalue_set_recur(icalvalue *value, struct icalrecurrencetype *recur);
LIBICAL_ICAL_EXPORT struct icalrecurrencetype *icalvalue_get_recur(const icalvalue *value);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_trigger(struct icaltriggertype v);
LIBICAL_ICAL_EXPORT void icalvalue_set_trigger(icalvalue *value, struct icaltriggertype v);
LIBICAL_ICAL_EXPORT struct icaltriggertype icalvalue_get_trigger(const icalvalue *value);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_date(struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalvalue_get_date(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_date(icalvalue *value, struct icaltimetype v);

/**
 * Creates a new icalvalue representing the specified icaltimetype.
 * @param v is an @p icaltimetype
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_datetime(struct icaltimetype v);

/**
 * Returns the icaltimetype corresponding to the specified icalvalue.
 * @param value pointer to an icalvalue.
 * @returns the icaltimetype as datetime.
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalvalue_get_datetime(const icalvalue *value);

/**
 * Sets an icalvalue for the specified icaltimetype.
 * @param value is a pointer to an icalvalue.
 * @param v is
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT void icalvalue_set_datetime(icalvalue *value, struct icaltimetype v);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_datetimedate(struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalvalue_get_datetimedate(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_datetimedate(icalvalue *value, struct icaltimetype v);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_datetimeperiod(struct icaldatetimeperiodtype v);
LIBICAL_ICAL_EXPORT void icalvalue_set_datetimeperiod(icalvalue *value,
                                                      struct icaldatetimeperiodtype v);
LIBICAL_ICAL_EXPORT struct icaldatetimeperiodtype icalvalue_get_datetimeperiod(const icalvalue *
                                                                               value);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_geo(struct icalgeotype v);
LIBICAL_ICAL_EXPORT struct icalgeotype icalvalue_get_geo(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_geo(icalvalue *value, struct icalgeotype v);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_attach(icalattach *attach);
LIBICAL_ICAL_EXPORT void icalvalue_set_attach(icalvalue *value, icalattach *attach);
LIBICAL_ICAL_EXPORT icalattach *icalvalue_get_attach(const icalvalue *value);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_binary(const char *v);
LIBICAL_ICAL_EXPORT void icalvalue_set_binary(icalvalue *value, const char *v);
LIBICAL_ICAL_EXPORT const char *icalvalue_get_binary(const icalvalue *value);

#define icalvalue_new_link icalvalue_new_uri
#define icalvalue_set_link icalvalue_set_uri
#define icalvalue_get_link icalvalue_get_uri

#define icalvalue_new_relatedto icalvalue_new_text
#define icalvalue_set_relatedto icalvalue_set_text
#define icalvalue_get_relatedto icalvalue_get_text

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_requeststatus(struct icalreqstattype v);
LIBICAL_ICAL_EXPORT struct icalreqstattype icalvalue_get_requeststatus(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_requeststatus(icalvalue *value, struct icalreqstattype v);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_color(const char *v);
LIBICAL_ICAL_EXPORT void icalvalue_set_color(icalvalue *value, const char *v);
LIBICAL_ICAL_EXPORT const char *icalvalue_get_color(const icalvalue *value);

typedef enum icalvalue_kind {
   ICAL_ANY_VALUE=5000,
    ICAL_ACTION_VALUE=5027,
    ICAL_ATTACH_VALUE=5003,
    ICAL_BINARY_VALUE=5011,
    ICAL_BOOLEAN_VALUE=5021,
    ICAL_BUSYTYPE_VALUE=5032,
    ICAL_CALADDRESS_VALUE=5023,
    ICAL_CARLEVEL_VALUE=5016,
    ICAL_CLASS_VALUE=5019,
    ICAL_CMD_VALUE=5010,
    ICAL_COLOR_VALUE=5044,
    ICAL_DATE_VALUE=5002,
    ICAL_DATETIME_VALUE=5028,
    ICAL_DATETIMEDATE_VALUE=5036,
    ICAL_DATETIMEPERIOD_VALUE=5015,
    ICAL_DURATION_VALUE=5020,
    ICAL_FLOAT_VALUE=5013,
    ICAL_GEO_VALUE=5004,
    ICAL_INTEGER_VALUE=5017,
    ICAL_LINK_VALUE=5042,
    ICAL_METHOD_VALUE=5030,
    ICAL_PARTICIPANTTYPE_VALUE=5037,
    ICAL_PERIOD_VALUE=5014,
    ICAL_POLLCOMPLETION_VALUE=5034,
    ICAL_POLLMODE_VALUE=5033,
    ICAL_PROXIMITY_VALUE=5039,
    ICAL_QUERY_VALUE=5001,
    ICAL_QUERYLEVEL_VALUE=5012,
    ICAL_RECUR_VALUE=5026,
    ICAL_RELATEDTO_VALUE=5043,
    ICAL_REQUESTSTATUS_VALUE=5009,
    ICAL_RESOURCETYPE_VALUE=5038,
    ICAL_STATUS_VALUE=5005,
    ICAL_STRING_VALUE=5007,
    ICAL_TASKMODE_VALUE=5035,
    ICAL_TEXT_VALUE=5008,
    ICAL_TRANSP_VALUE=5006,
    ICAL_TRIGGER_VALUE=5024,
    ICAL_UID_VALUE=5040,
    ICAL_URI_VALUE=5018,
    ICAL_UTCOFFSET_VALUE=5029,
    ICAL_X_VALUE=5022,
    ICAL_XLICCLASS_VALUE=5025,
    ICAL_XMLREFERENCE_VALUE=5041,
   ICAL_NO_VALUE=5031
} icalvalue_kind;

#define ICALPROPERTY_FIRST_ENUM 10000

typedef enum icalproperty_action {
    ICAL_ACTION_X = 10000,
    ICAL_ACTION_AUDIO = 10001,
    ICAL_ACTION_DISPLAY = 10002,
    ICAL_ACTION_EMAIL = 10003,
    ICAL_ACTION_PROCEDURE = 10004,
    ICAL_ACTION_NONE = 10099
} icalproperty_action;

typedef enum icalproperty_busytype {
    ICAL_BUSYTYPE_X = 10100,
    ICAL_BUSYTYPE_BUSY = 10101,
    ICAL_BUSYTYPE_BUSYUNAVAILABLE = 10102,
    ICAL_BUSYTYPE_BUSYTENTATIVE = 10103,
    ICAL_BUSYTYPE_NONE = 10199
} icalproperty_busytype;

typedef enum icalproperty_carlevel {
    ICAL_CARLEVEL_X = 10200,
    ICAL_CARLEVEL_CARNONE = 10201,
    ICAL_CARLEVEL_CARMIN = 10202,
    ICAL_CARLEVEL_CARFULL1 = 10203,
    ICAL_CARLEVEL_NONE = 10299
} icalproperty_carlevel;

typedef enum icalproperty_class {
    ICAL_CLASS_X = 10300,
    ICAL_CLASS_PUBLIC = 10301,
    ICAL_CLASS_PRIVATE = 10302,
    ICAL_CLASS_CONFIDENTIAL = 10303,
    ICAL_CLASS_NONE = 10399
} icalproperty_class;

typedef enum icalproperty_cmd {
    ICAL_CMD_X = 10400,
    ICAL_CMD_ABORT = 10401,
    ICAL_CMD_CONTINUE = 10402,
    ICAL_CMD_CREATE = 10403,
    ICAL_CMD_DELETE = 10404,
    ICAL_CMD_GENERATEUID = 10405,
    ICAL_CMD_GETCAPABILITY = 10406,
    ICAL_CMD_IDENTIFY = 10407,
    ICAL_CMD_MODIFY = 10408,
    ICAL_CMD_MOVE = 10409,
    ICAL_CMD_REPLY = 10410,
    ICAL_CMD_SEARCH = 10411,
    ICAL_CMD_SETLOCALE = 10412,
    ICAL_CMD_NONE = 10499
} icalproperty_cmd;

typedef enum icalproperty_method {
    ICAL_METHOD_X = 10500,
    ICAL_METHOD_PUBLISH = 10501,
    ICAL_METHOD_REQUEST = 10502,
    ICAL_METHOD_REPLY = 10503,
    ICAL_METHOD_ADD = 10504,
    ICAL_METHOD_CANCEL = 10505,
    ICAL_METHOD_REFRESH = 10506,
    ICAL_METHOD_COUNTER = 10507,
    ICAL_METHOD_DECLINECOUNTER = 10508,
    ICAL_METHOD_CREATE = 10509,
    ICAL_METHOD_READ = 10510,
    ICAL_METHOD_RESPONSE = 10511,
    ICAL_METHOD_MOVE = 10512,
    ICAL_METHOD_MODIFY = 10513,
    ICAL_METHOD_GENERATEUID = 10514,
    ICAL_METHOD_DELETE = 10515,
    ICAL_METHOD_POLLSTATUS = 10516,
    ICAL_METHOD_NONE = 10599
} icalproperty_method;

typedef enum icalproperty_participanttype {
    ICAL_PARTICIPANTTYPE_X = 11400,
    ICAL_PARTICIPANTTYPE_ACTIVE = 11401,
    ICAL_PARTICIPANTTYPE_INACTIVE = 11402,
    ICAL_PARTICIPANTTYPE_SPONSOR = 11403,
    ICAL_PARTICIPANTTYPE_CONTACT = 11404,
    ICAL_PARTICIPANTTYPE_BOOKINGCONTACT = 11405,
    ICAL_PARTICIPANTTYPE_EMERGENCYCONTACT = 11406,
    ICAL_PARTICIPANTTYPE_PUBLICITYCONTACT = 11407,
    ICAL_PARTICIPANTTYPE_PLANNERCONTACT = 11408,
    ICAL_PARTICIPANTTYPE_PERFORMER = 11409,
    ICAL_PARTICIPANTTYPE_SPEAKER = 11410,
    ICAL_PARTICIPANTTYPE_VOTER = 11411,
    ICAL_PARTICIPANTTYPE_NONE = 11499
} icalproperty_participanttype;

typedef enum icalproperty_pollcompletion {
    ICAL_POLLCOMPLETION_X = 10600,
    ICAL_POLLCOMPLETION_SERVER = 10601,
    ICAL_POLLCOMPLETION_SERVERSUBMIT = 10602,
    ICAL_POLLCOMPLETION_SERVERCHOICE = 10603,
    ICAL_POLLCOMPLETION_CLIENT = 10604,
    ICAL_POLLCOMPLETION_NONE = 10699
} icalproperty_pollcompletion;

typedef enum icalproperty_pollmode {
    ICAL_POLLMODE_X = 10700,
    ICAL_POLLMODE_BASIC = 10701,
    ICAL_POLLMODE_NONE = 10799
} icalproperty_pollmode;

typedef enum icalproperty_proximity {
    ICAL_PROXIMITY_X = 11300,
    ICAL_PROXIMITY_ARRIVE = 11301,
    ICAL_PROXIMITY_DEPART = 11302,
    ICAL_PROXIMITY_CONNECT = 11303,
    ICAL_PROXIMITY_DISCONNECT = 11304,
    ICAL_PROXIMITY_NONE = 11399
} icalproperty_proximity;

typedef enum icalproperty_querylevel {
    ICAL_QUERYLEVEL_X = 10800,
    ICAL_QUERYLEVEL_CALQL1 = 10801,
    ICAL_QUERYLEVEL_CALQLNONE = 10802,
    ICAL_QUERYLEVEL_NONE = 10899
} icalproperty_querylevel;

typedef enum icalproperty_resourcetype {
    ICAL_RESOURCETYPE_X = 11500,
    ICAL_RESOURCETYPE_ROOM = 11501,
    ICAL_RESOURCETYPE_PROJECTOR = 11502,
    ICAL_RESOURCETYPE_REMOTECONFERENCEAUDIO = 11503,
    ICAL_RESOURCETYPE_REMOTECONFERENCEVIDEO = 11504,
    ICAL_RESOURCETYPE_NONE = 11599
} icalproperty_resourcetype;

typedef enum icalproperty_status {
    ICAL_STATUS_X = 10900,
    ICAL_STATUS_TENTATIVE = 10901,
    ICAL_STATUS_CONFIRMED = 10902,
    ICAL_STATUS_COMPLETED = 10903,
    ICAL_STATUS_NEEDSACTION = 10904,
    ICAL_STATUS_CANCELLED = 10905,
    ICAL_STATUS_INPROCESS = 10906,
    ICAL_STATUS_DRAFT = 10907,
    ICAL_STATUS_FINAL = 10908,
    ICAL_STATUS_SUBMITTED = 10909,
    ICAL_STATUS_PENDING = 10910,
    ICAL_STATUS_FAILED = 10911,
    ICAL_STATUS_DELETED = 10912,
    ICAL_STATUS_NONE = 10999
} icalproperty_status;

typedef enum icalproperty_taskmode {
    ICAL_TASKMODE_X = 11200,
    ICAL_TASKMODE_AUTOMATICCOMPLETION = 11201,
    ICAL_TASKMODE_AUTOMATICFAILURE = 11202,
    ICAL_TASKMODE_AUTOMATICSTATUS = 11203,
    ICAL_TASKMODE_NONE = 11299
} icalproperty_taskmode;

typedef enum icalproperty_transp {
    ICAL_TRANSP_X = 11000,
    ICAL_TRANSP_OPAQUE = 11001,
    ICAL_TRANSP_OPAQUENOCONFLICT = 11002,
    ICAL_TRANSP_TRANSPARENT = 11003,
    ICAL_TRANSP_TRANSPARENTNOCONFLICT = 11004,
    ICAL_TRANSP_NONE = 11099
} icalproperty_transp;

typedef enum icalproperty_xlicclass {
    ICAL_XLICCLASS_X = 11100,
    ICAL_XLICCLASS_PUBLISHNEW = 11101,
    ICAL_XLICCLASS_PUBLISHUPDATE = 11102,
    ICAL_XLICCLASS_PUBLISHFREEBUSY = 11103,
    ICAL_XLICCLASS_REQUESTNEW = 11104,
    ICAL_XLICCLASS_REQUESTUPDATE = 11105,
    ICAL_XLICCLASS_REQUESTRESCHEDULE = 11106,
    ICAL_XLICCLASS_REQUESTDELEGATE = 11107,
    ICAL_XLICCLASS_REQUESTNEWORGANIZER = 11108,
    ICAL_XLICCLASS_REQUESTFORWARD = 11109,
    ICAL_XLICCLASS_REQUESTSTATUS = 11110,
    ICAL_XLICCLASS_REQUESTFREEBUSY = 11111,
    ICAL_XLICCLASS_REPLYACCEPT = 11112,
    ICAL_XLICCLASS_REPLYDECLINE = 11113,
    ICAL_XLICCLASS_REPLYDELEGATE = 11114,
    ICAL_XLICCLASS_REPLYCRASHERACCEPT = 11115,
    ICAL_XLICCLASS_REPLYCRASHERDECLINE = 11116,
    ICAL_XLICCLASS_ADDINSTANCE = 11117,
    ICAL_XLICCLASS_CANCELEVENT = 11118,
    ICAL_XLICCLASS_CANCELINSTANCE = 11119,
    ICAL_XLICCLASS_CANCELALL = 11120,
    ICAL_XLICCLASS_REFRESH = 11121,
    ICAL_XLICCLASS_COUNTER = 11122,
    ICAL_XLICCLASS_DECLINECOUNTER = 11123,
    ICAL_XLICCLASS_MALFORMED = 11124,
    ICAL_XLICCLASS_OBSOLETE = 11125,
    ICAL_XLICCLASS_MISSEQUENCED = 11126,
    ICAL_XLICCLASS_UNKNOWN = 11127,
    ICAL_XLICCLASS_NONE = 11199
} icalproperty_xlicclass;

#define ICALPROPERTY_LAST_ENUM 11600

/* ACTION */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_action(enum icalproperty_action v);
LIBICAL_ICAL_EXPORT enum icalproperty_action icalvalue_get_action(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_action(icalvalue *value, enum icalproperty_action v);

/* BOOLEAN */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_boolean(int v);
LIBICAL_ICAL_EXPORT int icalvalue_get_boolean(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_boolean(icalvalue *value, int v);

/* BUSYTYPE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_busytype(enum icalproperty_busytype v);
LIBICAL_ICAL_EXPORT enum icalproperty_busytype icalvalue_get_busytype(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_busytype(icalvalue *value, enum icalproperty_busytype v);

/* CAL-ADDRESS */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_caladdress(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_caladdress(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_caladdress(icalvalue *value, const char * v);

/* CAR-LEVEL */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_carlevel(enum icalproperty_carlevel v);
LIBICAL_ICAL_EXPORT enum icalproperty_carlevel icalvalue_get_carlevel(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_carlevel(icalvalue *value, enum icalproperty_carlevel v);

/* CMD */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_cmd(enum icalproperty_cmd v);
LIBICAL_ICAL_EXPORT enum icalproperty_cmd icalvalue_get_cmd(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_cmd(icalvalue *value, enum icalproperty_cmd v);

/* DURATION */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_duration(struct icaldurationtype v);
LIBICAL_ICAL_EXPORT struct icaldurationtype icalvalue_get_duration(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_duration(icalvalue *value, struct icaldurationtype v);

/* FLOAT */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_float(float v);
LIBICAL_ICAL_EXPORT float icalvalue_get_float(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_float(icalvalue *value, float v);

/* INTEGER */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_integer(int v);
LIBICAL_ICAL_EXPORT int icalvalue_get_integer(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_integer(icalvalue *value, int v);

/* METHOD */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_method(enum icalproperty_method v);
LIBICAL_ICAL_EXPORT enum icalproperty_method icalvalue_get_method(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_method(icalvalue *value, enum icalproperty_method v);

/* PARTICIPANT-TYPE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_participanttype(enum icalproperty_participanttype v);
LIBICAL_ICAL_EXPORT enum icalproperty_participanttype icalvalue_get_participanttype(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_participanttype(icalvalue *value, enum icalproperty_participanttype v);

/* PERIOD */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_period(struct icalperiodtype v);
LIBICAL_ICAL_EXPORT struct icalperiodtype icalvalue_get_period(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_period(icalvalue *value, struct icalperiodtype v);

/* POLLCOMPLETION */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_pollcompletion(enum icalproperty_pollcompletion v);
LIBICAL_ICAL_EXPORT enum icalproperty_pollcompletion icalvalue_get_pollcompletion(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_pollcompletion(icalvalue *value, enum icalproperty_pollcompletion v);

/* POLLMODE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_pollmode(enum icalproperty_pollmode v);
LIBICAL_ICAL_EXPORT enum icalproperty_pollmode icalvalue_get_pollmode(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_pollmode(icalvalue *value, enum icalproperty_pollmode v);

/* PROXIMITY */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_proximity(enum icalproperty_proximity v);
LIBICAL_ICAL_EXPORT enum icalproperty_proximity icalvalue_get_proximity(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_proximity(icalvalue *value, enum icalproperty_proximity v);

/* QUERY */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_query(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_query(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_query(icalvalue *value, const char * v);

/* QUERY-LEVEL */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_querylevel(enum icalproperty_querylevel v);
LIBICAL_ICAL_EXPORT enum icalproperty_querylevel icalvalue_get_querylevel(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_querylevel(icalvalue *value, enum icalproperty_querylevel v);

/* RESOURCE-TYPE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_resourcetype(enum icalproperty_resourcetype v);
LIBICAL_ICAL_EXPORT enum icalproperty_resourcetype icalvalue_get_resourcetype(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_resourcetype(icalvalue *value, enum icalproperty_resourcetype v);

/* STATUS */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_status(enum icalproperty_status v);
LIBICAL_ICAL_EXPORT enum icalproperty_status icalvalue_get_status(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_status(icalvalue *value, enum icalproperty_status v);

/* STRING */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_string(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_string(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_string(icalvalue *value, const char * v);

/* TASKMODE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_taskmode(enum icalproperty_taskmode v);
LIBICAL_ICAL_EXPORT enum icalproperty_taskmode icalvalue_get_taskmode(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_taskmode(icalvalue *value, enum icalproperty_taskmode v);

/* TEXT */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_text(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_text(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_text(icalvalue *value, const char * v);

/* TRANSP */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_transp(enum icalproperty_transp v);
LIBICAL_ICAL_EXPORT enum icalproperty_transp icalvalue_get_transp(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_transp(icalvalue *value, enum icalproperty_transp v);

/* UID */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_uid(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_uid(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_uid(icalvalue *value, const char * v);

/* URI */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_uri(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_uri(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_uri(icalvalue *value, const char * v);

/* UTC-OFFSET */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_utcoffset(int v);
LIBICAL_ICAL_EXPORT int icalvalue_get_utcoffset(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_utcoffset(icalvalue *value, int v);

/* X-LIC-CLASS */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_xlicclass(enum icalproperty_xlicclass v);
LIBICAL_ICAL_EXPORT enum icalproperty_xlicclass icalvalue_get_xlicclass(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_xlicclass(icalvalue *value, enum icalproperty_xlicclass v);

/* XML-REFERENCE */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_xmlreference(const char * v);
LIBICAL_ICAL_EXPORT const char * icalvalue_get_xmlreference(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_xmlreference(icalvalue *value, const char * v);

LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_class(enum icalproperty_class v);
LIBICAL_ICAL_EXPORT enum icalproperty_class icalvalue_get_class(const icalvalue *value);
LIBICAL_ICAL_EXPORT void icalvalue_set_class(icalvalue *value, enum icalproperty_class v);
#endif /*ICALVALUE_H*/

/*======================================================================
 FILE: icalderivedparameter.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/
#ifndef ICALDERIVEDPARAMETER_H
#define ICALDERIVEDPARAMETER_H

/**
 * @file icalderivedparameter.h
 * @brief ICalendar parameters.
 */

#include "libical_ical_export.h"


#include <stdbool.h>

typedef struct icalparameter_impl icalparameter;

LIBICAL_ICAL_EXPORT const char *icalparameter_enum_to_string(int e);
LIBICAL_ICAL_EXPORT int icalparameter_string_to_enum(const char *str);

/* START of section of machine generated code (mkderivedparameters.pl). Do not edit. */

typedef enum icalparameter_kind {
    ICAL_ANY_PARAMETER = 0,
    ICAL_ACTIONPARAM_PARAMETER = 1,
    ICAL_ALTREP_PARAMETER = 2,
    ICAL_CHARSET_PARAMETER = 3,
    ICAL_CN_PARAMETER = 4,
    ICAL_CUTYPE_PARAMETER = 5,
    ICAL_DELEGATEDFROM_PARAMETER = 6,
    ICAL_DELEGATEDTO_PARAMETER = 7,
    ICAL_DERIVED_PARAMETER = 54,
    ICAL_DIR_PARAMETER = 8,
    ICAL_DISPLAY_PARAMETER = 46,
    ICAL_EMAIL_PARAMETER = 50,
    ICAL_ENABLE_PARAMETER = 9,
    ICAL_ENCODING_PARAMETER = 10,
    ICAL_FBTYPE_PARAMETER = 11,
    ICAL_FEATURE_PARAMETER = 48,
    ICAL_FILENAME_PARAMETER = 42,
    ICAL_FMTTYPE_PARAMETER = 12,
    ICAL_GAP_PARAMETER = 55,
    ICAL_IANA_PARAMETER = 33,
    ICAL_ID_PARAMETER = 13,
    ICAL_LABEL_PARAMETER = 49,
    ICAL_LANGUAGE_PARAMETER = 14,
    ICAL_LATENCY_PARAMETER = 15,
    ICAL_LINKREL_PARAMETER = 56,
    ICAL_LOCAL_PARAMETER = 16,
    ICAL_LOCALIZE_PARAMETER = 17,
    ICAL_MANAGEDID_PARAMETER = 40,
    ICAL_MEMBER_PARAMETER = 18,
    ICAL_MODIFIED_PARAMETER = 44,
    ICAL_OPTIONS_PARAMETER = 19,
    ICAL_ORDER_PARAMETER = 52,
    ICAL_PARTSTAT_PARAMETER = 20,
    ICAL_PATCHACTION_PARAMETER = 51,
    ICAL_PUBLICCOMMENT_PARAMETER = 37,
    ICAL_RANGE_PARAMETER = 21,
    ICAL_REASON_PARAMETER = 47,
    ICAL_RELATED_PARAMETER = 22,
    ICAL_RELTYPE_PARAMETER = 23,
    ICAL_REQUIRED_PARAMETER = 43,
    ICAL_RESPONSE_PARAMETER = 38,
    ICAL_ROLE_PARAMETER = 24,
    ICAL_RSVP_PARAMETER = 25,
    ICAL_SCHEDULEAGENT_PARAMETER = 34,
    ICAL_SCHEDULEFORCESEND_PARAMETER = 35,
    ICAL_SCHEDULESTATUS_PARAMETER = 36,
    ICAL_SCHEMA_PARAMETER = 53,
    ICAL_SENTBY_PARAMETER = 26,
    ICAL_SIZE_PARAMETER = 41,
    ICAL_STAYINFORMED_PARAMETER = 39,
    ICAL_SUBSTATE_PARAMETER = 45,
    ICAL_TZID_PARAMETER = 27,
    ICAL_VALUE_PARAMETER = 28,
    ICAL_X_PARAMETER = 29,
    ICAL_XLICCOMPARETYPE_PARAMETER = 30,
    ICAL_XLICERRORTYPE_PARAMETER = 31,
    ICAL_NO_PARAMETER = 32
} icalparameter_kind;

#define ICALPARAMETER_FIRST_ENUM 20000

typedef enum icalparameter_action {
    ICAL_ACTIONPARAM_X = 20000,
    ICAL_ACTIONPARAM_ASK = 20001,
    ICAL_ACTIONPARAM_ABORT = 20002,
    ICAL_ACTIONPARAM_NONE = 20099
} icalparameter_action;

typedef enum icalparameter_cutype {
    ICAL_CUTYPE_X = 20100,
    ICAL_CUTYPE_INDIVIDUAL = 20101,
    ICAL_CUTYPE_GROUP = 20102,
    ICAL_CUTYPE_RESOURCE = 20103,
    ICAL_CUTYPE_ROOM = 20104,
    ICAL_CUTYPE_UNKNOWN = 20105,
    ICAL_CUTYPE_NONE = 20199
} icalparameter_cutype;

typedef enum icalparameter_derived {
    ICAL_DERIVED_X = 22300,
    ICAL_DERIVED_TRUE = 22301,
    ICAL_DERIVED_FALSE = 22302,
    ICAL_DERIVED_NONE = 22399
} icalparameter_derived;

typedef enum icalparameter_display {
    ICAL_DISPLAY_X = 22000,
    ICAL_DISPLAY_BADGE = 22001,
    ICAL_DISPLAY_GRAPHIC = 22002,
    ICAL_DISPLAY_FULLSIZE = 22003,
    ICAL_DISPLAY_THUMBNAIL = 22004,
    ICAL_DISPLAY_NONE = 22099
} icalparameter_display;

typedef enum icalparameter_enable {
    ICAL_ENABLE_X = 20200,
    ICAL_ENABLE_TRUE = 20201,
    ICAL_ENABLE_FALSE = 20202,
    ICAL_ENABLE_NONE = 20299
} icalparameter_enable;

typedef enum icalparameter_encoding {
    ICAL_ENCODING_X = 20300,
    ICAL_ENCODING_8BIT = 20301,
    ICAL_ENCODING_BASE64 = 20302,
    ICAL_ENCODING_NONE = 20399
} icalparameter_encoding;

typedef enum icalparameter_fbtype {
    ICAL_FBTYPE_X = 20400,
    ICAL_FBTYPE_FREE = 20401,
    ICAL_FBTYPE_BUSY = 20402,
    ICAL_FBTYPE_BUSYUNAVAILABLE = 20403,
    ICAL_FBTYPE_BUSYTENTATIVE = 20404,
    ICAL_FBTYPE_NONE = 20499
} icalparameter_fbtype;

typedef enum icalparameter_feature {
    ICAL_FEATURE_X = 22100,
    ICAL_FEATURE_AUDIO = 22101,
    ICAL_FEATURE_CHAT = 22102,
    ICAL_FEATURE_FEED = 22103,
    ICAL_FEATURE_MODERATOR = 22104,
    ICAL_FEATURE_PHONE = 22105,
    ICAL_FEATURE_SCREEN = 22106,
    ICAL_FEATURE_VIDEO = 22107,
    ICAL_FEATURE_NONE = 22199
} icalparameter_feature;

typedef enum icalparameter_local {
    ICAL_LOCAL_X = 20500,
    ICAL_LOCAL_TRUE = 20501,
    ICAL_LOCAL_FALSE = 20502,
    ICAL_LOCAL_NONE = 20599
} icalparameter_local;

typedef enum icalparameter_partstat {
    ICAL_PARTSTAT_X = 20600,
    ICAL_PARTSTAT_NEEDSACTION = 20601,
    ICAL_PARTSTAT_ACCEPTED = 20602,
    ICAL_PARTSTAT_DECLINED = 20603,
    ICAL_PARTSTAT_TENTATIVE = 20604,
    ICAL_PARTSTAT_DELEGATED = 20605,
    ICAL_PARTSTAT_COMPLETED = 20606,
    ICAL_PARTSTAT_INPROCESS = 20607,
    ICAL_PARTSTAT_FAILED = 20608,
    ICAL_PARTSTAT_NONE = 20699
} icalparameter_partstat;

typedef enum icalparameter_patchaction {
    ICAL_PATCHACTION_X = 22200,
    ICAL_PATCHACTION_CREATE = 22201,
    ICAL_PATCHACTION_BYNAME = 22202,
    ICAL_PATCHACTION_BYVALUE = 22203,
    ICAL_PATCHACTION_BYPARAM = 22204,
    ICAL_PATCHACTION_NONE = 22299
} icalparameter_patchaction;

typedef enum icalparameter_range {
    ICAL_RANGE_X = 20700,
    ICAL_RANGE_THISANDPRIOR = 20701,
    ICAL_RANGE_THISANDFUTURE = 20702,
    ICAL_RANGE_NONE = 20799
} icalparameter_range;

typedef enum icalparameter_related {
    ICAL_RELATED_X = 20800,
    ICAL_RELATED_START = 20801,
    ICAL_RELATED_END = 20802,
    ICAL_RELATED_NONE = 20899
} icalparameter_related;

typedef enum icalparameter_reltype {
    ICAL_RELTYPE_X = 20900,
    ICAL_RELTYPE_PARENT = 20901,
    ICAL_RELTYPE_CHILD = 20902,
    ICAL_RELTYPE_SIBLING = 20903,
    ICAL_RELTYPE_POLL = 20904,
    ICAL_RELTYPE_SNOOZE = 20905,
    ICAL_RELTYPE_CONCEPT = 20906,
    ICAL_RELTYPE_DEPENDSON = 20907,
    ICAL_RELTYPE_FINISHTOFINISH = 20908,
    ICAL_RELTYPE_FINISHTOSTART = 20909,
    ICAL_RELTYPE_FIRST = 20910,
    ICAL_RELTYPE_NEXT = 20911,
    ICAL_RELTYPE_REFID = 20912,
    ICAL_RELTYPE_STARTTOFINISH = 20913,
    ICAL_RELTYPE_STARTTOSTART = 20914,
    ICAL_RELTYPE_NONE = 20999
} icalparameter_reltype;

typedef enum icalparameter_required {
    ICAL_REQUIRED_X = 21000,
    ICAL_REQUIRED_TRUE = 21001,
    ICAL_REQUIRED_FALSE = 21002,
    ICAL_REQUIRED_NONE = 21099
} icalparameter_required;

typedef enum icalparameter_role {
    ICAL_ROLE_X = 21100,
    ICAL_ROLE_CHAIR = 21101,
    ICAL_ROLE_REQPARTICIPANT = 21102,
    ICAL_ROLE_OPTPARTICIPANT = 21103,
    ICAL_ROLE_NONPARTICIPANT = 21104,
    ICAL_ROLE_NONE = 21199
} icalparameter_role;

typedef enum icalparameter_rsvp {
    ICAL_RSVP_X = 21200,
    ICAL_RSVP_TRUE = 21201,
    ICAL_RSVP_FALSE = 21202,
    ICAL_RSVP_NONE = 21299
} icalparameter_rsvp;

typedef enum icalparameter_scheduleagent {
    ICAL_SCHEDULEAGENT_X = 21300,
    ICAL_SCHEDULEAGENT_SERVER = 21301,
    ICAL_SCHEDULEAGENT_CLIENT = 21302,
    ICAL_SCHEDULEAGENT_NONE = 21399
} icalparameter_scheduleagent;

typedef enum icalparameter_scheduleforcesend {
    ICAL_SCHEDULEFORCESEND_X = 21400,
    ICAL_SCHEDULEFORCESEND_REQUEST = 21401,
    ICAL_SCHEDULEFORCESEND_REPLY = 21402,
    ICAL_SCHEDULEFORCESEND_NONE = 21499
} icalparameter_scheduleforcesend;

typedef enum icalparameter_stayinformed {
    ICAL_STAYINFORMED_X = 21500,
    ICAL_STAYINFORMED_TRUE = 21501,
    ICAL_STAYINFORMED_FALSE = 21502,
    ICAL_STAYINFORMED_NONE = 21599
} icalparameter_stayinformed;

typedef enum icalparameter_substate {
    ICAL_SUBSTATE_X = 21900,
    ICAL_SUBSTATE_OK = 21901,
    ICAL_SUBSTATE_ERROR = 21902,
    ICAL_SUBSTATE_SUSPENDED = 21903,
    ICAL_SUBSTATE_NONE = 21999
} icalparameter_substate;

typedef enum icalparameter_value {
    ICAL_VALUE_X = 21600,
    ICAL_VALUE_BINARY = 21601,
    ICAL_VALUE_BOOLEAN = 21602,
    ICAL_VALUE_DATE = 21603,
    ICAL_VALUE_DURATION = 21604,
    ICAL_VALUE_FLOAT = 21605,
    ICAL_VALUE_INTEGER = 21606,
    ICAL_VALUE_PERIOD = 21607,
    ICAL_VALUE_RECUR = 21608,
    ICAL_VALUE_TEXT = 21609,
    ICAL_VALUE_URI = 21610,
    ICAL_VALUE_ERROR = 21611,
    ICAL_VALUE_DATETIME = 21612,
    ICAL_VALUE_UTCOFFSET = 21613,
    ICAL_VALUE_CALADDRESS = 21614,
    ICAL_VALUE_UID = 21615,
    ICAL_VALUE_XMLREFERENCE = 21616,
    ICAL_VALUE_NONE = 21699
} icalparameter_value;

typedef enum icalparameter_xliccomparetype {
    ICAL_XLICCOMPARETYPE_X = 21700,
    ICAL_XLICCOMPARETYPE_EQUAL = 21701,
    ICAL_XLICCOMPARETYPE_NOTEQUAL = 21702,
    ICAL_XLICCOMPARETYPE_LESS = 21703,
    ICAL_XLICCOMPARETYPE_GREATER = 21704,
    ICAL_XLICCOMPARETYPE_LESSEQUAL = 21705,
    ICAL_XLICCOMPARETYPE_GREATEREQUAL = 21706,
    ICAL_XLICCOMPARETYPE_REGEX = 21707,
    ICAL_XLICCOMPARETYPE_ISNULL = 21708,
    ICAL_XLICCOMPARETYPE_ISNOTNULL = 21709,
    ICAL_XLICCOMPARETYPE_NONE = 21799
} icalparameter_xliccomparetype;

typedef enum icalparameter_xlicerrortype {
    ICAL_XLICERRORTYPE_X = 21800,
    ICAL_XLICERRORTYPE_COMPONENTPARSEERROR = 21801,
    ICAL_XLICERRORTYPE_PROPERTYPARSEERROR = 21802,
    ICAL_XLICERRORTYPE_PARAMETERNAMEPARSEERROR = 21803,
    ICAL_XLICERRORTYPE_PARAMETERVALUEPARSEERROR = 21804,
    ICAL_XLICERRORTYPE_VALUEPARSEERROR = 21805,
    ICAL_XLICERRORTYPE_INVALIDITIP = 21806,
    ICAL_XLICERRORTYPE_UNKNOWNVCALPROPERROR = 21807,
    ICAL_XLICERRORTYPE_MIMEPARSEERROR = 21808,
    ICAL_XLICERRORTYPE_VCALPROPPARSEERROR = 21809,
    ICAL_XLICERRORTYPE_NONE = 21899
} icalparameter_xlicerrortype;

#define ICALPARAMETER_LAST_ENUM 22400


/* ACTIONPARAM */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_actionparam(icalparameter_action v);
LIBICAL_ICAL_EXPORT icalparameter_action icalparameter_get_actionparam(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_actionparam(icalparameter *value, icalparameter_action v);

/* ALTREP */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_altrep(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_altrep(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_altrep(icalparameter *value, const char * v);

/* CHARSET */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_charset(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_charset(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_charset(icalparameter *value, const char * v);

/* CN */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_cn(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_cn(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_cn(icalparameter *value, const char * v);

/* CUTYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_cutype(icalparameter_cutype v);
LIBICAL_ICAL_EXPORT icalparameter_cutype icalparameter_get_cutype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_cutype(icalparameter *value, icalparameter_cutype v);

/* DELEGATED-FROM */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_delegatedfrom_list(icalstrarray * v);
LIBICAL_ICAL_EXPORT icalstrarray * icalparameter_get_delegatedfrom(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_delegatedfrom(icalparameter *value, icalstrarray * v);
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_delegatedfrom(const char * v);
LIBICAL_ICAL_EXPORT size_t icalparameter_get_delegatedfrom_size(icalparameter *param);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_delegatedfrom_nth(icalparameter *param, size_t position);
LIBICAL_ICAL_EXPORT void icalparameter_add_delegatedfrom(icalparameter *value, const char * v);
LIBICAL_ICAL_EXPORT void icalparameter_remove_delegatedfrom(icalparameter *value, const char * v);

/* DELEGATED-TO */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_delegatedto_list(icalstrarray * v);
LIBICAL_ICAL_EXPORT icalstrarray * icalparameter_get_delegatedto(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_delegatedto(icalparameter *value, icalstrarray * v);
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_delegatedto(const char * v);
LIBICAL_ICAL_EXPORT size_t icalparameter_get_delegatedto_size(icalparameter *param);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_delegatedto_nth(icalparameter *param, size_t position);
LIBICAL_ICAL_EXPORT void icalparameter_add_delegatedto(icalparameter *value, const char * v);
LIBICAL_ICAL_EXPORT void icalparameter_remove_delegatedto(icalparameter *value, const char * v);

/* DERIVED */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_derived(icalparameter_derived v);
LIBICAL_ICAL_EXPORT icalparameter_derived icalparameter_get_derived(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_derived(icalparameter *value, icalparameter_derived v);

/* DIR */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_dir(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_dir(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_dir(icalparameter *value, const char * v);

/* DISPLAY */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_display_list(icalenumarray * v);
LIBICAL_ICAL_EXPORT icalenumarray * icalparameter_get_display(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_display(icalparameter *value, icalenumarray * v);
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_display(icalparameter_display v);
LIBICAL_ICAL_EXPORT size_t icalparameter_get_display_size(icalparameter *param);
LIBICAL_ICAL_EXPORT icalparameter_display icalparameter_get_display_nth(icalparameter *param, size_t position);
LIBICAL_ICAL_EXPORT void icalparameter_add_display(icalparameter *value, icalenumarray_element * v);
LIBICAL_ICAL_EXPORT void icalparameter_remove_display(icalparameter *value, icalenumarray_element * v);

/* EMAIL */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_email(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_email(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_email(icalparameter *value, const char * v);

/* ENABLE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_enable(icalparameter_enable v);
LIBICAL_ICAL_EXPORT icalparameter_enable icalparameter_get_enable(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_enable(icalparameter *value, icalparameter_enable v);

/* ENCODING */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_encoding(icalparameter_encoding v);
LIBICAL_ICAL_EXPORT icalparameter_encoding icalparameter_get_encoding(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_encoding(icalparameter *value, icalparameter_encoding v);

/* FBTYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_fbtype(icalparameter_fbtype v);
LIBICAL_ICAL_EXPORT icalparameter_fbtype icalparameter_get_fbtype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_fbtype(icalparameter *value, icalparameter_fbtype v);

/* FEATURE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_feature_list(icalenumarray * v);
LIBICAL_ICAL_EXPORT icalenumarray * icalparameter_get_feature(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_feature(icalparameter *value, icalenumarray * v);
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_feature(icalparameter_feature v);
LIBICAL_ICAL_EXPORT size_t icalparameter_get_feature_size(icalparameter *param);
LIBICAL_ICAL_EXPORT icalparameter_feature icalparameter_get_feature_nth(icalparameter *param, size_t position);
LIBICAL_ICAL_EXPORT void icalparameter_add_feature(icalparameter *value, icalenumarray_element * v);
LIBICAL_ICAL_EXPORT void icalparameter_remove_feature(icalparameter *value, icalenumarray_element * v);

/* FILENAME */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_filename(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_filename(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_filename(icalparameter *value, const char * v);

/* FMTTYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_fmttype(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_fmttype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_fmttype(icalparameter *value, const char * v);

/* GAP */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_gap(struct icaldurationtype v);
LIBICAL_ICAL_EXPORT struct icaldurationtype icalparameter_get_gap(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_gap(icalparameter *value, struct icaldurationtype v);

/* IANA */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_iana(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_iana(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_iana(icalparameter *value, const char * v);

/* ID */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_id(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_id(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_id(icalparameter *value, const char * v);

/* LABEL */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_label(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_label(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_label(icalparameter *value, const char * v);

/* LANGUAGE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_language(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_language(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_language(icalparameter *value, const char * v);

/* LATENCY */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_latency(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_latency(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_latency(icalparameter *value, const char * v);

/* LINKREL */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_linkrel(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_linkrel(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_linkrel(icalparameter *value, const char * v);

/* LOCAL */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_local(icalparameter_local v);
LIBICAL_ICAL_EXPORT icalparameter_local icalparameter_get_local(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_local(icalparameter *value, icalparameter_local v);

/* LOCALIZE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_localize(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_localize(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_localize(icalparameter *value, const char * v);

/* MANAGED-ID */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_managedid(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_managedid(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_managedid(icalparameter *value, const char * v);

/* MEMBER */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_member_list(icalstrarray * v);
LIBICAL_ICAL_EXPORT icalstrarray * icalparameter_get_member(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_member(icalparameter *value, icalstrarray * v);
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_member(const char * v);
LIBICAL_ICAL_EXPORT size_t icalparameter_get_member_size(icalparameter *param);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_member_nth(icalparameter *param, size_t position);
LIBICAL_ICAL_EXPORT void icalparameter_add_member(icalparameter *value, const char * v);
LIBICAL_ICAL_EXPORT void icalparameter_remove_member(icalparameter *value, const char * v);

/* MODIFIED */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_modified(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_modified(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_modified(icalparameter *value, const char * v);

/* OPTIONS */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_options(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_options(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_options(icalparameter *value, const char * v);

/* ORDER */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_order(int v);
LIBICAL_ICAL_EXPORT int icalparameter_get_order(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_order(icalparameter *value, int v);

/* PARTSTAT */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_partstat(icalparameter_partstat v);
LIBICAL_ICAL_EXPORT icalparameter_partstat icalparameter_get_partstat(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_partstat(icalparameter *value, icalparameter_partstat v);

/* PATCH-ACTION */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_patchaction(icalparameter_patchaction v);
LIBICAL_ICAL_EXPORT icalparameter_patchaction icalparameter_get_patchaction(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_patchaction(icalparameter *value, icalparameter_patchaction v);

/* PUBLIC-COMMENT */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_publiccomment(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_publiccomment(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_publiccomment(icalparameter *value, const char * v);

/* RANGE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_range(icalparameter_range v);
LIBICAL_ICAL_EXPORT icalparameter_range icalparameter_get_range(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_range(icalparameter *value, icalparameter_range v);

/* REASON */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_reason(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_reason(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_reason(icalparameter *value, const char * v);

/* RELATED */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_related(icalparameter_related v);
LIBICAL_ICAL_EXPORT icalparameter_related icalparameter_get_related(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_related(icalparameter *value, icalparameter_related v);

/* RELTYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_reltype(icalparameter_reltype v);
LIBICAL_ICAL_EXPORT icalparameter_reltype icalparameter_get_reltype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_reltype(icalparameter *value, icalparameter_reltype v);

/* REQUIRED */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_required(icalparameter_required v);
LIBICAL_ICAL_EXPORT icalparameter_required icalparameter_get_required(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_required(icalparameter *value, icalparameter_required v);

/* RESPONSE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_response(int v);
LIBICAL_ICAL_EXPORT int icalparameter_get_response(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_response(icalparameter *value, int v);

/* ROLE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_role(icalparameter_role v);
LIBICAL_ICAL_EXPORT icalparameter_role icalparameter_get_role(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_role(icalparameter *value, icalparameter_role v);

/* RSVP */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_rsvp(icalparameter_rsvp v);
LIBICAL_ICAL_EXPORT icalparameter_rsvp icalparameter_get_rsvp(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_rsvp(icalparameter *value, icalparameter_rsvp v);

/* SCHEDULE-AGENT */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_scheduleagent(icalparameter_scheduleagent v);
LIBICAL_ICAL_EXPORT icalparameter_scheduleagent icalparameter_get_scheduleagent(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_scheduleagent(icalparameter *value, icalparameter_scheduleagent v);

/* SCHEDULE-FORCE-SEND */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_scheduleforcesend(icalparameter_scheduleforcesend v);
LIBICAL_ICAL_EXPORT icalparameter_scheduleforcesend icalparameter_get_scheduleforcesend(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_scheduleforcesend(icalparameter *value, icalparameter_scheduleforcesend v);

/* SCHEDULE-STATUS */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_schedulestatus(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_schedulestatus(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_schedulestatus(icalparameter *value, const char * v);

/* SCHEMA */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_schema(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_schema(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_schema(icalparameter *value, const char * v);

/* SENT-BY */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_sentby(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_sentby(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_sentby(icalparameter *value, const char * v);

/* SIZE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_size(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_size(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_size(icalparameter *value, const char * v);

/* STAY-INFORMED */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_stayinformed(icalparameter_stayinformed v);
LIBICAL_ICAL_EXPORT icalparameter_stayinformed icalparameter_get_stayinformed(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_stayinformed(icalparameter *value, icalparameter_stayinformed v);

/* SUBSTATE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_substate(icalparameter_substate v);
LIBICAL_ICAL_EXPORT icalparameter_substate icalparameter_get_substate(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_substate(icalparameter *value, icalparameter_substate v);

/* TZID */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_tzid(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_tzid(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_tzid(icalparameter *value, const char * v);

/* VALUE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_value(icalparameter_value v);
LIBICAL_ICAL_EXPORT icalparameter_value icalparameter_get_value(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_value(icalparameter *value, icalparameter_value v);

/* X */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_x(const char * v);
LIBICAL_ICAL_EXPORT const char * icalparameter_get_x(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_x(icalparameter *value, const char * v);

/* X-LIC-COMPARETYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_xliccomparetype(icalparameter_xliccomparetype v);
LIBICAL_ICAL_EXPORT icalparameter_xliccomparetype icalparameter_get_xliccomparetype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_xliccomparetype(icalparameter *value, icalparameter_xliccomparetype v);

/* X-LIC-ERRORTYPE */
LIBICAL_ICAL_EXPORT icalparameter * icalparameter_new_xlicerrortype(icalparameter_xlicerrortype v);
LIBICAL_ICAL_EXPORT icalparameter_xlicerrortype icalparameter_get_xlicerrortype(const icalparameter *value);
LIBICAL_ICAL_EXPORT void icalparameter_set_xlicerrortype(icalparameter *value, icalparameter_xlicerrortype v);
#endif /*ICALPARAMETER_H*/

/* END   of section of machine generated code (mkderivedparameters.pl). Do not edit. */


/*======================================================================
 FILE: icalvalue.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 ======================================================================*/

/**
 * @file icalvalue.h
 * @brief Defines the data structure representing iCalendar parameter values.
 */

#ifndef ICALVALUE_H
#define ICALVALUE_H

#include "libical_ical_export.h"


#include <stdbool.h>

/**
 * Construct a new icalvalue of the specified icalvalue_kind.
 *
 * @param kind is the icalvalue_kind to use
 *
 * @return a pointer to the newly allocated icalvalue. The data structure
 * contains all null values and is essentially invalid.
 * Free the resulting memory with icalvalue_free.
 */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new(icalvalue_kind kind);

/**
 * Deeply clone an icalvalue.
 *
 * @param old is a pointer to a valid icalvalue from which to clone
 *
 * @return a pointer to the memory for the newly cloned icalvalue.
 * Free the resulting memory using icalvalue_free.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_clone(const icalvalue *old);

/**
 * Construct and populate a new icalvalue of the specified icalvalue_kind.
 *
 * @param kind the icalvalue_kind to use
 * @param str is a non-NULL pointer to the data used to populate the new icalvalue
 *
 * @return a pointer to the newly allocated icalvalue. Free the resulting
 * memory with icalvalue_free.
 */
LIBICAL_ICAL_EXPORT icalvalue *icalvalue_new_from_string(icalvalue_kind kind, const char *str);

/**
 * Free the memory for an icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 */
LIBICAL_ICAL_EXPORT void icalvalue_free(icalvalue *value);

/**
 * Determine if the specified icalvalue is valid.
 *
 * @param value a pointer to a icalvalue
 *
 * @return true if @p value is valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalvalue_is_valid(const icalvalue *value);

/**
 * Create a string representation of an icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 *
 * @return a pointer to a char string containing the string representatin of @p v
value.
 * NULL is returned is @p value is invalid.
 *
 * @see icalvalue_as_ical_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalvalue_as_ical_string(const icalvalue *value);

/**
 * Create a string representation of an icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 *
 * @return a pointer to a char string containing the string representatin of @p value. NULL is returned is @p value is invalid.
 *
 * @see icalvalue_as_ical_string
 */
LIBICAL_ICAL_EXPORT char *icalvalue_as_ical_string_r(const icalvalue *value);

/**
 * Get the icalvalue_kind of an icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 *
 * @return the icalvalue_kind of @p value. ICAL_NO_VALUE is returned if value is null.
 */
LIBICAL_ICAL_EXPORT icalvalue_kind icalvalue_isa(const icalvalue *value);

/**
 * Determine if the specified address points to an icalvalue.
 *
 * @param value a pointer to a possible icalvalue.
 *
 * @return true if the address points to an icalvalue; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalvalue_isa_value(void *value);

/**
 * Compares two icalvalues.
 *
 * @param a an icalvalue to compare
 * @param b an icalvalue to compare
 *
 * @return an icalparameter_xliccomparetype representing how @p a and @p b compare;
 * if the values do not have the same type ICAL_XLICCOMPARETYPE_NOTEQUAL is returned;
 * ICAL_XLICCOMPARETYPE_NONE is returned if the values type is unknown or one of the values is null.
 */
LIBICAL_ICAL_EXPORT icalparameter_xliccomparetype icalvalue_compare(const icalvalue *a,
                                                                    const icalvalue *b);

/* Special, non autogenerated value accessors */

/* Defined in icalderivedvalue.h */
/* icalvalue* icalvalue_new_recur (struct icalrecurrencetype *v); */
/* void icalvalue_set_recur(icalvalue* value, struct icalrecurrencetype *v); */
/* struct icalrecurrencetype *icalvalue_get_recur(const icalvalue* value); */

/* icalvalue* icalvalue_new_trigger (struct icaltriggertype v); */
/* void icalvalue_set_trigger(icalvalue* value, struct icaltriggertype v); */
/* struct icaltriggertype icalvalue_get_trigger(const icalvalue* value); */

/* icalvalue* icalvalue_new_datetimeperiod (struct icaldatetimeperiodtype v); */
/* void icalvalue_set_datetimeperiod(icalvalue* value, */
/*                                struct icaldatetimeperiodtype v); */
/* struct icaldatetimeperiodtype icalvalue_get_datetimeperiod(const icalvalue* value); */

/* Convert enumerations */

/**
 * Converts a char string into an icalvalue_kind.
 *
 * @param str a pointer to a char string containing the character representation
 * of an icalvalue_kind
 *
 * @return the icalvalue_kind associated with @p str. ICAL_NO_VALUE is returned
 * if @p str is invalid.
 */
LIBICAL_ICAL_EXPORT icalvalue_kind icalvalue_string_to_kind(const char *str);

/**
 * Converts an icalvalue_kind to its string representation.
 *
 * @param kind is the icalvalue_kind to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalvalue_kind.
 */
LIBICAL_ICAL_EXPORT const char *icalvalue_kind_to_string(const icalvalue_kind kind);

/**
 * Check the validity of the specified icalvalue_kind.
 *
 * @param kind is the icalvalue_kind to use
 *
 * @return true if the icalvalue_kind is valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalvalue_kind_is_valid(const icalvalue_kind kind);

/**
 * Resets the icalvalue_kind of the specified icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 */
LIBICAL_ICAL_EXPORT void icalvalue_reset_kind(icalvalue *value);

/**
 * Encode a character string in ical format, escape certain characters, etc.
 *
 * @param szText is a pointer to a char string to be encoded
 * @param szEncText is a pointer to a char string to contain the encoded
 * input string upon return.
 * @param maxBufferLen is the maximum number of characters to encode
 *
 * @return true if the encoding was successful; false otherwise.
 *
 * @see icalvalue_decode_ical_string
 */
LIBICAL_ICAL_EXPORT bool icalvalue_encode_ical_string(const char *szText,
                                                      char *szEncText, int maxBufferLen);

/**
 * Decode the string that has been encoded by icalvalue_encode_ical_string().
 *
 * @param szText is a pointer to a char string to be decoded
 * @param szDecText is a pointer to a char string to contain the decoded
 * input string upon return.
 * @param maxBufferLen is the maximum number of characters to encode
 *
 * @return true if the decoding was successful; false otherwise.
 *
 * @see icalvalue_encode_ical_string
 */
LIBICAL_ICAL_EXPORT bool icalvalue_decode_ical_string(const char *szText,
                                                      char *szDecText, int maxBufferLen);

/* For the library only -- do not make visible */
/// @cond PRIVATE
extern void print_date_to_string(char *str, const struct icaltimetype *data);
extern void print_datetime_to_string(char *str, const struct icaltimetype *data);
/// @endcond

#endif /*ICALVALUE_H */

/*======================================================================
  FILE: icalparameter.h
  CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalparameter.h
 * @brief Defines the data structure representing iCalendar parameters.
 */

#ifndef ICALPARAMETER_H
#define ICALPARAMETER_H

#include "libical_ical_export.h"


/* Declared in icalderivedparameter.h */
/*typedef struct icalparameter_impl icalparameter;*/

/**
 * @brief Creates new icalparameter object.
 * @param kind The kind of icalparameter to create.
 * @return An icalparameter with the given kind.
 *
 * @par Error handling
 * If there was an internal error regarding
 * memory allocation, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the icalparameter_free() method.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * icalparameter *parameter = icalparameter_new();
 *
 * if(parameter) {
 *     // use parameter ...
 * }
 *
 * // release parameter
 * icalparameter_free(parameter);
 * ```
 */
LIBICAL_ICAL_EXPORT icalparameter *icalparameter_new(icalparameter_kind kind);

/**
 * @brief Creates new icalparameter as a clone of the given one.
 * @param old The existing, non-`NULL` parameter to clone.
 * @return An icalparameter that is a clone of the given one.
 *
 * @par Error handling
 * If @a old is `NULL`, it returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If there was an internal error cloning the data, it returns `NULL`
 * without reporting any error in ::icalerrno.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the icalparameter_free() method.
 *
 * @par Usage
 * ```x
 * // create an icalparameter
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * // clone the parameter
 * icalparameter *clone = icalparameter_clone(param);
 *
 * if(clone) {
 *     // use clone ...
 * }
 *
 * // release parameters
 * icalparameter_free(param);
 * icalparameter_free(clone);
 * ```
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalparameter *icalparameter_clone(const icalparameter *old);

/**
 * @brief Creates new icalparameter object from string
 * @param str The string from which to create the icalparameter, in the form `"PARAMNAME=VALUE"`
 * @return An icalparameter that corresponds to the given string.
 *
 * @par Error handling
 * If there was an internal error copying data, it returns `NULL` and sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR. If @a str was `NULL`, it returns
 * `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR. If @a str was malformed,
 * it returns `NULL` and sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the icalparameter_free() method.
 *
 * @par Usage
 * ```c
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     // use param ...
 * }
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT icalparameter *icalparameter_new_from_string(const char *str);

/**
 * @brief Creates new icalparameter of a given @a kind with a given @a value
 * @param kind The kind of icalparameter to create
 * @param value The value of the parameter
 * @return An icalparameter with the given kind and value.
 *
 * @par Error handling
 * If value is `NULL`, it returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * Objects created by this method are owned by the caller and
 * must be released with the icalparameter_free() method.
 *
 * @par Example
 * ```c
 * // create new parameter
 * icalparameter *param;
 * param = icalparameter_new_from_value_string(ICAL_ROLE_PARAMETER, "CHAIR");
 *
 * // check parameter
 * assert(0 == strcmp(icalparameter_get_iana_name(param), "ROLE"));
 * assert(0 == strcmp(icalparameter_get_iana_value(param), "CHAIR"));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT icalparameter *icalparameter_new_from_value_string(icalparameter_kind kind,
                                                                       const char *value);

/**
 * @brief Frees an icalparameter object.
 * @param parameter The icalparameter to free
 *
 * This method needs to be used on all parameter objects returned
 * from any of the `_new()` methods including icalparameter_new(),
 * icalparameter_new_from_string() and icalparameter_new_from_value_string()
 * and on cloned parameter objects returned by icalparameter_clone()
 * when these object are not needed anymore and to be released.
 *
 * @par Usage
 * ```c
 * icalparameter *param = icalparameter_new();
 *
 * if(param) {
 *     // use param...
 * }
 *
 * // after use, release it
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparameter_free(icalparameter *parameter);

/**
 * @brief Converts icalparameter into a string representation
 * @param parameter The icalparameter to convert
 * @return A string representing the parameter according to RFC5445/RFC6868.
 * @sa icalparameter_as_ical_string_r()
 *
 * @par Error handling
 * If there is any error, the method returns `NULL`. Furthermore,
 * if @a parameter is `NULL`, it also sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If it doesn't recognize the kind of the parameter, it sets ::icalerrno
 * it ::ICAL_BADARG_ERROR. If the parameter is otherwise malformed, it
 * sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Strings returned by this method are owned by libical, they must
 * not be freed and they may be reclaimed with the next call into
 * the library. A version of this function, which returns strings
 * that are not owned by libical, is icalparameter_as_ical_string_r().
 *
 * @par Usage
 * ```c
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     printf("%s\n", icalparameter_as_ical_string(param));
 * }
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icalparameter_as_ical_string(icalparameter *parameter);

/**
 * @brief Converts icalparameter into a string representation according to RFC5445/RFC6868.
 * @param parameter The icalparameter to convert
 * @return A string representing the parameter
 * @sa icalparameter_as_ical_string()
 *
 * @par Error handling
 * If there is any error, the method returns `NULL`. Furthermore,
 * if parameter is `NULL`, it also sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * If it doesn't recognize the kind of the parameter, it sets ::icalerrno
 * to ::ICAL_BADARG_ERROR. If the parameter is otherwise malformed, it
 * sets ::icalerrno to ::ICAL_MALFORMEDDATA_ERROR.
 *
 * @par Ownership
 * Strings returned by this method are owned by the caller, thus they need
 * to be manually `icalmemory_free_buffer()`d after use.
 * A version of this function which returns strings that do not
 * need to be freed manually is icalparameter_as_ical_string().
 *
 * @par Usage
 * ```c
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * if(param) {
 *     char *str = icalparameter_as_ical_string(param);
 *     printf("%s\n", str);
 *     icalmemory_free_buffer(str);
 * }
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icalparameter_as_ical_string_r(icalparameter *parameter);

/**
 * Returns the icalparameter_kind of parameter.
 *
 * @param parameter The icalparameter whose kind to determine
 * @return The icalparameter_kind of the parameter
 *
 * @b Error handling
 * Returns ICAL_NO_PARAMETER when passed NULL.
 *
 * @b Usage
 * @code
 * // create parameter
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * // check what type of parameter this is
 * assert(icalparameter_isa(param) == ICAL_ROLE_PARAMETER);
 *
 * // release memory
 * icalparameter_free(param);
 * @endcode
 */
LIBICAL_ICAL_EXPORT icalparameter_kind icalparameter_isa(const icalparameter *parameter);

/**
 * Determines if the given param is an icalparameter
 * @param param The libical-originated object to check
 * @return true if the object is an icalparameter, false otherwise.
 * @note This function expects to be given an object originating from
 *  libical - if this function is passed anything that is not from
 *  libical, its behavior is undefined.
 *
 * @b Error handling
 * When given a `NULL` object, it returns 0.
 *
 * @b Usage
 * ```c
 * // create parameter
 * icalparameter *param = icalparameter_new_from_string("ROLE=CHAIR");
 *
 * // check if it's a parameter
 * assert(icalparameter_isa_parameter(param));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalparameter_isa_parameter(void *param);

/* Access the name of an X parameter */

/**
 * @brief Sets the X-name of @a param to @a v
 * @param param The icalparameter to change
 * @param v The X-name to set @a param to
 * @sa icalparameter_get_xname()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * icalparameter *param = icalparameter_new();
 *
 * // sets xname
 * icalparameter_set_xname(param, "X-TEST");
 *
 * // compare xname
 * assert(0 == strcmp(icalparameter_get_xname(param), "X-TEST"));
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparameter_set_xname(icalparameter *param, const char *v);

/**
 * @brief Returns the X-name of @a param
 * @param param The icalparameter whose X-name is to be returned
 * @return A string representing the X-name of @a param
 * @sa icalparameter_set_xname()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an icalparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * icalparameter *param = icalparameter_new();
 *
 * // sets xname
 * icalparameter_set_xname(param, "X-TEST");
 *
 * // compare xname
 * assert(0 == strcmp(icalparameter_get_xname(param), "X-TEST"));
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalparameter_get_xname(const icalparameter *param);

/**
 * @brief Sets the X-value of @a param to @a v
 * @param param The icalparameter to change
 * @param v The X-value to set @a param to
 * @sa icalparameter_get_xvalue()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * icalparameter *param = icalparameter_new_from_string("X-TEST=FAIL");
 *
 * // set test to success
 * icalparameter_set_xvalue(param, "SUCCESS");
 *
 * // check that it worked
 * assert(0 == strcmp(icalparameter_get_xvalue(param), "SUCCESS"));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparameter_set_xvalue(icalparameter *param, const char *v);

/**
 * @brief Returns the X-value of @a param
 * @param param The icalparameter whose X-value is to be returned
 * @return A string representing the X-value of @a param
 * @sa icalparameter_set_xvalue()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an icalparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * icalparameter *param = icalparameter_new_from_string("X-TEST=FAIL");
 *
 * // set test to success
 * icalparameter_set_xvalue(param, "SUCCESS");
 *
 * // check that it worked
 * assert(0 == strcmp(icalparameter_get_xvalue(param), "SUCCESS"));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalparameter_get_xvalue(const icalparameter *param);

/* Access the name of an IANA parameter */

/**
 * @brief Sets the IANA name of @a param to @a v
 * @param param The icalparameter to change
 * @param v The IANA name to set @a param to
 * @sa icalparameter_get_iana_name()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets :calerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * icalparameter *param = icalparameter_new();
 *
 * // sets iana name
 * icalparameter_set_iana_name(param, "ROLE");
 *
 * // compare iana name
 * assert(0 == strcmp(icalparameter_get_iana_name(param), "X-TEST"));
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparameter_set_iana_name(icalparameter *param, const char *v);

/**
 * @brief Returns the IANA name of @a param
 * @param param The icalparameter whose IANA name is to be returned
 * @return A string representing the IANA name of @a param
 * @sa icalparameter_set_iana_name()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an icalparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // creates new parameter
 * icalparameter *param = icalparameter_new();
 *
 * // sets iana name
 * icalparameter_set_iana_name(param, "X-TEST");
 *
 * // compare iana name
 * assert(0 == strcmp(icalparameter_get_iana_name(param), "X-TEST"));
 *
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalparameter_get_iana_name(const icalparameter *param);

/**
 * @brief Sets the IANA value of @a param to @a v
 * @param param The icalparameter to change
 * @param v The IANA value to set @a param to
 * @sa icalparameter_get_iana_value()
 *
 * @par Error handling
 * If either @a param or @a v are `NULL`, it sets ::icalerrno to ICAL_BARARG_ERROR.
 * If there is an error acquiring memory, it sets `errno` to `ENOMEM`.
 *
 * @par Ownership
 * The passed string @a v stays in the ownership of the caller - libical
 * creates a copy of it.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * icalparameter *param = icalparameter_new_from_string("ROLE=ATTENDEE");
 *
 * // set role to chair
 * icalparameter_set_iana_value(param, "CHAIR");
 *
 * // check that it worked
 * assert(0 == strcmp(icalparameter_get_iana_value(param), "SUCCESS"));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparameter_set_iana_value(icalparameter *param, const char *v);

/**
 * @brief Returns the IANA value of @a param
 * @param param The icalparameter whose value is to be returned
 * @return A string representing the value of @a param
 * @sa icalparameter_set_iana_value()
 *
 * @par Error handling
 * Returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR when a `NULL`
 * is passed instead of an icalparameter.
 *
 * @par Ownership
 * The string that is returned stays owned by libical and must not
 * be freed by the caller.
 *
 * @par Usage
 * ```c
 * // create new parameter
 * icalparameter *param = icalparameter_new_from_string("ROLE=ATTENDEE");
 *
 * // set role to chair
 * icalparameter_set_iana_value(param, "CHAIR");
 *
 * // check that it worked
 * assert(0 == strcmp(icalparameter_get_iana_value(param), "SUCCESS"));
 *
 * // release memory
 * icalparameter_free(param);
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalparameter_get_iana_value(const icalparameter *param);

/**
 * @brief Determines if two parameters have the same name
 * @param param1 First parameter to compare
 * @param param2 Second parameter to compare
 * @return true if they have the same name, false otherwise.
 *
 * @par Error handling
 * If either of @a param1 or @a param2 are `NULL`, it returns 0 and sets
 * ::icalerrno to ::ICAL_BADARG_ERROR.
 *
 * @par Ownership
 * Does not take ownership of either icalparameter.
 *
 * @par Example
 * ```c
 * // create two parameters
 * icalparameter *param1 = icalparameter_new_from_string("ROLE=CHAIR");
 * icalparameter *param2 = icalparameter_new_from_string("EMAIL=mailto@example.com");
 *
 * // compare parameter names for equality
 * assert(icalparameter_has_same_name(param1, param2) == 0);
 *
 * // release memory
 * icalparameter_free(param1);
 * icalparameter_free(param2);
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalparameter_has_same_name(const icalparameter *param1, const icalparameter *param2);

/* Convert enumerations */

/**
 * @brief Returns a string representing the given icalparameter_kind
 * @param kind The icalparameter_kind
 * @return A string representing @a kind
 *
 * @par Error handling
 * When passed a non-existing icalparameter_kind, it returns `NULL`.
 *
 * @par Ownership
 * The string that is returned by this function is owned by libical and
 * must not be freed by the caller.
 *
 * @par Usage
 * ```c
 * assert(0 == strcmp(icalparameter_kind_to_string(ICAL_ROLE_PARAMETER), "ROLE"));
 * assert(0 == strcmp(icalparameter_kind_to_string(ICAL_EMAIL_PARAMETER), "EMAIL));
 * assert(0 == strcmp(icalparameter_kind_to_string(ICAL_ID_PARAMETER), "ID"));
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalparameter_kind_to_string(icalparameter_kind kind);

/**
 * @brief Returns the icalparameter_kind for a given string
 * @param string A string describing an icalparameter_kind
 * @return An icalparameter_kind
 *
 * @par Error handling
 * Returns ICAL_NO_PARAMETER if @a string is `NULL`.
 * If it can't find the parameter, depending on
 * the ical_get_unknown_token_handling_setting(), it returns either
 * ICAL_NO_PARAMETER or ICAL_IANA_PARAMETER.
 *
 * @par Ownership
 * Does not take ownership of @a string.
 *
 * @par Usage
 * ```c
 * assert(icalparameter_string_to_kind("ROLE")  == ICAL_ROLE_PARAMETER);
 * assert(icalparameter_string_to_kind("EMAIL") == ICAL_EMAIL_PARAMETER);
 * assert(icalparameter_string_to_kind("ID")    == ICAL_ID_PARAMETER);
 * ```
 */
LIBICAL_ICAL_EXPORT icalparameter_kind icalparameter_string_to_kind(const char *string);

/**
 * @brief Checks the validity of an icalparameter_kind
 * @param kind The icalparameter_kind
 * @return true if @a kind is valid, false otherwise
 *
 * @par Usage
 * ```c
 * assert(icalparameter_kind_is_valid(ICAL_ROLE_PARAMETER));
 * ```
 * @since 3.0.4
 */
LIBICAL_ICAL_EXPORT bool icalparameter_kind_is_valid(const icalparameter_kind kind);

/**
 * Gets the icalvalue_kind of a icalparameter_kind.
 *
 * @param kind the parameter_kind
 * @param is_multivalued an address pointing to integer that will contain a value
 *        of one if the @p kind is a multi-value; a value of zero otherwise.
 *
 * @return the icalvalue_kind of the specified icalparameter_kind. Additionally,
 * @p is_mulitivalued will indicate if the value_kind is multi-valued.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalvalue_kind icalparameter_kind_value_kind(const icalparameter_kind kind, int *is_multivalued);

/**
 * Return if the specified parameter is multivalued.
 *
 * @param param is a pointer to the icalparameter.
 *
 * @return true if the specified parameter is multivalued; false otherwise.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT bool icalparameter_is_multivalued(const icalparameter *param);

/**
 * Decode the specified char string as a parameter value per RFC6868.
 *
 * @param value is a pointer to the char string to decode.
 *
 * @p value will contain the decoded value on return.
 * No error checking is performed.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalparameter_decode_value(char *value);

#endif

/*======================================================================
 FILE: icalderivedproperty.h
 CREATOR: eric 09 May 1999

 SPDX-FileCopyrightText: 1999, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 ======================================================================*/

/**
 * @file icalderivedproperty.h
 * @brief ICalendar properties.
 */

#ifndef ICALDERIVEDPROPERTY_H
#define ICALDERIVEDPROPERTY_H

#include "libical_sentinel.h"


#include <stdbool.h>

typedef struct icalproperty_impl icalproperty;

typedef enum icalproperty_kind {
    ICAL_ANY_PROPERTY = 0,
    ICAL_ACCEPTRESPONSE_PROPERTY = 102,
    ICAL_ACKNOWLEDGED_PROPERTY = 1,
    ICAL_ACTION_PROPERTY = 2,
    ICAL_ALLOWCONFLICT_PROPERTY = 3,
    ICAL_ATTACH_PROPERTY = 4,
    ICAL_ATTENDEE_PROPERTY = 5,
    ICAL_BUSYTYPE_PROPERTY = 101,
    ICAL_CALENDARADDRESS_PROPERTY = 130,
    ICAL_CALID_PROPERTY = 6,
    ICAL_CALMASTER_PROPERTY = 7,
    ICAL_CALSCALE_PROPERTY = 8,
    ICAL_CAPVERSION_PROPERTY = 9,
    ICAL_CARLEVEL_PROPERTY = 10,
    ICAL_CARID_PROPERTY = 11,
    ICAL_CATEGORIES_PROPERTY = 12,
    ICAL_CLASS_PROPERTY = 13,
    ICAL_CMD_PROPERTY = 14,
    ICAL_COLOR_PROPERTY = 118,
    ICAL_COMMENT_PROPERTY = 15,
    ICAL_COMPLETED_PROPERTY = 16,
    ICAL_COMPONENTS_PROPERTY = 17,
    ICAL_CONCEPT_PROPERTY = 133,
    ICAL_CONFERENCE_PROPERTY = 120,
    ICAL_CONTACT_PROPERTY = 18,
    ICAL_CREATED_PROPERTY = 19,
    ICAL_CSID_PROPERTY = 20,
    ICAL_DATEMAX_PROPERTY = 21,
    ICAL_DATEMIN_PROPERTY = 22,
    ICAL_DECREED_PROPERTY = 23,
    ICAL_DEFAULTCHARSET_PROPERTY = 24,
    ICAL_DEFAULTLOCALE_PROPERTY = 25,
    ICAL_DEFAULTTZID_PROPERTY = 26,
    ICAL_DEFAULTVCARS_PROPERTY = 27,
    ICAL_DENY_PROPERTY = 28,
    ICAL_DESCRIPTION_PROPERTY = 29,
    ICAL_DTEND_PROPERTY = 30,
    ICAL_DTSTAMP_PROPERTY = 31,
    ICAL_DTSTART_PROPERTY = 32,
    ICAL_DUE_PROPERTY = 33,
    ICAL_DURATION_PROPERTY = 34,
    ICAL_ESTIMATEDDURATION_PROPERTY = 113,
    ICAL_EXDATE_PROPERTY = 35,
    ICAL_EXPAND_PROPERTY = 36,
    ICAL_EXRULE_PROPERTY = 37,
    ICAL_FREEBUSY_PROPERTY = 38,
    ICAL_GEO_PROPERTY = 39,
    ICAL_GRANT_PROPERTY = 40,
    ICAL_IANA_PROPERTY = 136,
    ICAL_IMAGE_PROPERTY = 119,
    ICAL_ITIPVERSION_PROPERTY = 41,
    ICAL_LASTMODIFIED_PROPERTY = 42,
    ICAL_LINK_PROPERTY = 134,
    ICAL_LOCATION_PROPERTY = 43,
    ICAL_LOCATIONTYPE_PROPERTY = 127,
    ICAL_MAXCOMPONENTSIZE_PROPERTY = 44,
    ICAL_MAXDATE_PROPERTY = 45,
    ICAL_MAXRESULTS_PROPERTY = 46,
    ICAL_MAXRESULTSSIZE_PROPERTY = 47,
    ICAL_METHOD_PROPERTY = 48,
    ICAL_MINDATE_PROPERTY = 49,
    ICAL_MULTIPART_PROPERTY = 50,
    ICAL_NAME_PROPERTY = 115,
    ICAL_ORGANIZER_PROPERTY = 52,
    ICAL_OWNER_PROPERTY = 53,
    ICAL_PARTICIPANTTYPE_PROPERTY = 128,
    ICAL_PATCHDELETE_PROPERTY = 124,
    ICAL_PATCHORDER_PROPERTY = 122,
    ICAL_PATCHPARAMETER_PROPERTY = 125,
    ICAL_PATCHTARGET_PROPERTY = 123,
    ICAL_PATCHVERSION_PROPERTY = 121,
    ICAL_PERCENTCOMPLETE_PROPERTY = 54,
    ICAL_PERMISSION_PROPERTY = 55,
    ICAL_POLLCOMPLETION_PROPERTY = 110,
    ICAL_POLLITEMID_PROPERTY = 103,
    ICAL_POLLMODE_PROPERTY = 104,
    ICAL_POLLPROPERTIES_PROPERTY = 105,
    ICAL_POLLWINNER_PROPERTY = 106,
    ICAL_PRIORITY_PROPERTY = 56,
    ICAL_PRODID_PROPERTY = 57,
    ICAL_PROXIMITY_PROPERTY = 126,
    ICAL_QUERY_PROPERTY = 58,
    ICAL_QUERYLEVEL_PROPERTY = 59,
    ICAL_QUERYID_PROPERTY = 60,
    ICAL_QUERYNAME_PROPERTY = 61,
    ICAL_RDATE_PROPERTY = 62,
    ICAL_RECURACCEPTED_PROPERTY = 63,
    ICAL_RECUREXPAND_PROPERTY = 64,
    ICAL_RECURLIMIT_PROPERTY = 65,
    ICAL_RECURRENCEID_PROPERTY = 66,
    ICAL_REFID_PROPERTY = 135,
    ICAL_REFRESHINTERVAL_PROPERTY = 116,
    ICAL_RELATEDTO_PROPERTY = 67,
    ICAL_RELCALID_PROPERTY = 68,
    ICAL_REPEAT_PROPERTY = 69,
    ICAL_REPLYURL_PROPERTY = 111,
    ICAL_REQUESTSTATUS_PROPERTY = 70,
    ICAL_RESOURCETYPE_PROPERTY = 129,
    ICAL_RESOURCES_PROPERTY = 71,
    ICAL_RESPONSE_PROPERTY = 112,
    ICAL_RESTRICTION_PROPERTY = 72,
    ICAL_RRULE_PROPERTY = 73,
    ICAL_SCOPE_PROPERTY = 74,
    ICAL_SEQUENCE_PROPERTY = 75,
    ICAL_SOURCE_PROPERTY = 117,
    ICAL_STATUS_PROPERTY = 76,
    ICAL_STORESEXPANDED_PROPERTY = 77,
    ICAL_STRUCTUREDDATA_PROPERTY = 132,
    ICAL_STYLEDDESCRIPTION_PROPERTY = 131,
    ICAL_SUMMARY_PROPERTY = 78,
    ICAL_TARGET_PROPERTY = 79,
    ICAL_TASKMODE_PROPERTY = 114,
    ICAL_TRANSP_PROPERTY = 80,
    ICAL_TRIGGER_PROPERTY = 81,
    ICAL_TZID_PROPERTY = 82,
    ICAL_TZIDALIASOF_PROPERTY = 108,
    ICAL_TZNAME_PROPERTY = 83,
    ICAL_TZOFFSETFROM_PROPERTY = 84,
    ICAL_TZOFFSETTO_PROPERTY = 85,
    ICAL_TZUNTIL_PROPERTY = 109,
    ICAL_TZURL_PROPERTY = 86,
    ICAL_UID_PROPERTY = 87,
    ICAL_URL_PROPERTY = 88,
    ICAL_VERSION_PROPERTY = 89,
    ICAL_VOTER_PROPERTY = 107,
    ICAL_X_PROPERTY = 90,
    ICAL_XLICCLASS_PROPERTY = 91,
    ICAL_XLICCLUSTERCOUNT_PROPERTY = 92,
    ICAL_XLICERROR_PROPERTY = 93,
    ICAL_XLICMIMECHARSET_PROPERTY = 94,
    ICAL_XLICMIMECID_PROPERTY = 95,
    ICAL_XLICMIMECONTENTTYPE_PROPERTY = 96,
    ICAL_XLICMIMEENCODING_PROPERTY = 97,
    ICAL_XLICMIMEFILENAME_PROPERTY = 98,
    ICAL_XLICMIMEOPTINFO_PROPERTY = 99,
    ICAL_NO_PROPERTY = 100
} icalproperty_kind;

/* ACCEPT-RESPONSE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_acceptresponse(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_acceptresponse(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_acceptresponse(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_acceptresponse(const char * v, ...);

/* ACKNOWLEDGED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_acknowledged(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_acknowledged(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_acknowledged(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_acknowledged(struct icaltimetype v, ...);

/* ACTION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_action(enum icalproperty_action v);
LIBICAL_ICAL_EXPORT void icalproperty_set_action(icalproperty *prop, enum icalproperty_action v);
LIBICAL_ICAL_EXPORT enum icalproperty_action icalproperty_get_action(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_action(enum icalproperty_action v, ...);

/* ALLOW-CONFLICT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_allowconflict(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_allowconflict(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_allowconflict(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_allowconflict(const char * v, ...);

/* ATTACH */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_attach(icalattach * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_attach(icalproperty *prop, icalattach * v);
LIBICAL_ICAL_EXPORT icalattach * icalproperty_get_attach(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_attach(icalattach * v, ...);

/* ATTENDEE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_attendee(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_attendee(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_attendee(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_attendee(const char * v, ...);

/* BUSYTYPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_busytype(enum icalproperty_busytype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_busytype(icalproperty *prop, enum icalproperty_busytype v);
LIBICAL_ICAL_EXPORT enum icalproperty_busytype icalproperty_get_busytype(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_busytype(enum icalproperty_busytype v, ...);

/* CALENDAR-ADDRESS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_calendaraddress(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_calendaraddress(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_calendaraddress(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_calendaraddress(const char * v, ...);

/* CALID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_calid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_calid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_calid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_calid(const char * v, ...);

/* CALMASTER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_calmaster(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_calmaster(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_calmaster(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_calmaster(const char * v, ...);

/* CALSCALE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_calscale(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_calscale(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_calscale(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_calscale(const char * v, ...);

/* CAP-VERSION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_capversion(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_capversion(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_capversion(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_capversion(const char * v, ...);

/* CAR-LEVEL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_carlevel(enum icalproperty_carlevel v);
LIBICAL_ICAL_EXPORT void icalproperty_set_carlevel(icalproperty *prop, enum icalproperty_carlevel v);
LIBICAL_ICAL_EXPORT enum icalproperty_carlevel icalproperty_get_carlevel(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_carlevel(enum icalproperty_carlevel v, ...);

/* CARID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_carid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_carid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_carid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_carid(const char * v, ...);

/* CATEGORIES */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_categories(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_categories(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_categories(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_categories(const char * v, ...);

/* CLASS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_class(enum icalproperty_class v);
LIBICAL_ICAL_EXPORT void icalproperty_set_class(icalproperty *prop, enum icalproperty_class v);
LIBICAL_ICAL_EXPORT enum icalproperty_class icalproperty_get_class(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_class(enum icalproperty_class v, ...);

/* CMD */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_cmd(enum icalproperty_cmd v);
LIBICAL_ICAL_EXPORT void icalproperty_set_cmd(icalproperty *prop, enum icalproperty_cmd v);
LIBICAL_ICAL_EXPORT enum icalproperty_cmd icalproperty_get_cmd(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_cmd(enum icalproperty_cmd v, ...);

/* COLOR */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_color(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_color(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_color(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_color(const char * v, ...);

/* COMMENT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_comment(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_comment(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_comment(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_comment(const char * v, ...);

/* COMPLETED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_completed(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_completed(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_completed(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_completed(struct icaltimetype v, ...);

/* COMPONENTS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_components(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_components(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_components(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_components(const char * v, ...);

/* CONCEPT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_concept(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_concept(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_concept(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_concept(const char * v, ...);

/* CONFERENCE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_conference(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_conference(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_conference(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_conference(const char * v, ...);

/* CONTACT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_contact(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_contact(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_contact(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_contact(const char * v, ...);

/* CREATED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_created(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_created(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_created(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_created(struct icaltimetype v, ...);

/* CSID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_csid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_csid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_csid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_csid(const char * v, ...);

/* DATE-MAX */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_datemax(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_datemax(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_datemax(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_datemax(struct icaltimetype v, ...);

/* DATE-MIN */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_datemin(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_datemin(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_datemin(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_datemin(struct icaltimetype v, ...);

/* DECREED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_decreed(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_decreed(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_decreed(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_decreed(const char * v, ...);

/* DEFAULT-CHARSET */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_defaultcharset(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_defaultcharset(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_defaultcharset(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_defaultcharset(const char * v, ...);

/* DEFAULT-LOCALE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_defaultlocale(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_defaultlocale(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_defaultlocale(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_defaultlocale(const char * v, ...);

/* DEFAULT-TZID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_defaulttzid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_defaulttzid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_defaulttzid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_defaulttzid(const char * v, ...);

/* DEFAULT-VCARS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_defaultvcars(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_defaultvcars(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_defaultvcars(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_defaultvcars(const char * v, ...);

/* DENY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_deny(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_deny(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_deny(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_deny(const char * v, ...);

/* DESCRIPTION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_description(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_description(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_description(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_description(const char * v, ...);

/* DTEND */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_dtend(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_dtend(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_dtend(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_dtend(struct icaltimetype v, ...);

/* DTSTAMP */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_dtstamp(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_dtstamp(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_dtstamp(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_dtstamp(struct icaltimetype v, ...);

/* DTSTART */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_dtstart(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_dtstart(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_dtstart(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_dtstart(struct icaltimetype v, ...);

/* DUE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_due(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_due(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_due(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_due(struct icaltimetype v, ...);

/* DURATION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_duration(struct icaldurationtype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_duration(icalproperty *prop, struct icaldurationtype v);
LIBICAL_ICAL_EXPORT struct icaldurationtype icalproperty_get_duration(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_duration(struct icaldurationtype v, ...);

/* ESTIMATED-DURATION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_estimatedduration(struct icaldurationtype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_estimatedduration(icalproperty *prop, struct icaldurationtype v);
LIBICAL_ICAL_EXPORT struct icaldurationtype icalproperty_get_estimatedduration(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_estimatedduration(struct icaldurationtype v, ...);

/* EXDATE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_exdate(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_exdate(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_exdate(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_exdate(struct icaltimetype v, ...);

/* EXPAND */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_expand(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_expand(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_expand(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_expand(int v, ...);

/* EXRULE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_exrule(struct icalrecurrencetype * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_exrule(icalproperty *prop, struct icalrecurrencetype * v);
LIBICAL_ICAL_EXPORT struct icalrecurrencetype * icalproperty_get_exrule(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_exrule(struct icalrecurrencetype * v, ...);

/* FREEBUSY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_freebusy(struct icalperiodtype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_freebusy(icalproperty *prop, struct icalperiodtype v);
LIBICAL_ICAL_EXPORT struct icalperiodtype icalproperty_get_freebusy(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_freebusy(struct icalperiodtype v, ...);

/* GEO */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_geo(struct icalgeotype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_geo(icalproperty *prop, struct icalgeotype v);
LIBICAL_ICAL_EXPORT struct icalgeotype icalproperty_get_geo(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_geo(struct icalgeotype v, ...);

/* GRANT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_grant(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_grant(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_grant(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_grant(const char * v, ...);

/* IANA */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_iana(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_iana(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_iana(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_iana(const char * v, ...);

/* IMAGE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_image(icalattach * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_image(icalproperty *prop, icalattach * v);
LIBICAL_ICAL_EXPORT icalattach * icalproperty_get_image(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_image(icalattach * v, ...);

/* ITIP-VERSION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_itipversion(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_itipversion(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_itipversion(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_itipversion(const char * v, ...);

/* LAST-MODIFIED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_lastmodified(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_lastmodified(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_lastmodified(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_lastmodified(struct icaltimetype v, ...);

/* LINK */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_link(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_link(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_link(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_link(const char * v, ...);

/* LOCATION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_location(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_location(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_location(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_location(const char * v, ...);

/* LOCATION-TYPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_locationtype(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_locationtype(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_locationtype(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_locationtype(const char * v, ...);

/* MAX-COMPONENT-SIZE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_maxcomponentsize(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_maxcomponentsize(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_maxcomponentsize(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_maxcomponentsize(int v, ...);

/* MAXDATE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_maxdate(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_maxdate(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_maxdate(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_maxdate(struct icaltimetype v, ...);

/* MAXRESULTS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_maxresults(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_maxresults(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_maxresults(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_maxresults(int v, ...);

/* MAXRESULTSSIZE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_maxresultssize(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_maxresultssize(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_maxresultssize(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_maxresultssize(int v, ...);

/* METHOD */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_method(enum icalproperty_method v);
LIBICAL_ICAL_EXPORT void icalproperty_set_method(icalproperty *prop, enum icalproperty_method v);
LIBICAL_ICAL_EXPORT enum icalproperty_method icalproperty_get_method(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_method(enum icalproperty_method v, ...);

/* MINDATE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_mindate(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_mindate(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_mindate(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_mindate(struct icaltimetype v, ...);

/* MULTIPART */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_multipart(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_multipart(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_multipart(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_multipart(const char * v, ...);

/* NAME */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_name(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_name(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_name(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_name(const char * v, ...);

/* ORGANIZER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_organizer(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_organizer(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_organizer(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_organizer(const char * v, ...);

/* OWNER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_owner(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_owner(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_owner(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_owner(const char * v, ...);

/* PARTICIPANT-TYPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_participanttype(enum icalproperty_participanttype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_participanttype(icalproperty *prop, enum icalproperty_participanttype v);
LIBICAL_ICAL_EXPORT enum icalproperty_participanttype icalproperty_get_participanttype(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_participanttype(enum icalproperty_participanttype v, ...);

/* PATCH-DELETE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_patchdelete(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_patchdelete(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_patchdelete(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_patchdelete(const char * v, ...);

/* PATCH-ORDER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_patchorder(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_patchorder(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_patchorder(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_patchorder(int v, ...);

/* PATCH-PARAMETER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_patchparameter(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_patchparameter(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_patchparameter(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_patchparameter(const char * v, ...);

/* PATCH-TARGET */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_patchtarget(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_patchtarget(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_patchtarget(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_patchtarget(const char * v, ...);

/* PATCH-VERSION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_patchversion(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_patchversion(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_patchversion(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_patchversion(const char * v, ...);

/* PERCENT-COMPLETE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_percentcomplete(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_percentcomplete(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_percentcomplete(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_percentcomplete(int v, ...);

/* PERMISSION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_permission(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_permission(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_permission(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_permission(const char * v, ...);

/* POLL-COMPLETION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_pollcompletion(enum icalproperty_pollcompletion v);
LIBICAL_ICAL_EXPORT void icalproperty_set_pollcompletion(icalproperty *prop, enum icalproperty_pollcompletion v);
LIBICAL_ICAL_EXPORT enum icalproperty_pollcompletion icalproperty_get_pollcompletion(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_pollcompletion(enum icalproperty_pollcompletion v, ...);

/* POLL-ITEM-ID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_pollitemid(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_pollitemid(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_pollitemid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_pollitemid(int v, ...);

/* POLL-MODE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_pollmode(enum icalproperty_pollmode v);
LIBICAL_ICAL_EXPORT void icalproperty_set_pollmode(icalproperty *prop, enum icalproperty_pollmode v);
LIBICAL_ICAL_EXPORT enum icalproperty_pollmode icalproperty_get_pollmode(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_pollmode(enum icalproperty_pollmode v, ...);

/* POLL-PROPERTIES */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_pollproperties(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_pollproperties(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_pollproperties(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_pollproperties(const char * v, ...);

/* POLL-WINNER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_pollwinner(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_pollwinner(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_pollwinner(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_pollwinner(int v, ...);

/* PRIORITY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_priority(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_priority(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_priority(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_priority(int v, ...);

/* PRODID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_prodid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_prodid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_prodid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_prodid(const char * v, ...);

/* PROXIMITY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_proximity(enum icalproperty_proximity v);
LIBICAL_ICAL_EXPORT void icalproperty_set_proximity(icalproperty *prop, enum icalproperty_proximity v);
LIBICAL_ICAL_EXPORT enum icalproperty_proximity icalproperty_get_proximity(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_proximity(enum icalproperty_proximity v, ...);

/* QUERY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_query(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_query(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_query(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_query(const char * v, ...);

/* QUERY-LEVEL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_querylevel(enum icalproperty_querylevel v);
LIBICAL_ICAL_EXPORT void icalproperty_set_querylevel(icalproperty *prop, enum icalproperty_querylevel v);
LIBICAL_ICAL_EXPORT enum icalproperty_querylevel icalproperty_get_querylevel(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_querylevel(enum icalproperty_querylevel v, ...);

/* QUERYID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_queryid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_queryid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_queryid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_queryid(const char * v, ...);

/* QUERYNAME */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_queryname(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_queryname(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_queryname(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_queryname(const char * v, ...);

/* RDATE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_rdate(struct icaldatetimeperiodtype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_rdate(icalproperty *prop, struct icaldatetimeperiodtype v);
LIBICAL_ICAL_EXPORT struct icaldatetimeperiodtype icalproperty_get_rdate(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_rdate(struct icaldatetimeperiodtype v, ...);

/* RECUR-ACCEPTED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_recuraccepted(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_recuraccepted(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_recuraccepted(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_recuraccepted(const char * v, ...);

/* RECUR-EXPAND */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_recurexpand(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_recurexpand(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_recurexpand(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_recurexpand(const char * v, ...);

/* RECUR-LIMIT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_recurlimit(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_recurlimit(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_recurlimit(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_recurlimit(const char * v, ...);

/* RECURRENCE-ID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_recurrenceid(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_recurrenceid(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_recurrenceid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_recurrenceid(struct icaltimetype v, ...);

/* REFID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_refid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_refid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_refid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_refid(const char * v, ...);

/* REFRESH-INTERVAL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_refreshinterval(struct icaldurationtype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_refreshinterval(icalproperty *prop, struct icaldurationtype v);
LIBICAL_ICAL_EXPORT struct icaldurationtype icalproperty_get_refreshinterval(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_refreshinterval(struct icaldurationtype v, ...);

/* RELATED-TO */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_relatedto(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_relatedto(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_relatedto(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_relatedto(const char * v, ...);

/* RELCALID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_relcalid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_relcalid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_relcalid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_relcalid(const char * v, ...);

/* REPEAT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_repeat(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_repeat(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_repeat(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_repeat(int v, ...);

/* REPLY-URL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_replyurl(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_replyurl(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_replyurl(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_replyurl(const char * v, ...);

/* REQUEST-STATUS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_requeststatus(struct icalreqstattype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_requeststatus(icalproperty *prop, struct icalreqstattype v);
LIBICAL_ICAL_EXPORT struct icalreqstattype icalproperty_get_requeststatus(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_requeststatus(struct icalreqstattype v, ...);

/* RESOURCE-TYPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_resourcetype(enum icalproperty_resourcetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_resourcetype(icalproperty *prop, enum icalproperty_resourcetype v);
LIBICAL_ICAL_EXPORT enum icalproperty_resourcetype icalproperty_get_resourcetype(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_resourcetype(enum icalproperty_resourcetype v, ...);

/* RESOURCES */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_resources(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_resources(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_resources(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_resources(const char * v, ...);

/* RESPONSE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_response(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_response(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_response(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_response(int v, ...);

/* RESTRICTION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_restriction(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_restriction(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_restriction(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_restriction(const char * v, ...);

/* RRULE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_rrule(struct icalrecurrencetype * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_rrule(icalproperty *prop, struct icalrecurrencetype * v);
LIBICAL_ICAL_EXPORT struct icalrecurrencetype * icalproperty_get_rrule(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_rrule(struct icalrecurrencetype * v, ...);

/* SCOPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_scope(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_scope(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_scope(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_scope(const char * v, ...);

/* SEQUENCE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_sequence(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_sequence(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_sequence(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_sequence(int v, ...);

/* SOURCE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_source(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_source(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_source(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_source(const char * v, ...);

/* STATUS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_status(enum icalproperty_status v);
LIBICAL_ICAL_EXPORT void icalproperty_set_status(icalproperty *prop, enum icalproperty_status v);
LIBICAL_ICAL_EXPORT enum icalproperty_status icalproperty_get_status(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_status(enum icalproperty_status v, ...);

/* STORES-EXPANDED */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_storesexpanded(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_storesexpanded(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_storesexpanded(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_storesexpanded(const char * v, ...);

/* STRUCTURED-DATA */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_structureddata(icalattach * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_structureddata(icalproperty *prop, icalattach * v);
LIBICAL_ICAL_EXPORT icalattach * icalproperty_get_structureddata(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_structureddata(icalattach * v, ...);

/* STYLED-DESCRIPTION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_styleddescription(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_styleddescription(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_styleddescription(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_styleddescription(const char * v, ...);

/* SUMMARY */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_summary(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_summary(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_summary(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_summary(const char * v, ...);

/* TARGET */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_target(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_target(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_target(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_target(const char * v, ...);

/* TASK-MODE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_taskmode(enum icalproperty_taskmode v);
LIBICAL_ICAL_EXPORT void icalproperty_set_taskmode(icalproperty *prop, enum icalproperty_taskmode v);
LIBICAL_ICAL_EXPORT enum icalproperty_taskmode icalproperty_get_taskmode(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_taskmode(enum icalproperty_taskmode v, ...);

/* TRANSP */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_transp(enum icalproperty_transp v);
LIBICAL_ICAL_EXPORT void icalproperty_set_transp(icalproperty *prop, enum icalproperty_transp v);
LIBICAL_ICAL_EXPORT enum icalproperty_transp icalproperty_get_transp(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_transp(enum icalproperty_transp v, ...);

/* TRIGGER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_trigger(struct icaltriggertype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_trigger(icalproperty *prop, struct icaltriggertype v);
LIBICAL_ICAL_EXPORT struct icaltriggertype icalproperty_get_trigger(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_trigger(struct icaltriggertype v, ...);

/* TZID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_tzid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzid(const char * v, ...);

/* TZID-ALIAS-OF */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzidaliasof(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzidaliasof(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_tzidaliasof(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzidaliasof(const char * v, ...);

/* TZNAME */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzname(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzname(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_tzname(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzname(const char * v, ...);

/* TZOFFSETFROM */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzoffsetfrom(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzoffsetfrom(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_tzoffsetfrom(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzoffsetfrom(int v, ...);

/* TZOFFSETTO */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzoffsetto(int v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzoffsetto(icalproperty *prop, int v);
LIBICAL_ICAL_EXPORT int icalproperty_get_tzoffsetto(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzoffsetto(int v, ...);

/* TZUNTIL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzuntil(struct icaltimetype v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzuntil(icalproperty *prop, struct icaltimetype v);
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_tzuntil(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzuntil(struct icaltimetype v, ...);

/* TZURL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_tzurl(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_tzurl(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_tzurl(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_tzurl(const char * v, ...);

/* UID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_uid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_uid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_uid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_uid(const char * v, ...);

/* URL */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_url(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_url(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_url(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_url(const char * v, ...);

/* VERSION */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_version(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_version(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_version(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_version(const char * v, ...);

/* VOTER */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_voter(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_voter(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_voter(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_voter(const char * v, ...);

/* X */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_x(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_x(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_x(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_x(const char * v, ...);

/* X-LIC-CLASS */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicclass(enum icalproperty_xlicclass v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicclass(icalproperty *prop, enum icalproperty_xlicclass v);
LIBICAL_ICAL_EXPORT enum icalproperty_xlicclass icalproperty_get_xlicclass(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicclass(enum icalproperty_xlicclass v, ...);

/* X-LIC-CLUSTERCOUNT */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicclustercount(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicclustercount(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicclustercount(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicclustercount(const char * v, ...);

/* X-LIC-ERROR */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicerror(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicerror(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicerror(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicerror(const char * v, ...);

/* X-LIC-MIMECHARSET */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimecharset(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimecharset(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimecharset(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimecharset(const char * v, ...);

/* X-LIC-MIMECID */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimecid(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimecid(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimecid(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimecid(const char * v, ...);

/* X-LIC-MIMECONTENTTYPE */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimecontenttype(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimecontenttype(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimecontenttype(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimecontenttype(const char * v, ...);

/* X-LIC-MIMEENCODING */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimeencoding(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimeencoding(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimeencoding(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimeencoding(const char * v, ...);

/* X-LIC-MIMEFILENAME */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimefilename(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimefilename(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimefilename(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimefilename(const char * v, ...);

/* X-LIC-MIMEOPTINFO */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_xlicmimeoptinfo(const char * v);
LIBICAL_ICAL_EXPORT void icalproperty_set_xlicmimeoptinfo(icalproperty *prop, const char * v);
LIBICAL_ICAL_EXPORT const char * icalproperty_get_xlicmimeoptinfo(const icalproperty *prop);
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalproperty *icalproperty_vanew_xlicmimeoptinfo(const char * v, ...);

#endif /*ICALPROPERTY_H*/

/*======================================================================
 FILE: icalproperty.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalproperty.h
 * @brief Defines the data structure representing iCalendar properties.
 */

#ifndef ICALPROPERTY_H
#define ICALPROPERTY_H

#include "libical_ical_export.h"
 /* To get icalproperty_kind enumerations */

#include <stdarg.h> /* for va_... */

/// @cond PRIVATE
/* This is exposed so that callers will not have to allocate and
 *   deallocate iterators. Pretend that you can't see it. */
struct icalpvl_elem_t;
typedef struct icalparamiter {
    icalparameter_kind kind;
    struct icalpvl_elem_t *iter;
} icalparamiter;
/// @endcond

/**
 * Construct a new icalproperty of the specified icalproperty_kind.
 *
 * @param kind is the icalproperty_kind to use
 *
 * @return a pointer to the newly allocated icalproperty. The data structure
 * contains all null values and is essentially invalid.
 * Free the resulting memory with icalproperty_free.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new(icalproperty_kind kind);

/**
 * Deeply clones an icalproperty.
 *
 * @param old a pointer to the icalproperty to clone
 * @return a pointer to the memory for the newly cloned icalproperty.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_clone(const icalproperty *old);

/**
 * Construct and populate a new icalproperty from a char string.
 *
 * @param str a non-NULL pointer to the data used to populate the new icalproperty.
 *
 * @return a pointer to the newly allocated icalproperty. Free the resulting
 * memory with icalproperty_free.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalproperty_new_from_string(const char *str);

/**
 * Stringify an icalproperty.
 *
 * @param prop a pointer to an icalproperty
 *
 * @return a pointer to a char string containing the string representation of @p prop.
 * NULL is returned is @p prop is invalid.
 *
 * @see icalproperty_as_ical_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_as_ical_string(icalproperty *prop);

/**
 * Stringify an icalproperty.
 *
 * @param prop a pointer to an icalproperty
 *
 * @return a pointer to a char string containing the string representation of @p prop.
 * NULL is returned is @p prop is invalid.
 *
 * @see icalproperty_as_ical_string
 */
LIBICAL_ICAL_EXPORT char *icalproperty_as_ical_string_r(icalproperty *prop);

/**
 * Free the memory for an icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 */
LIBICAL_ICAL_EXPORT void icalproperty_free(icalproperty *prop);

/**
 * Determines the icalproperty_kind of the specified icalproperty.
 *
 * @param property a pointer to valid icalproperty.
 *
 * @return the icalproperty_kind of @p property; ICAL_NO_PROPERTY is
 * returned if @p property is NULL.
 */
LIBICAL_ICAL_EXPORT icalproperty_kind icalproperty_isa(const icalproperty *property);

/**
 * Determines if the specified pointer is an icalproperty pointer.
 *
 * Just looks if the ::id member strncmps to "prop".
 *
 * @param property a pointer, presumably to an icalproperty.
 *
 * @return true if the pointer looks like an icalproperty; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalproperty_isa_property(void *property);

/**
 * Adds a list of parameter to the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty.
 * @param args a va_list of pointers that presumably point to list of
 * valid icalparameters.
 *
 * If any item in @p va_list points to an illegal icalparameter the internal
 * library ::icalerrno is set to ::ICAL_BADARG_ERROR.
 *
 * Any item in @p va_list points to an icalvalue is ignored.
 */
LIBICAL_ICAL_EXPORT void icalproperty_add_parameters(icalproperty *prop, va_list args);

/**
 * Adds a parameter to the specified icalproperty.
 *
 * No error checking is performed by this function.
 *
 * @param prop a pointer to a valid icalproperty
 * @param parameter a pointer to a presumably valid icalparameter
 */
LIBICAL_ICAL_EXPORT void icalproperty_add_parameter(icalproperty *prop, icalparameter *parameter);

/**
 * Adds an icalparameter to an icalproperty.
 *
 * No error checking is performed by this function.
 *
 * @param prop a pointer to a valid icalproperty
 * @param parameter a pointer to a presumably valid icalparameter
 *
 * If @p parameter kind is already attached to @p prop then the old
 * parameter is removed in favor of @p parameter.
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_parameter(icalproperty *prop, icalparameter *parameter);

/**
 * Sets a icalparameter from a string for the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 * @param name a pointer to a char string containing the parameter name
 * @param value a pointer to a char string containing the parameter value
 *
 * If @p name refers to an invalid icalparameter_kind or @p value is illegal,
 * then the internal library ::icalerrno is set to ::ICAL_BADARG_ERROR.
 *
 * @see icalproperty_get_parameter_as_string
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_parameter_from_string(icalproperty *prop,
                                                                const char *name,
                                                                const char *value);

/**
 * Gets the parameter value for a specified icalproperty parameter.
 *
 * @param prop a pointer to a valid icalproperty
 * @param name a a pointer to a char string containing the name of icalparameter to use
 *
 * @return a pointer to a char string containing the value for the specified
 * icalparameter name; NULL is returned is @p name refers to an invalid
 * icalproperty_kind.
 *
 * @see icalproperty_get_parameter_as_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_get_parameter_as_string(icalproperty *prop,
                                                                     const char *name);

/**
 * Gets the parameter value for a specified icalproperty parameter.
 *
 * @param prop a pointer to a valid icalproperty
 * @param name a pointer to a char string containing the name of icalparameter to use
 *
 * @return a pointer to a char string containing the value for the specified
 * icalparameter name; NULL is returned is @p name refers to an invalid
 * icalproperty_kind.
 *
 * @see icalproperty_get_parameter_as_string
 */
LIBICAL_ICAL_EXPORT char *icalproperty_get_parameter_as_string_r(icalproperty *prop,
                                                                 const char *name);

/** @brief Removes all parameters with the specified kind.
 *
 *  @param prop   A valid icalproperty.
 *  @param kind   The kind to remove (ex. ICAL_TZID_PARAMETER)
 *
 *  See icalproperty_remove_parameter_by_name() and
 *  icalproperty_remove_parameter_by_ref() for alternate ways of
 *  removing parameters
 */
LIBICAL_ICAL_EXPORT void icalproperty_remove_parameter_by_kind(icalproperty *prop,
                                                               icalparameter_kind kind);

/** @brief Removes all parameters with the specified name.
 *
 *  @param prop   A valid icalproperty.
 *  @param name   The name of the parameter to remove
 *
 *  This function removes parameters with the given name.  The name
 *  corresponds to either a built-in name (TZID, etc.) or the name of
 *  an extended parameter (X-FOO)
 *
 *  See icalproperty_remove_parameter_by_kind() and
 *  icalproperty_remove_parameter_by_ref() for alternate ways of removing
 *  parameters
 */
LIBICAL_ICAL_EXPORT void icalproperty_remove_parameter_by_name(icalproperty *prop,
                                                               const char *name);

/** @brief Removes the specified parameter reference from the property.
 *
 *  @param prop   A valid icalproperty.
 *  @param param  A reference to a specific icalparameter.
 *
 *  This function removes the specified parameter reference from the
 *  property.
 */
LIBICAL_ICAL_EXPORT void icalproperty_remove_parameter_by_ref(icalproperty *prop,
                                                              icalparameter *param);

/**
 * Gets the number of parameter for a specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return the number of parameters attached to @p prop.
 * Returns -1 if @p prop is NULL.
 */
LIBICAL_ICAL_EXPORT int icalproperty_count_parameters(const icalproperty *prop);

/* Iterate through the parameters */

/**
 * From the head position, iterates the icalparameter list attached to the
 * specified icalproperty until the first icalparameter_kind is found.
 *
 * @param prop a pointer to a valid icalproperty
 * @param kind an icalparameter_kind to use for the search
 *
 * @return a pointer to the first icalparameter found of icalparameter_kind @p kind
;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalparameter *icalproperty_get_first_parameter(icalproperty *prop,
                                                                    icalparameter_kind kind);

/**
 * From the current position, iterates the icalparameter list attached to the
 * specified icalproperty until the next icalparameter_kind is found.
 *
 * @param prop a pointer to a valid icalproperty
 * @param kind an icalparameter_kind to use for the search
 *
 * @return a pointer to the next icalparameter found of icalparamter_kind @p kind;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalparameter *icalproperty_get_next_parameter(icalproperty *prop,
                                                                   icalparameter_kind kind);

/* Access the value of the property */

/**
 * Sets an icalvalue for the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 * @param value a pointer to a valid icalvalue to use
 *
 * If @p prop already has an icalvalue it will be replaced.
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_value(icalproperty *prop, icalvalue *value);

/**
 * Sets an icalvalue for the specified icalproperty from a char string..
 *
 * @param prop a pointer to a valid icalproperty
 * @param str a non-NULL pointer to char string to be converted to the icalvalue
 * @param type a non-NULL pointer to a char string to be converted to an icalvalue_kind
 *
 * If @p type string matches "NO" then the icalvalue_kind will be taken
 * from an existing icalvalue (if one exists) or will use the default
 * icalvalue_kind for the icalproperty.
 *
 * If @p prop already has an icalvalue it will be replaced.
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_value_from_string(icalproperty *prop, const char *str,
                                                            const char *type);

/**
 * Gets the icalvalue for the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return a pointer the @p prop icalvalue; or NULL if @p prop does not
 * have an attached icalvalue yet.
 */
LIBICAL_ICAL_EXPORT icalvalue *icalproperty_get_value(const icalproperty *prop);

/**
 * Gets the icalvalue for the specified icalproperty as a char string.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return a pointer the string-converted @p prop icalvalue; or NULL
 * if @p prop does not have an attached icalvalue yet.
 *
 * @see icalproperty_get_value_as_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_get_value_as_string(const icalproperty *prop);

/**
 * Gets the icalvalue for the specified icalproperty as a char string.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return a pointer the string-converted @p prop icalvalue; or NULL
 * if @p prop does not have an attached icalvalue yet.
 *
 * @see icalproperty_get_value_as_string
 */
LIBICAL_ICAL_EXPORT char *icalproperty_get_value_as_string_r(const icalproperty *prop);

/**
 * Sets the parent @p icalproperty for the specified @p icalvalue.
 *
 * @param value a pointer to a valid icalvalue
 * @param property a pointer to a presumably valid icalproperty to use
 */
LIBICAL_ICAL_EXPORT void icalvalue_set_parent(icalvalue *value, icalproperty *property);

/**
 * Gets the parent icalproperty of the specified icalvalue.
 *
 * @param value a pointer to the icalvalue
 *
 * @return the parent @p icalproperty for the specified @p icalvalue.
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT icalproperty *icalvalue_get_parent(const icalvalue *value);

/* Deal with X properties */

/**
 * Sets the X-NAME property of the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 * @param name a pointer to a char string to use as the X-NAME
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_x_name(icalproperty *prop, const char *name);

/**
 * Gets the X-NAME icalproperty of the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return a pointer to a char string containing the X-NAME property.
 * Will be NULL if an X-NAME property has not been set yet.
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_get_x_name(const icalproperty *prop);

/* Deal with IANA properties */

/**
 * Sets the IANA name for an icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 * @param name a pointer to char string containing the IANA name.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_iana_name(icalproperty *prop, const char *name);

/**
 * Gets the IANA name of the specified icalproperty.
 *
 * @param prop a pointer to a valid icalproperty
 *
 * @return a pointer to a char string containing the @p comp IANA name; will be NULL if the
 * name has yet to be specified.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_get_iana_name(const icalproperty *prop);

/**
 * Gets the name of the specified icalproperty.
 *
 * Returns the name of the property -- the type name converted to a
 * string, or the value of _get_x_name if the type is and X property.
 *
 * @param prop a pointer to the icalproperty
 *
 * @return a pointer to a string containing the icalproperty's name.
 *
 * @see icalproperty_get_property_name_r
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_get_property_name(const icalproperty *prop);

/**
 * Gets the name of the specified icalproperty.
 *
 * Returns the name of the property -- the type name converted to a
 * string, or the value of _get_x_name if the type is and X property.
 *
 * @param prop a pointer to the icalproperty
 *
 * @return a pointer to a string containing the icalproperty's name.
 *
 * @see icalproperty_get_property_name
 */
LIBICAL_ICAL_EXPORT char *icalproperty_get_property_name_r(const icalproperty *prop);

/**
 * Converts an icalparameter_value to an icalvalue_kind.
 *
 * @param value the icalparameter_value to use
 *
 * @return the icalvalue_kind conversion from @p value; returns ICAL_NO_VALUE
 * if @p value is invalid.
 */
LIBICAL_ICAL_EXPORT icalvalue_kind icalparameter_value_to_value_kind(icalparameter_value value);

/**
 * Sets the parent icalproperty for the specified icalparameter.
 *
 * @param param a pointer to a valid icalparameter
 * @param property a pointer to a presumably valid icalproperty to use
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT void icalparameter_set_parent(icalparameter *param, icalproperty *property);

/**
 * Gets the parent icalproperty of an icalparameter.
 *
 * @param param a pointer to the icalparameter
 *
 * @return the parent @p icalproperty for the specified @p icalparameter.
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT icalproperty *icalparameter_get_parent(const icalparameter *param);

/* Convert kinds to string and get default value type */

/**
 * Converts an icalproperty_kind to an icalvalue_kind.
 *
 * @param kind is the icalproperty_kind to use
 *
 * @return the icalvalue_kind from @p kind; returns ICAL_NO_VALUE if
 * @p kind is invalid.
 */
LIBICAL_ICAL_EXPORT icalvalue_kind icalproperty_kind_to_value_kind(icalproperty_kind kind);

/**
 * Converts an icalvalue_kind to an icalproperty_kind.
 *
 * @param kind is the icalvalue_kind to use
 *
 * @return the icalproperty_kind from @p kind; returns ICAL_NO_PROPERTY if
 * @p kind is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_kind icalproperty_value_kind_to_kind(icalvalue_kind kind);

/**
 * Converts an icalproperty_kind to its string representation.
 *
 * @param kind is the icalproperty_kind to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_kind.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_kind_to_string(icalproperty_kind kind);

/**
 * Converts a char string into an icalproperty_kind.
 *
 * @param string a pointer to a char string containing the character representati
on
 * of an icalproperty_kind
 *
 * @return the icalproperty_kind associated with @p string.
 * ICAL_NO_PROPERTY is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_kind icalproperty_string_to_kind(const char *string);

/**
 * Check validity of a specified icalproperty_kind.
 *
 * @param kind is the icalproperty_kind
 *
 * @return true if the specified icalproperty_kind is valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalproperty_kind_is_valid(const icalproperty_kind kind);

/**
 * Converts a char string into an icalproperty_method.
 *
 * @param str a pointer to a char string containing the character representati
on
 * of an icalproperty_method
 *
 * @return the icalproperty_method associated with @p string.
 * ICAL_METHOD_NONE is returned if @p str is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_method icalproperty_string_to_method(const char *str);

/**
 * Converts an icalproperty_method to its string representation.
 *
 * @param method is the icalproperty_method to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_method.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_method_to_string(icalproperty_method method);

/**
 * Converts an integer representing some icalproperty type to its
 * string representation.
 *
 * @param e is an integer between ICALPROPERTY_FIRST_ENUM and ICALPROPERTY_LAST_ENUM, inclusive.
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty type.
 *
 * @see icalproperty_enum_to_string_r
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_enum_to_string(int e);

/**
 * Converts an integer representing some icalproperty type to its
 * string representation.
 *
 * @param e is an integer between ICALPROPERTY_FIRST_ENUM and ICALPROPERTY_LAST_ENUM, inclusive.
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty type.
 *
 * @see icalproperty_enum_to_string
 */
LIBICAL_ICAL_EXPORT char *icalproperty_enum_to_string_r(int e);

/**
 * Converts an integer representation of an icalvalue_kind enum along
 * with a string representation of an icalproperty_kind to an integer
 * representation of an icalproperty enum.
 *
 * @param kind is a integer representation of an icalvalue_kind
 * @param str is a non-NULL pointer to a char string containing
 * the string representation of the icalproperty enum.
 *
 * @return an integer representation of an icalproperty_kind enum; returns
 * zero if @p kind is invalid.
 */
LIBICAL_ICAL_EXPORT int icalproperty_kind_and_string_to_enum(const int kind, const char *str);

/**
 * Converts an icalproperty_status to its string representation.
 *
 * @param status is the icalproperty_status to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_status.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_status_to_string(icalproperty_status status);

/**
 * Converts a char string into an icalproperty_status.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalproperty_status
 *
 * @return the icalproperty_status associated with @p string.
 * ICAL_STATUS_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_status icalproperty_string_to_status(const char *string);

/**
 * Converts an icalproperty_action to its string representation.
 *
 * @param action is the icalproperty_action to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_action.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_action_to_string(icalproperty_action action);

/**
 * Converts a char string into an icalproperty_action.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalproperty_action
 *
 * @return the icalproperty_action associated with @p string.
 * ICAL_ACTION_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_action icalproperty_string_to_action(const char *string);

/**
 * Converts an icalproperty_transp to its string representation.
 *
 * @param transp is the icalproperty_transp to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_transp.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_transp_to_string(icalproperty_transp transp);

/**
 * Converts a char string into an icalproperty_transp.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalproperty_transp
 *
 * @return the icalproperty_transp associated with @p string.
 * ICAL_TRANSP_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_transp icalproperty_string_to_transp(const char *string);

/**
 * Converts an icalproperty_class to its string representation.
 *
 * @param propclass is the icalproperty_class to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_class.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_class_to_string(icalproperty_class propclass);

/**
 * Converts a char string into an icalproperty_class.
 *
 * @param string a pointer to a char string containing the character representati
on
 * of an icalproperty_class_
 *
 * @return the icalproperty_class associated with @p string.
 * ICAL_CLASS_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_class icalproperty_string_to_class(const char *string);

/**
 * Converts an icalproperty_participanttype to its string representation.
 *
 * @param participanttype is the icalproperty_participanttype to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_participanttype.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_participanttype_to_string(icalproperty_participanttype participanttype);

/**
 * Converts a char string into an icalproperty_participanttype.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalproperty_participanttype
 *
 * @return the icalproperty_participanttype associated with @p string.
 * ICAL_PARTICIPANTTYPE_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_participanttype icalproperty_string_to_participanttype(const char *string);

/**
 * Converts an icalproperty_resourcetype to its string representation.
 *
 * @param resourcetype is the icalproperty_resourcetype to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalproperty_resourcetype.
 */
LIBICAL_ICAL_EXPORT const char *icalproperty_resourcetype_to_string(icalproperty_resourcetype resourcetype);

/**
 * Converts a char string into an icalproperty_resourcetype.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalproperty_resourcetype
 *
 * @return the icalproperty_resourcetype associated with @p string.
 * ICAL_RESOURCETYPE_NONE is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty_resourcetype icalproperty_string_to_resourcetype(const char *string);

/**
 * Determines if a integer ia a valid enum for a specified icalproperty_kind.
 *
 * @param kind is the icalproperty_kind
 * @param e is a an integer to validate as an enum of type icalproperty_kind
 *
 * @return true if the specified integer is a valid enum for icalproperty_kind;
 * false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalproperty_enum_belongs_to_property(icalproperty_kind kind, int e);

/**
 * Normalizes (reorders and sorts the parameters) the specified icalproperty.
 *
 * @param prop a pointer a valid icalproperty
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT void icalproperty_normalize(icalproperty *prop);

/**
 * Sets if empty properties are permitted.
 *
 * Determines the library behavior whenever an empty property is encountered.
 * When not set (the default) empty properties are replaced with X-LIC-ERROR properties.
 * Otherwise, processing proceeds normally and the property value will be empty.
 *
 * @param enable If true, libical allows empty properties; otherwise empty properties
 *               are replaced by X-LIC-ERROR properties.
 *
 * Note that if icalerror_get_errors_are_fatal is also true a SIGABRT will be raised
 * whenever an empty property is encountered.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_allow_empty_properties(bool enable);

/**
 * Returns if empty properties are allowed; else are replaced with X-LIC-ERROR properties.
 *
 * @return true if empty properties are allowed; else returns false
 * @since 4.0
 *
 */
LIBICAL_ICAL_EXPORT bool icalproperty_get_allow_empty_properties(void);

/// @cond PRIVATE
LIBICAL_ICAL_EXPORT icalparamiter icalproperty_begin_parameter(icalproperty *property, icalparameter_kind kind);

LIBICAL_ICAL_EXPORT icalparameter *icalparamiter_next(icalparamiter *i);

LIBICAL_ICAL_EXPORT icalparameter *icalparamiter_deref(icalparamiter *i);
/// @endcond

#endif /*ICALPROPERTY_H */

/*======================================================================
 FILE: icalcomponent.h
 CREATOR: eric 20 March 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalcomponent.h
 * @brief Defines the data structure for iCalendar components
 */

#ifndef ICALCOMPONENT_H
#define ICALCOMPONENT_H

#include "libical_sentinel.h"
#include "libical_ical_export.h"


typedef struct icalcomponent_impl icalcomponent;

/* These are exposed so that callers will not have to allocate and
   deallocate iterators. Pretend that you can't see them. */
/// @cond PRIVATE
struct icalpvl_elem_t;
typedef struct icalcompiter {
    icalcomponent_kind kind;
    struct icalpvl_elem_t *iter;
} icalcompiter;

typedef struct icalpropiter {
    icalproperty_kind kind;
    struct icalpvl_elem_t *iter;
} icalpropiter;
/// @endcond

/**
 * Constructs a new icalcomponent of a specified kind.
 *
 * The data structure contains all null values and is essentially invalid.
 * Free the allocated memory with icalcomponent_free.
 *
 * @param kind is the icalcompent_kind to construct
 *
 * @return a pointer to a valid icalcomponent.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new(icalcomponent_kind kind);

/**
 * Deeply clones an icalcomponent.
 *
 * Free the allocated memory with icalcomponent_free.
 *
 * @param old a pointer to a valid icalcomponent
 *
 * @return a pointer to the memory for the newly cloned icalcomponent.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_clone(const icalcomponent *old);

/**
 * Construct a new icalcomponent from a character string.
 *
 * Free the allocated memory with icalcomponent_free.
 *
 * @param str a char string containing a properly formatted ICS calendar.
 *
 * @return a pointer to an icalcomponent or NULL if an anomaly was encountered.
 * To handle parse errors, set the ::icalparser_state to ::ICALPARSER_ERROR
 * and/or return components of the type ::ICAL_XLICINVALID_COMPONENT,
 * or components with properties of the type ICAL_XLICERROR_PROPERTY.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_from_string(const char *str);

/**
 * Construct a new icalcomponent from a list of icalproperties of icalcomponents.
 *
 * Free the allocated memory with icalcomponent_free.
 * Make sure to pass NULL (not 0) as the final argument!
 *
 * @param kind the icalcomponent_kind of icalcomponent to use
 *
 * @return a pointer to an icalcomponent. NULL .
 */
LIBICAL_ICAL_EXPORT LIBICAL_SENTINEL icalcomponent *icalcomponent_vanew(icalcomponent_kind kind, ...);

/**
 * Construct a new X-NAME icalcomponent.
 *
 * Free the allocated memory with icalcomponent_free.
 *
 * @param x_name a pointer to a char string containing the value for the "X-NAME"
 *
 * @return a pointer to a valid icalcomponent.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_x(const char *x_name);

/**
 * Construct a new icalcomponent with an IANA component name.
 *
 * @param iana_name a pointer to a char string containing the IANA name.
 *
 * @return A pointer to a new icalcomponent; or NULL on memory allocation failure.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_iana(const char *iana_name);

/**
 * Destruct the specified icalcomponent.
 *
 * Frees the memory alloced for the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcompent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_free(icalcomponent *component);

/**
 * Creates a character string representation of an icalcomponent.
 *
 * @param component a pointer to a icalcomponent
 *
 * @return a pointer to a char string containing the @p component string
 * representation; NULL if a memory allocation failure is encountered.
 *
 * @see icalcomponent_as_ical_string_r
 */
LIBICAL_ICAL_EXPORT char *icalcomponent_as_ical_string(const icalcomponent *component);

/**
 * Creates a character string representation of an icalcomponent.
 *
 * @param component a pointer to a icalcomponent
 *
 * @return a pointer to a char string containing the @p component string
 * representation; NULL if a memory allocation failure is encountered.
 *
 * @see icalcomponent_as_ical_string
 */
LIBICAL_ICAL_EXPORT char *icalcomponent_as_ical_string_r(const icalcomponent *component);

/**
 * Determines if the specified icalcomponent is valid.
 *
 * @param component a pointer to possibly invalid icalcomponent
 *
 * @return true if @p component is valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalcomponent_is_valid(const icalcomponent *component);

/**
 * Determines the icalcomponent_kind of the specified icalcomponent.
 *
 * @param component a pointer to valid icalcomponent.
 *
 * @return the icalcomponent_kind of @p component.
 */
LIBICAL_ICAL_EXPORT icalcomponent_kind icalcomponent_isa(const icalcomponent *component);

/**
 * Determines if the specified pointer is an icalcomponent pointer.
 *
 * Just looks if the ::id member strncmps to "comp".
 *
 * @param component a pointer, presumably to an icalcomponent.
 *
 * @return true if the pointer looks like an icalcomponent; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalcomponent_isa_component(const void *component);

/* Deal with X components */

/**
 * Sets the X-NAME property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param name a non-NULL pointer to a char string containing the X-NAME to use.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_x_name(icalcomponent *comp, const char *name);

/**
 * Gets the X-NAME property of an icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return pointer to a char string with the X-NAME property for @p comp.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_x_name(const icalcomponent *comp);

/* Deal with IANA components */

/**
 * Sets the IANA name for an icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param name a pointer to char string containing the IANA name.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_iana_name(icalcomponent *comp, const char *name);

/**
 * Gets the IANA name of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a pointer to a char string containing the @p comp IANA name; will be NULL if the
 * name has yet to be specified.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_iana_name(const icalcomponent *comp);

/**
 * Gets the name of the specified icalcomponent.
 *
 * The icalcomponent's name is its type name converted to a string,
 * or the value of _get_x_name if is an X- component type.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a pointer to a char string with the name of the specified icalcomponent.
 * @see icalcomponent_get_component_name_r
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_component_name(const icalcomponent *comp);

/**
 * Gets the name of the specified icalcomponent.
 *
 * The icalcomponent's name is its type name converted to a string,
 * or the value of _get_x_name if is an X- component type.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a pointer to a char string with the name of the specified icalcomponent.
 * @see icalcomponent_get_component_name
 */
LIBICAL_ICAL_EXPORT char *icalcomponent_get_component_name_r(const icalcomponent *comp);

/***** Working with Properties *****/

/**
 * Adds an icalproperty to the specified icalcomponent.
 *
 * No error checking is performed by this function, although it will
 * assert if the specified icalproperty has already been added.
 *
 * @param component a pointer to a valid icalcomponent
 * @param property a pointer to a presumably valid icalproperty
 */
LIBICAL_ICAL_EXPORT void icalcomponent_add_property(icalcomponent *component,
                                                    icalproperty *property);

/**
 * Removes an icalproperty from the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param property a pointer to the icalproperty to remove
 */
LIBICAL_ICAL_EXPORT void icalcomponent_remove_property(icalcomponent *component,
                                                       icalproperty *property);

/**
 * Removes all icalproperty's of an icalproperty_kind from the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind is the icalproperty_kind to use
 */
LIBICAL_ICAL_EXPORT void icalcomponent_remove_property_by_kind(icalcomponent *component,
                                                               icalproperty_kind kind);

/**
 * Gets the number of properties of an icalproperty_kind in an icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind the ical_property_kind to use for the search
 *
 * @return the number of @p kind property types attached to @p component.
 */
LIBICAL_ICAL_EXPORT int icalcomponent_count_properties(icalcomponent *component,
                                                       icalproperty_kind kind);

/**
 * Sets the parent icalcomponent for the specified icalproperty.
 *
 * @param property a pointer to a valid icalproperty
 * @param component a pointer to a valid icalcomponent to use as the parent
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT void icalproperty_set_parent(icalproperty *property,
                                                 icalcomponent *component);

/**
 * Gets the parent icalcomponent for the specified icalproperty.
 *
 * @param property a pointer to a valid icalproperty
 *
 * @return a pointer to the parent icalcomponent of the specified icalproperty.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalproperty_get_parent(const icalproperty *property);

/* Iterate through the properties */

/**
 * Gets the icalproperty associated to the current icalpropiter of the
 * specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 *
 * @return a pointer to the current icalproperty or NULL if the current
 * icalpropiter is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalcomponent_get_current_property(icalcomponent *component);

/**
 * From the head position, iterates the icalproperty list attached to the
 * specified icalcomponent until the first icalproperty_kind is found.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind an icalproperty_kind to use for the search
 *
 * @return a pointer to the first icalproperty found of icalproperty_kind @p kind;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalcomponent_get_first_property(icalcomponent *component,
                                                                   icalproperty_kind kind);

/**
 * From the current position, iterates the icalproperty list attached to the
 * specified icalcomponent until the next icalproperty_kind is found.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind an icalproperty_kind to use for the search
 *
 * @return a pointer to the next icalproperty found of icalproperty_kind @p kind;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalcomponent_get_next_property(icalcomponent *component,
                                                                  icalproperty_kind kind);

/***** Working with Components *****/

/**
 * Gets a pointer to the first VEVENT, VTODO or VJOURNAL sub-component
 * located in the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a pointer to the first VEVENT, VTODO or VJOURNAL located in
 * the specified icalcomponent. @p comp itself returned if it is found to
 * be a VEVENT, VTODO or VJOURNAL. NULL is returned if the search failed.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_inner(icalcomponent *comp);

/**
 * Attaches a child icalcomponent to a parent icalcomponent
 *
 * @param parent a pointer to a valid parent icalcomponent
 * @param child a pointer to a valid child icalcomponent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_add_component(icalcomponent *parent, icalcomponent *child);

/**
 * Detaches a child icalcomponent from a parent icalcomponent
 *
 * @param parent a pointer to a valid parent icalcomponent
 * @param child a pointer to a valid child icalcomponent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_remove_component(icalcomponent *parent,
                                                        icalcomponent *child);

/**
 * Gets the number of components of an icalcomponent_kind in an icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind the icalcomponent_kind to use for the search
 *
 * @return the number of @p kind component types attached to @p component.
 */
LIBICAL_ICAL_EXPORT int icalcomponent_count_components(icalcomponent *component,
                                                       icalcomponent_kind kind);

/**
 * Merges two VCALENDAR components.
 *
 * This takes 2 VCALENDAR components and merges the second one into the first,
 * resolving any problems with conflicting TZIDs. comp_to_merge will no
 * longer exist after calling this function.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param comp_to_merge a pointer to a valid icalcompent to merge into @p comp
 */
LIBICAL_ICAL_EXPORT void icalcomponent_merge_component(icalcomponent *comp,
                                                       icalcomponent *comp_to_merge);

/* Iteration Routines. There are two forms of iterators, internal and
external. The internal ones came first, and are almost completely
sufficient, but they fail badly when you want to construct a loop that
removes components from the container.*/

/* Iterate through components */

/**
 * Gets the icalcomponent associated to the current icalcompiter of the
 * specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 *
 * @return a pointer to the current icalcomponent
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_current_component(icalcomponent *component);

/**
 * From the head position, iterates the icalcomponent list attached to the
 * specified icalcomponent until the first icalcomponent_kind is found.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind an icalcomponent_kind to use for the search
 *
 * @return a pointer to the first icalcomponent found of icalcomponent_kind @p kind;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_first_component(icalcomponent *component,
                                                                     icalcomponent_kind kind);

/**
 * From the current position, iterates the icalcomponent list attached to the
 * specified icalcomponent until the next icalcomponent_kind is found.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind an icalcomponent_kind to use for the search
 *
 * @return a pointer to the next icalcomponent found of icalcomponent_kind @p kind;
 * NULL if no matches are found.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_next_component(icalcomponent *component,
                                                                    icalcomponent_kind kind);

/* Using external iterators */

/**
 * Gets an icalcompiter associated to the first icalcomponent with icalcomponent_kind
 * attached to the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind the icalcomponent_kind to use for the search
 *
 * @return an icalcompiter for the first component found with icalcomponent_kind @p kind;
 * Use icalcompiter_is_valid() to determine if the return value is valid.
 */
LIBICAL_ICAL_EXPORT icalcompiter icalcomponent_begin_component(icalcomponent *component,
                                                               icalcomponent_kind kind);

/**
 * Gets an icalcompiter associated to the last icalcomponent with icalcomponent_kind
 * attached to the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind the icalcomponent_kind to use for the search
 *
 * @return an icalcompiter for the last component found with icalcomponent_kind
 * @p kind; if no matches are found ::icalcompiter_null is returned.
 */
LIBICAL_ICAL_EXPORT icalcompiter icalcomponent_end_component(icalcomponent *component,
                                                             icalcomponent_kind kind);

/**
 * Gets the next icalcomponent referenced by the specified icalcompiter with
 * a matching icalcomponent_kind.
 *
 * @param i a pointer to a valid icalcomponent
 *
 * @return a pointer to the next icalcomponent with a matching icalcomponent_kind
 * after the one referenced by @p i. NULL is returned if @p is invalid or if
 * there are no matches found.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcompiter_next(icalcompiter *i);

/**
 * Gets the previous icalcomponent referenced by the specified icalcompiter with
 * a matching icalcomponent_kind.
 *
 * @param i a pointer to a valid icalcomponent
 *
 * @return a pointer to the previous icalcomponent with a matching icalcomponent_kind
 * before the one referenced by @p i. NULL is returned if @p is invalid or if
 * there are no matches found.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcompiter_prior(icalcompiter *i);

/**
 * Gets the current icalcomponent referenced by the specified icalcompiter.
 *
 * @param i a pointer to a valid icalcompiter
 *
 * @return a pointer to the icalcomponent associated to @p i or NULL
 * if @p i is invalid.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcompiter_deref(icalcompiter *i);

/**
 * Checks if the specified icalcompiter is valid.
 *
 * @param i a pointer to a possibly invalid icalcompiter
 *
 * @return true if @p i points to a valid icalcompiter; false otherwise.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT bool icalcompiter_is_valid(const icalcompiter *i);

/**
 * Gets an icalpropiter associated to the first icalproperty with icalproperty_kind
 * attached to the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 * @param kind the ical_property_kind to use for the search
 *
 * @return an icalpropiter for the first property found with icalproperty_kind @p kind;
 * Use icalpropiter_is_valid() to determine if the return value is valid.
 */
LIBICAL_ICAL_EXPORT icalpropiter icalcomponent_begin_property(icalcomponent *component,
                                                              icalproperty_kind kind);

/**
 * Gets the next icalproperty referenced by the specified icalpropiter with
 * a matching icalproperty_kind.
 *
 * @param i a pointer to a valid icalpropiter
 *
 * @return a pointer to the next icalproperty with a matching icalproperty_kind
 * after the one referenced by @p i. NULL is returned if @p is invalid or if
 * there are no matches found.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalpropiter_next(icalpropiter *i);

/**
 * Gets the current icalproperty referenced by the specified icalpropiter.
 *
 * @param i a pointer to a valid icalpropiter
 *
 * @return a pointer to the icalproperty associated to @p i or NULL
 * if @p i is invalid.
 */
LIBICAL_ICAL_EXPORT icalproperty *icalpropiter_deref(icalpropiter *i);

/**
 * Checks if the specified icalpropiter is valid.
 *
 * @param i a pointer to a possibly invalid icalpropiter
 *
 * @return true if @p i points to a valid icalpropiter; false otherwise.
 *
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT bool icalpropiter_is_valid(const icalpropiter *i);

/***** Working with embedded error properties *****/

/* Check the component against itip rules and insert error properties */
/* Working with embedded error properties */

/**
 * Checks restrictions on the specified icalcomponent
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return true if @p comp is a VCALENDAR component and it has restrictions;
 * other false is returned. If a non-VCALENDER component is encountered
 * the internal library ::icalerrno is set to ::ICAL_BADARG_ERROR.
 */
LIBICAL_ICAL_EXPORT bool icalcomponent_check_restrictions(icalcomponent *comp);

/**
 * Gets the number of errors encountered parsing the data.
 *
 * @param component a pointer to a valid icalcomponent
 *
 * @return the number of X-LIC-ERROR instances in the specified icalcomponent.
 */
LIBICAL_ICAL_EXPORT int icalcomponent_count_errors(icalcomponent *component);

/**
 * Removes all X-LIC-ERROR properties in an icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_strip_errors(icalcomponent *component);

/**
 * Converts X-LIC-ERROR into RETURN-STATUS properties in an icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_convert_errors(icalcomponent *component);

/// @cond PRIVATE
/* Internal operations. They are private, and you should not be using them. */

/**
 * Gets the parent icalcomponent for the specified icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent
 *
 * @return a pointer to the parent icalcomponent of @p component.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_parent(const icalcomponent *component);

/**
 * Sets the parent icalcomponent for another icalcomponent.
 *
 * @param component a pointer to a valid icalcomponent to use as the child
 * @param parent a pointer to a valid icalcomponent to use as the parent
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_parent(icalcomponent *component,
                                                  icalcomponent *parent);

/// @endcond

/* Kind conversion routines */

/**
 * Check the validity of the specified icalcomponent_kind.
 *
 * @param kind is the icalcomponent_kind to use
 *
 * @return true if the icalcomponent_kind is valid; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icalcomponent_kind_is_valid(const icalcomponent_kind kind);

/**
 * Converts a char string into an icalcomponent_kind.
 *
 * @param string a pointer to a char string containing the character representation
 * of an icalcomponent_kind
 *
 * @return the icalcomponent_kind associated with @p string. ::ICAL_NO_COMPONENT
 * is returned if @p string is invalid.
 */
LIBICAL_ICAL_EXPORT icalcomponent_kind icalcomponent_string_to_kind(const char *string);

/**
 * Converts an icalcomponent_kind to its string representation.
 *
 * @param kind is the icalcomponent_kind to use
 *
 * @return a pointer to a char string containing the string representation
 * of the specified icalcomponent_kind.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_kind_to_string(icalcomponent_kind kind);

/************* Derived class methods.  ****************************

If the code was in an OO language, the remaining routines would be
members of classes derived from icalcomponent. Don't call them on the
wrong component subtypes. */

/**
 * Get a reference to the first VEVENT, VTODO or VJOURNAL in an icalcomponent.
 *
 * @param c a pointer to a valid icalcomponent
 *
 * @return a pointer to the first VEVENT, VTODO or VJOURNAL found
 * in the specified icalcomponent, or NULL if none are found.
 *
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_get_first_real_component(const icalcomponent *c);

/**
 * Gets the timespan covered by the specified icalcomponent, in UTC.
 *
 * See icalcomponent_foreach_recurrence() for a better way to
 * extract spans from a component.
 *
 * This method can be called on either a VCALENDAR or any real
 * component. If the VCALENDAR contains no real component, but
 * contains a VTIMEZONE, we return that span instead.
 * This might not be a desirable behavior; we keep it for now
 * for backward compatibility, but it might be deprecated at a
 * future time.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * FIXME this API needs to be clarified. DTEND is defined as the
 * first available time after the end of this event, so the span
 * should actually end 1 second before DTEND.
 *
 * @return the timespan in icaltime_span covered by the specified icalcomponent.
 *
 * @see icalcomponent_foreach_recurrence
 *
 */
LIBICAL_ICAL_EXPORT struct icaltime_span icalcomponent_get_span(icalcomponent *comp);

/******************** Convenience routines **********************/

/**
 * Sets the DTSTART property for the specified icalcomponent.
 *
 * This method respects the icaltime type (DATE vs DATE-TIME) and
 * timezone (or lack thereof).
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icaltimetype to use as the DSTART property
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_dtstart(icalcomponent *comp, struct icaltimetype v);

/**
 * Gets the DTSTART property of an icalcomponent.
 *
 * If DTSTART is a DATE-TIME with a timezone parameter and a
 * corresponding VTIMEZONE is present in the component, the
 * returned component will already be in the correct timezone;
 * otherwise the caller is responsible for converting it.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * FIXME this is useless until we can flag the failure
 *
 * @return the DTSTART as an icaltimetype of the specified icalcomponent.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalcomponent_get_dtstart(icalcomponent *comp);

/* For the icalcomponent routines only, dtend and duration are tied
   together. If you call the get routine for one and the other exists,
   the routine will calculate the return value. That is, if there is a
   DTEND and you call get_duration, the routine will return the difference
   between DTEND and DTSTART. However, if you call a set routine for
   one and the other exists, no action will be taken and icalerrno will
   be set to ICAL_MALFORMEDDATA_ERROR. If you call a set routine and
   neither exists, the routine will create the appropriate property. */

/**
 * Gets the DTEND property of an icalcomponent.
 *
 * If a DTEND property is not present but a DURATION is, we use
 * that to determine the proper end.
 *
 * If DTSTART is a DATE-TIME with a timezone parameter and a
 * corresponding VTIMEZONE is present in the component, the
 * returned component will already be in the correct timezone;
 * otherwise the caller is responsible for converting it.
 *
 * For the icalcomponent routines only, dtend and duration are tied
 * together. If you call the get routine for one and the other
 * exists, the routine will calculate the return value. That is, if
 * there is a DTEND and you call get_duration, the routine will
 * return the difference between DTEND and DTSTART.
 *
 * When DURATION and DTEND are both missing, for VEVENT an implicit
 * DTEND is calculated based of DTSTART; for AVAILABLE, VAVAILABILITY,
 * and VFREEBUSY null-time is returned.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return null-time, unless called on AVAILABLE, VEVENT,
 * VAVAILABILITY, or VFREEBUSY components.
 *
 * FIXME this is useless until we can flag the failure
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalcomponent_get_dtend(icalcomponent *comp);

/**
 * Sets the DTEND property for the specified icalcomponent.
 *
 * This method respects the icaltime type (DATE vs DATE-TIME) and
 * timezone (or lack thereof).
 *
 * This also checks that a DURATION property isn't already there,
 * and returns an error if it is. It's the caller's responsibility
 * to remove it.
 *
 * For the icalcomponent routines only, DTEND and DURATION are tied
 * together. If you call this routine and DURATION exists, no action
 * will be taken and icalerrno will be set to ICAL_MALFORMEDDATA_ERROR.
 * If neither exists, the routine will create the appropriate
 * property.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icaltimetype to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_dtend(icalcomponent *comp, struct icaltimetype v);

/**
 * Gets the DUE property of a VTODO icalcomponent.
 *
 * @param comp a pointer to a valid VTODO icalcomponent
 *
 * Uses the DUE property if it exists, otherwise we calculate the DUE
 * value by adding the task's duration to the DTSTART time.
 *
 * @return the DURATION as an icaltimetype of the specified icalcomponent
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalcomponent_get_due(icalcomponent *comp);

/**
 * Sets the due date of a VTODO task.
 *
 * @param comp a pointer to a valid VTODO icalcomponent
 * @param v    a valid due date time.
 *
 * The DUE and DURATION properties are tied together:
 * - If no duration or due properties then sets the DUE property.
 * - If a DUE property is already set, then resets it to the value v.
 * - If a DURATION property is already set, then calculates the new
 *   duration based on the supplied value of @p v.
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_due(icalcomponent *comp, struct icaltimetype v);

/**
 * Sets the DURATION property for the specified icalcomponent.
 *
 * This method respects the icaltime type (DATE vs DATE-TIME) and
 * timezone (or lack thereof).
 *
 * This also checks that a DTEND property isn't already there,
 * and returns an error if it is. It's the caller's responsibility
 * to remove it.
 *
 * For the icalcomponent routines only, DTEND and DURATION are tied
 * together. If you call this routine and DTEND exists, no action
 * will be taken and icalerrno will be set to ICAL_MALFORMEDDATA_ERROR.
 * If neither exists, the routine will create the appropriate  property.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icalduration type DURATION to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_duration(icalcomponent *comp,
                                                    struct icaldurationtype v);

/**
 * Gets the DURATION property of an icalcomponent.
 *
 * For the icalcomponent routines only, DTEND and DURATION are tied
 * together. If you call the get routine for one and the other
 * exists, the routine will calculate the return value. That is, if
 * there is a DTEND and you call get_duration, the routine will return
 * the difference between DTEND and DTSTART in AVAILABLE, VEVENT, or
 * VAVAILABILITY; and the difference between DUE and DTSTART in VTODO.
 * When both DURATION and DTEND are missing from VEVENT an implicit
 * duration is returned, based on the value-type of DTSTART. Otherwise
 * null-duration is returned.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return the DURATION as an icalduration of the specified icalcomponent.
 */
LIBICAL_ICAL_EXPORT struct icaldurationtype icalcomponent_get_duration(icalcomponent *comp);

/**
 * Sets the METHOD property of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param method is the icalproperty_method METHOD property to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_method(icalcomponent *comp, icalproperty_method method);

/**
 * Gets the METHOD property of an icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return an icalproperty_method with the METHOD property for @p comp.
 * If there is no such property then a value of ICAL_METHOD_NONE is returned.
 * If @p comp is invalid then a value of ICAL_METHOD_NONE is returned
 * and the internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT icalproperty_method icalcomponent_get_method(icalcomponent *comp);

/**
 * Gets the DTSTAMP property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return an icaltimetype with the DTSTAMP property for @p comp.
 * If there is no such property then a value of `icaltime_null_time()` is
 * returned.
 * If @p comp is invalid then a value of `icaltime_null_time()` is returned
 * and the internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalcomponent_get_dtstamp(icalcomponent *comp);

/**
 * Sets the DTSTAMP property of an icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icaltimetype to use as the DTSTAMP property
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_dtstamp(icalcomponent *comp, struct icaltimetype v);

/**
 * Sets the SUMMARY property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to a char string with the SUMMARY to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_summary(icalcomponent *comp, const char *v);

/**
 * Gets the SUMMARY property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return pointer to a char string with the SUMMARY property for @p comp.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_summary(icalcomponent *comp);

/**
 * Sets the COMMENT property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to a char string with the COMMENT to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_comment(icalcomponent *comp, const char *v);

/**
 * Gets the COMMENT property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return pointer to a char string with the COMMENT property for @p comp.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_comment(icalcomponent *comp);

/**
 * Sets the UID property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to a char string with the UID to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_uid(icalcomponent *comp, const char *v);

/**
 * Gets the UID property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return pointer to a char string with the UID property for @p comp.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_uid(icalcomponent *comp);

/**
 * Sets the RELCALID property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to a char string with the RELCALID to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_relcalid(icalcomponent *comp, const char *v);

/**
 * Gets the RELCALID property of an icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return the relcalid of the specified icalcomponent.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_relcalid(icalcomponent *comp);

/**
 * Sets the RECURRENCEID property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icaltimetype RECURRENCEID to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_recurrenceid(icalcomponent *comp,
                                                        struct icaltimetype v);

/**
 * Gets the RECURRENCEID property of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return an icaltimetype with the RECURRENCEID property for @p comp.
 * If there is no such property then a value of `icaltime_null_time()`
 * is returned.
 * If @p comp is invalid then a value of `icaltime_null_time()` is returned
 * and the internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalcomponent_get_recurrenceid(icalcomponent *comp);

/**
 * Sets the DESCRIPTION property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to a char string with the DESCRIPTION to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_description(icalcomponent *comp, const char *v);

/**
 * Gets the DESCRIPTION property of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return pointer to a char string with the DESCRIPTION property for @p comp.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_description(icalcomponent *comp);

/**
 * Sets the LOCATION property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v a pointer to char string with the LOCATION to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_location(icalcomponent *comp, const char *v);

/**
 * Gets the LOCATION property of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a pointer to a char string with the LOCATION property for @p comp.
 * If there is no such property then a value of NULL is returned.
 * If @p comp is invalid then a value of NULL is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT const char *icalcomponent_get_location(icalcomponent *comp);

/**
 * Sets the SEQUENCE property for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the integer SEQUENCE to use
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_sequence(icalcomponent *comp, int v);

/**
 * Gets the SEQUENCE property of the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @return a integer SEQUENCE property for @p comp.
 * If there is no such property then a value of zero is returned.
 * If @p comp is invalid then a value of zero is returned and the
 * internal library ::icalerrno is set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT int icalcomponent_get_sequence(icalcomponent *comp);

/**
 * Sets the STATUS for the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param v is the icalproperty_status to use as the STATUS property
 *
 * If @p comp is invalid then the internal library ::icalerrno is
 * set to ::ICAL_MALFORMEDDATA_ERROR.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_set_status(icalcomponent *comp, enum icalproperty_status v);

/**
 * Gets the status property of the icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @returns in normal conditions, the status property as an icalproperty_status
 * of the specified icalcomponent; else ICAL_STATUS_NONE if a problem parsing the
 * status was detected.
 */
LIBICAL_ICAL_EXPORT enum icalproperty_status icalcomponent_get_status(icalcomponent *comp);

/**
 * Calls the given function for each TZID parameter found in the
 * component, as well as any subcomponents.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param callback a pointer to a function to call for each TZID parameter
 * @param callback_data a pointer to data associated with the callback function
 */
LIBICAL_ICAL_EXPORT void icalcomponent_foreach_tzid(icalcomponent *comp,
                                                    void (*callback)(icalparameter *param,
                                                                     void *data),
                                                    void *callback_data);

/**
 * Return the icaltimezone in the component corresponding to the
 * specified TZID, or NULL if a one cannot be found.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param tzid a pointer to a char string containing the TZID
 *
 * @return the icaltimezone in the specified icalcomponent corresponding
 * to the TZID, or NULL if it can't be found.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icalcomponent_get_timezone(icalcomponent *comp,
                                                             const char *tzid);

/**
 * @brief Decides if a recurrence is acceptable.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param dtstart the base dtstart value for this component.
 * @param recurtime the time to test against.
 *
 * @return true if the recurrence value is excluded, false otherwise.
 *
 * This function decides if a specific recurrence value is
 * excluded by EXRULE or EXDATE properties.
 *
 * It's not the most efficient code.  You might get better performance
 * if you assume that recurtime is always increasing for each
 * call. Then you could:
 *
 *   - sort the EXDATE values
 *   - save the state of each EXRULE iterator for the next call.
 *
 * In this case though you don't need to worry how you call this
 * function.  It will always return the correct result.
 */
LIBICAL_ICAL_EXPORT bool icalproperty_recurrence_is_excluded(icalcomponent *comp,
                                                             struct icaltimetype *dtstart,
                                                             struct icaltimetype *recurtime);

/**
 * Iterates through all recurrences of an event.
 *
 * @param comp           a pointer to a VEVENT icalcomponent
 * @param start          Ignore timespans before this
 * @param end            Ignore timespans after this
 * @param callback       Function called for each timespan within the range
 * @param callback_data  Pointer passed back to the callback function
 *
 * This function will call the specified callback function for once
 * for the base value of DTSTART, and foreach recurring date/time
 * value.
 *
 * It will filter out events that are specified as an EXDATE or an EXRULE.
 */
LIBICAL_ICAL_EXPORT void icalcomponent_foreach_recurrence(icalcomponent *comp,
                                                          struct icaltimetype start,
                                                          struct icaltimetype end,
                                                          void (*callback)(icalcomponent *comp,
                                                                           const struct icaltime_span *span,
                                                                           void *data),
                                                          void *callback_data);

/**
 * Normalizes (reorders and sorts the properties) the specified icalcomponent.
 *
 * @param comp a pointer to a valid icalcomponent
 *
 * @since 3.0
 */
LIBICAL_ICAL_EXPORT void icalcomponent_normalize(icalcomponent *comp);

/**
 * Computes the datetime corresponding to the specified @p icalproperty and @p icalcomponent.
 * If the property is a DATE-TIME with a TZID parameter and a corresponding VTIMEZONE
 * is present in the component, the returned component will already be in the correct
 * timezone; otherwise the caller is responsible for converting it.
 *
 * Call icaltime_is_null_time() on the returned value to detect failures.
 *
 * @param prop a pointer to a valid icalproperty
 * @param comp a pointer to a valid icalcomponent
 *
 * @return the DATE or DATE_TIME an icaltimetype of the specified icalcomponent.
 *
 * @since 3.0.5
 */
LIBICAL_ICAL_EXPORT struct icaltimetype icalproperty_get_datetime_with_component(
    icalproperty *prop,
    icalcomponent *comp);
/*************** Type Specific routines ***************/

/**
 * Constructs a new ::ICAL_VCALENDAR_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vcalendar(void);

/**
 * Constructs a new ::ICAL_VEVENT_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vevent(void);

/**
 * Constructs a new ::ICAL_VTODO_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vtodo(void);

/**
 * Constructs a new ::ICAL_VJOURNAL_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vjournal(void);

/**
 * Constructs a new ::ICAL_VALARM_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_valarm(void);

/**
 * Constructs a new ::ICAL_VFREEBUSY_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vfreebusy(void);

/**
 * Constructs a new ::ICAL_VTIMEZONE_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vtimezone(void);

/**
 * Constructs a new ::ICAL_XSTANDARD_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_xstandard(void);

/**
 * Constructs a new ::ICAL_XDAYLIGHT_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_xdaylight(void);

/**
 * Constructs a new ::ICAL_VAGENDA_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vagenda(void);

/**
 * Constructs a new ::ICAL_VQUERY_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vquery(void);

/**
 * Constructs a new ::ICAL_VREPLY_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vreply(void);

/**
 * Constructs a new ::ICAL_VAVAILABILITY_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vavailability(void);

/**
 * Constructs a new ::ICAL_XAVAILABLE_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_xavailable(void);

/**
 * Constructs a new ::ICAL_VPOLL_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vpoll(void);

/**
 * Constructs a new ::ICAL_VVOTER_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vvoter(void);

/**
 * Constructs a new ::ICAL_XVOTE_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_xvote(void);

/**
 * Constructs a new ::ICAL_VPATCH_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vpatch(void);

/**
 * Constructs a new ::ICAL_XPATCH_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_xpatch(void);

/**
 * Constructs a new ::ICAL_PARTICIPANT_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_participant(void);

/**
 * Constructs a new ::ICAL_VLOCATION_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vlocation(void);

/**
 * Constructs a new ::ICAL_VRESOURCE_COMPONENT icalcomponent.
 *
 * @return a pointer to the new icalcomponet. Free with icalcomponent_free
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalcomponent_new_vresource(void);

#endif /* !ICALCOMPONENT_H */

/*======================================================================
 FILE: icaltimezone.h
 CREATOR: Damon Chaplin 15 March 2001

 SPDX-FileCopyrightText: 2001, Damon Chaplin <damon@ximian.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icaltimezone.h
 * @brief Timezone handling routines
 */

#ifndef ICALTIMEZONE_H
#define ICALTIMEZONE_H

#include "libical_ical_export.h"


#include <stdbool.h>
#include <stdio.h>

#if !defined(ICALTIMEZONE_DEFINED)
#define ICALTIMEZONE_DEFINED
/**
 * An opaque struct representing a timezone.
 * We declare this here to avoid a circular dependency.
 */
typedef struct _icaltimezone icaltimezone;
#endif

/*
 * Creating/Destroying individual icaltimezones.
 */

/**
 * Creates a new icaltimezone.
 * The data structure contains all null values and is essentially invalid.
 *
 * @return a pointer to the new invalid icaltimezone.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_new(void);

/**
 * Deep clones an icaltimezone.
 *
 * Invalid icaltimezone data structures can also be cloned.
 *
 * @param originalzone is a pointer to an icaltimezone.
 *
 * @return a pointer to the cloned icaltimezone.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_copy(const icaltimezone *originalzone);

/** @brief Frees all memory used for the icaltimezone.
 * @param zone The icaltimezone to be freed
 * @param free_struct Whether to free the icaltimezone struct as well
 */
LIBICAL_ICAL_EXPORT void icaltimezone_free(icaltimezone *zone, int free_struct);

/**
 * Sets the prefix to be used for tzid's generated from system tzdata.
 * Must be globally unique (such as a domain name owned by the developer
 * of the calling application), and begin and end with forward slashes.
 * The string must be less than 256 chars long.
 *
 * No error or sanity checking is performed in this function; the caller is
 * entirely responsible for using a proper tzid string.
 *
 * Do not change or de-allocate the string buffer after calling this.
 *
 * @param new_prefix a string (properly formatted and less then 256 characters long)
 * representing the tzid for the system tzdata. If not specified, the library default
 * "/freeassociation.sourceforge.net/" is used.
 */
LIBICAL_ICAL_EXPORT void icaltimezone_set_tzid_prefix(const char *new_prefix);

/**
 * Get the current setting of the tzid prefix.
 *
 * @return a pointer to a char string containing the current tzid prefix.
 */
LIBICAL_ICAL_EXPORT const char *icaltimezone_tzid_prefix(void);

/*
 * Accessing timezones.
 */

/** @brief Releases builtin timezone memory. */
LIBICAL_ICAL_EXPORT void icaltimezone_free_builtin_timezones(void);

/**
 * Gets an icalarray of icaltimezone structs, one for each builtin timezone.
 *
 * This will load and parse the zones.tab file to get the
 * timezone names and their coordinates. It will not load the
 * VTIMEZONE data for any timezones.
 *
 * @return a pointer to an icalarray containing the list of icaltimezone structs
 * associated with the buildtin timezones.
 */
LIBICAL_ICAL_EXPORT icalarray *icaltimezone_get_builtin_timezones(void);

/**
 * Gets a single builtin timezone, given its Olson location.
 *
 * @param location a pointer to a char string containing the Olson location to search
 *
 * @return a pointer to a builtin icaltimezone that matches the specified
 * Olson location.  NULL is returned if the location is empty or if the
 * search fails.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_get_builtin_timezone(const char *location);

/**
 * Gets a single builtin timezone, given its offset from UTC.
 *
 * @param offset the offset from UTC to search
 * @param tzname a pointer to a char string containing a TZNAME to search.
 *
 * @return a pointer to a builtin icaltimezone that matches the specified
 * @p offset and @p tzname. NULL is returned if tzname is NULL or if the
 * search fails.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_get_builtin_timezone_from_offset(int offset,
                                                                                const char *tzname);

/**
 * Gets Returns a single builtin timezone, given its TZID.
 *
 * @param tzid a pointer to a char string containing the TZID to find
 *
 * @return a pointer to a builting icaltimezone for the specified TZID.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_get_builtin_timezone_from_tzid(const char *tzid);

/**
 * Gets the UTC timezone.
 *
 * @return a pointer to an icaltimezone representing the UTC timezone.
 */
LIBICAL_ICAL_EXPORT icaltimezone *icaltimezone_get_utc_timezone(void);

/**
 * Gets the TZID of a timezone.
 *
 * @param zone a pointer to a valid icaltimezone
 *
 * @return a pointer to a char string containing the TZID for the
 * specified icaltimezone. NULL will be returned for floating timezones.
  */
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_tzid(icaltimezone *zone);

/**
 * Gets the LOCATION of a timezone.
 *
 * @param zone a pointer to a valid icaltimezone
 *
 * @return a pointer to a char string containing the LOCATION for the
 * specified timezone. NULL will be returned for floating timezones.
 */
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_location(const icaltimezone *zone);

/**
 * Gets the TZNAME properties used in the latest STANDARD and DAYLIGHT
 * components a a builtin timezone.
 *
 * If they are the same it will return just one, e.g. "LMT".
 * If they are different it will format them like "EST/EDT".
 *
 * @param zone is a pointer to a valid icaltimezone
 *
 * @return a pointer to a char string containing the TZNAME for the
 * specified icaltimezone. NULL will be returned for floating timezones.
*/
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_tznames(icaltimezone *zone);

/**
 * Gets the latitude of a builtin timezone.
 *
 * @param zone a pointer to a valid icaltimezone
 *
 * @return the latitude of the specified icaltimezone as a double.
 */
LIBICAL_ICAL_EXPORT double icaltimezone_get_latitude(const icaltimezone *zone);

/**
 * Gets the longitude of a builtin timezone.
 *
 * @param zone a pointer to a valid icaltimezone
 *
 * @return the longitude of the specified icaltimezone as a double.
 */
LIBICAL_ICAL_EXPORT double icaltimezone_get_longitude(const icaltimezone *zone);

/**
 * Gets the VTIMEZONE component of a timezone.
 *
 * @param zone is a pointer to a valid icaltimezone.
 *
 * @return a pointer to the VTIMEZONE component of the specified icaltimezone.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icaltimezone_get_component(icaltimezone *zone);

/**
 * Sets the VTIMEZONE component of an icaltimezone, initializing the
 * tzid, location & tzname fields.
 *
 * @param zone a pointer to a valid icaltimezone
 * @param comp is a pointer to a valid icalcomponent to use
 *
 * @returns true on success or false on failure, i.e.  no TZID was found.
 */
LIBICAL_ICAL_EXPORT bool icaltimezone_set_component(icaltimezone *zone, icalcomponent *comp);

/**
 * Get the timezone display name.
 *
 * We prefer to use the Olson city name, but fall back on the TZNAME, or finally
 * the TZID. We don't want to use "" as it may be wrongly interpreted as a
 * floating time. Do not free the returned string.
 *
 * @param zone a pointer to a valid icaltimezone
 *
 * @return a pointer to a char string containing the timezone display name.
 */
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_display_name(icaltimezone *zone);

/**
 * Rotate a time from one timezone to another.
 *
 * @param tt is a the icaltimetype to rotate. If @p tt represents a date (ie. there is no associated time)
 * then no conversion is performed.
 * @param from_zone is the timezone to rotate from. Any timezone specified inside the icaltimetype is ignored.
 * If @p from_zone is NULL then no conversion is performed.
 * @param to_zone is the timezone to rotate to.  If @p to_zone is NULL then the time is rotated to UTC.
 *
 */

LIBICAL_ICAL_EXPORT void icaltimezone_convert_time(struct icaltimetype *tt,
                                                   icaltimezone *from_zone,
                                                   icaltimezone *to_zone);

/*
 * Getting offsets from UTC.
 */

/**
 * Calculates the UTC offset of a given local time in the given timezone.
 *
 * It is the number of seconds to add to UTC to get local time.
 *
 * @param zone is a pointer to a valid icaltimezone
 * @param tt is an icaltimetype with the local time
 * @param is_daylight is a pointer to an int which will be set to 1 (true)
 * on return if the time is in daylight-savings; in non-daylight-saving
 * it will be set to 0 (false).
 *
 * @return the UTC offset corresponding to the timezone change. For local times
 * and UTC a 0 offset is returned. Additionally, if @p tt is NULL or if the
 * @p tt year is too large a 0 offset is returned.
 */
LIBICAL_ICAL_EXPORT int icaltimezone_get_utc_offset(icaltimezone *zone,
                                                    const struct icaltimetype *tt, int *is_daylight);

/**
 * Calculates the UTC offset of a given UTC time in the given timezone.
 *
 * It is the number of seconds to add to UTC to get local time.
 *
 * @param zone is a pointer to a valid icaltimezone
 * @param tt is an icaltimetype with the UTC time
 * @param is_daylight is a pointer to an int which will be set to 1 (true)
 * on return if the time is in daylight-savings; in non-daylight-saving
 * it will be set to 0 (false).
 *
 * @return the UTC offset corresponding to the timezone change. For local times
 * and UTC a 0 offset is returned.
 */
LIBICAL_ICAL_EXPORT int icaltimezone_get_utc_offset_of_utc_time(icaltimezone *zone,
                                                                const struct icaltimetype *tt,
                                                                int *is_daylight);

/// @cond PRIVATE

/*
 * Handling arrays of timezones. For internal use.
 */
LIBICAL_ICAL_NO_EXPORT icalarray *icaltimezone_array_new(void);

LIBICAL_ICAL_NO_EXPORT void icaltimezone_array_append_from_vtimezone(icalarray *timezones,
                                                                     icalcomponent *child);

LIBICAL_ICAL_NO_EXPORT void icaltimezone_array_free(icalarray *timezones);
/// @endcond

/**
 * Applies a list of timezone changes from an array of changes until an end year.
 *
 * @param comp a pointer to a valid icalcomponent
 * @param end_year the end year
 * @param changes a pointer to an icalarray containing the changes to be applied
 *
 */
LIBICAL_ICAL_EXPORT void icaltimezone_expand_vtimezone(icalcomponent *comp,
                                                       int end_year,
                                                       icalarray *changes);

/**
 * Gets the LOCATION or X-LIC-LOCATION property from a VTIMEZONE.
 *
 * @param component is a pointer to a valid icalcomponent.
 *
 * @return a pointer to a char string containing the LOCATION or X-LIC-LOCATION
 * property for the specified icalcomponent.
 */
LIBICAL_ICAL_EXPORT char *icaltimezone_get_location_from_vtimezone(icalcomponent *component);

/**
 * Gets the TZNAMEs used for the last STANDARD & DAYLIGHT components in a VTIMEZONE.
 *
 * If both STANDARD and DAYLIGHT components use the same TZNAME, it
 * returns that. If they use different TZNAMEs, it formats them like
 * "EST/EDT". The returned string should be freed by the caller.
 *
 * @param component a pointer to a valid icalcomponent
 *
 * @return a pointer to a char string containing the TZNAMEs.
 */
LIBICAL_ICAL_EXPORT char *icaltimezone_get_tznames_from_vtimezone(icalcomponent *component);

/**
 * Truncate a VTIMEZONE component to the given start and end times.
 *
 * If either time is null, then no truncation will occur at that point.
 * If either time is non-null, then it MUST be specified as UTC.
 * If the start time is non-null and ms_compatible is false,
 * then the DTSTART of RRULEs will be adjusted to occur after the start time.
 *
 * @param vtz is a pointer to a valid VTIMEZONE icalcomponent
 * @param start is the starting icaltimetype
 * @param end is the ending icaltimetype
 * @param ms_compatible is a flag indicating if the truncation should be
 * compatible with Microsoft Outlook/Exchange (which doesn't appear to
 * like truncating the frontend of RRULEs).
 *
 * @since 3.0.6
 */
LIBICAL_ICAL_EXPORT void icaltimezone_truncate_vtimezone(icalcomponent *vtz,
                                                         icaltimetype start,
                                                         icaltimetype end,
                                                         bool ms_compatible);

/*
 * @par Handling the default location the timezone files
 */

/**
 * Gets the fullpath to the system zoneinfo directory (where zone.tab lives).
 * The returned value points to static memory inside the library and should
 * not try to be freed.
 *
 * If the TZDIR variable appears in the environment, it will be searched first
 * for zone.tab.  If zone.tab is not located in TZDIR (or if TZDIR is not in the
 * environment), then a list of well-known paths where the system zone.tab
 * typically is installed is searched.
 *
 * @return a pointer to a char string containing the system zoneinfo directory name.
 *
 * @since 4.0 previously known as icaltzutil_get_zone_directory
 */
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_system_zone_directory(void);

/**
 * Sets the fullpath to the system zoneinfo directory (zone.tab must reside in there).
 * @param zonepath const character string containing the fullpath to the zoneinfo directory.
 *
 * The internal zoneinfo path can be cleared if @p zonepath is empty or NULL.
 * @since 4.0 previously known as icaltzutil_set_zone_directory
 */
LIBICAL_ICAL_EXPORT void icaltimezone_set_system_zone_directory(const char *zonepath);

/**
 * Gets the directory to look for the zonefiles, either system or builtin.
 *
 * @return a pointer to a char string containing the zonefile directory name.
 */
LIBICAL_ICAL_EXPORT const char *icaltimezone_get_zone_directory(void);

/**
 * Sets the directory to look for the zonefiles, either system or builtin.
 *
 * The memory allocated by this function should be freed using icaltimezone_set_zone_directory().
 *
 * @param path is a char string containing the directory path for zoneinfo data.
 */
LIBICAL_ICAL_EXPORT void icaltimezone_set_zone_directory(const char *path);

/**
 * Frees the zonefile directory.
 *
 * Frees the memory allocated by the icaltimezone_set_zone_directory()
 */
LIBICAL_ICAL_EXPORT void icaltimezone_free_zone_directory(void);

/**
 * Set the library to use builtin timezone data.
 *
 * @param set if true, configures the library to use builtin timezone data;
 * otherwise, the system timezone data is used.
 */
LIBICAL_ICAL_EXPORT void icaltimezone_set_builtin_tzdata(bool set);

/**
 * Get if the library is using builtin timezone data.
 *
 * @return true if the builtin timezone data is being used; false otherwise.
 */
LIBICAL_ICAL_EXPORT bool icaltimezone_get_builtin_tzdata(void);

/*
 * Debugging Output.
 */

/**
 * Outputs a list of timezone changes for the given timezone to the
 * given file, up to the maximum year given.
 *
 * We compare this output with the output from 'vzic --dump-changes' to
 * make sure that we are consistent. (vzic is the Olson timezone
 * database to VTIMEZONE converter.)
 *
 * The output format is:
 *
 *      Zone-Name [tab] Date [tab] Time [tab] UTC-Offset
 *
 * The Date and Time fields specify the time change in UTC.
 *
 * The UTC Offset is for local (wall-clock) time. It is the amount of time
 * to add to UTC to get local time.
 *
 * @param zone is a pointer to a valid icaltimezone to use
 * @param max_year is the maximum year to process
 * @param fp is a pointer to FILE for a file that is opened for writing
 *
 * @return true. always.
 */
LIBICAL_ICAL_EXPORT bool icaltimezone_dump_changes(icaltimezone *zone, int max_year, FILE *fp);

#endif /* ICALTIMEZONE_H */

/*======================================================================
 FILE: icalparser.h
 CREATOR: eric 20 April 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

#ifndef ICALPARSER_H
#define ICALPARSER_H

#include "libical_ical_export.h"


/**
 * @file  icalparser.h
 * @brief Line-oriented parsing.
 *
 * This file provides methods to parse iCalendar-formatted data
 * into the structures provided by this library.
 *
 * @par Usage
 * Create a new parser via icalparser_new_parser(), then add lines one at
 * a time with icalparser_add_line(). icalparser_add_line() will return
 * non-zero when it has finished with a component.
 */

/**
 * Implementation of the icalparser struct, which holds the
 * state for the current parsing operation.
 */
typedef struct icalparser_impl icalparser;

/**
 * @enum icalparser_state
 * @typedef icalparser_state
 * @brief Represents the current state of the parser
 */
typedef enum icalparser_state
{
    /** An error occurred while parsing. */
    ICALPARSER_ERROR,

    /** Parsing was successful. */
    ICALPARSER_SUCCESS,

    /** Currently parsing the begin of a component. */
    ICALPARSER_BEGIN_COMP,

    /** Currently parsing the end of the component. */
    ICALPARSER_END_COMP,

    /** Parsing is currently in progress. */
    ICALPARSER_IN_PROGRESS
} icalparser_state;

/// @cond PRIVATE
typedef char *(*icalparser_line_gen_func)(char *s, size_t size, void *d);
/// @endcond

/**
 * @brief Creates a new icalparser.
 * @return An icalparser object
 *
 * @par Error handling
 * On error, it returns `NULL` and sets ::icalerrno to
 * ::ICAL_NEWFAILED_ERROR.
 *
 * @par Ownership
 * All icalparser objects created with this function need to be
 * freed using the icalparser_free() function.
 *
 * @par Usage
 * ```c
 * // create new parser
 * icalparser *parser = icalparser_new();
 *
 * // do something with it...
 *
 * // free parser
 * icalparser_free(parser);
 * ```
 */
LIBICAL_ICAL_EXPORT icalparser *icalparser_new(void);

/**
 * @brief Adds a single line to be parsed by the icalparser.
 * @param parser The parser to use
 * @param line A string representing a single line of RFC5545-formatted iCalendar data
 * @return When this was the last line of the component to be parsed,
 *  it returns the icalcomponent, otherwise it returns `NULL`.
 * @sa icalparser_parse()
 *
 * @par Error handling
 * -   If @a parser is `NULL`, it returns `NULL` and sets ::icalerrno to
 *     ::ICAL_BADARG_ERROR.
 * -   If @a line is empty, if returns `NULL`
 * -   If @a line is `NULL`, it returns `NULL` and sets the @a parser's ::icalparser_state to
 *     ::ICALPARSER_ERROR.
 * -   For errors during parsing, the functions can set the ::icalparser_state to
 *     ::ICALPARSER_ERROR and/or return components of the type ICAL_XLICINVALID_COMPONENT,
 *     or components with properties of the type ICAL_XLICERROR_PROPERTY.
 *
 * @par Ownership
 * Ownership of the @a line is transferred to libical upon calling this
 * method. The returned icalcomponent is owned by the caller and needs
 * to be `free()`d with the appropriate method after it's no longer needed.
 *
 * @par Example
 * ```c
 * char* read_stream(char *s, size_t size, void *d)
 * {
       return fgets(s, (int)size, (FILE*)d);
 * }
 *
 * void parse()
 * {
 *     char* line;
 *     FILE* stream;
 *     icalcomponent *component;
 *
 *     icalparser *parser = icalparser_new();
 *     stream = fopen(argv[1],"r");
 *
 *     icalparser_set_gen_data(parser, stream);
 *
 *     do{
 *         // get a single content line
 *         line = icalparser_get_line(parser, read_stream);
 *
 *         // add that line to the parser
 *         c = icalparser_add_line(parser,line);
 *
 *         // once we parsed a component, print it
 *         if (c != 0) {
 *             printf("%s", icalcomponent_as_ical_string(c));
 *             icalcomponent_free(c);
 *         }
 *     } while (line != 0);
 *
 *     icalparser_free(parser);
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalparser_add_line(icalparser *parser, char *line);

/**
 * @brief Cleans out an icalparser and returns whatever it has parsed so far.
 * @param parser The icalparser to clean
 * @return The parsed icalcomponent
 *
 * @par Error handling
 * If @a parser is `NULL`, it returns `NULL` and sets ::icalerrno to
 * ::ICAL_BADARG_ERROR. For parsing errors, it inserts an `X-LIC-ERROR`
 * property into the affected components.
 *
 * @par Ownership
 * The returned icalcomponent is property of the caller and needs to be
 * free'd with icalcomponent_free() after use.
 *
 * This will parse components even if it hasn't encountered a proper
 * `END` tag for it yet and return them, as well as clearing any intermediate
 * state resulting from being in the middle of parsing something so the
 * parser can be used to parse something new.
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalparser_clean(icalparser *parser);

/**
 * @brief Returns current state of the icalparser
 * @param parser The (valid, non-`NULL`) parser object
 * @return The current state of the icalparser, as an ::icalparser_state
 *
 * @par Example
 * ```c
 * icalparser *parser = icalparser_new();
 *
 * // use icalparser...
 *
 * if(icalparser_get_state(parser) == ICALPARSER_ERROR) {
 *     // handle error
 * } else {
 *     // ...
 * }
 * ```
 *
 * icalparser_free(parser);
 */
LIBICAL_ICAL_EXPORT icalparser_state icalparser_get_state(const icalparser *parser);

/**
 * @brief Frees an icalparser object.
 * @param parser The icalparser to be freed.
 *
 * @par Example
 * ```c
 * icalparser *parser = icalparser_new();
 *
 * // use parser ...
 *
 * icalparser_free(parser);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalparser_free(icalparser *parser);

/**
 * @brief Message oriented parsing.
 * @param parser The parser to use
 * @param line_gen_func A function that returns one content line per invocation
 * @return The parsed icalcomponent
 * @sa icalparser_parse_string()
 *
 * Reads an icalcomponent using the supplied @a line_gen_func, returning the parsed
 * component (or `NULL` on error).
 *
 * @par Error handling
 * -   If @a parser is `NULL`, it returns `NULL` and sets ::icalerrno to ::ICAL_BADARG_ERROR.
 * -   If data read by @a line_gen_func is empty, if returns `NULL`
 * -   If data read by @a line_gen_func is `NULL`, it returns `NULL`
 *     and sets the @a parser's ::icalparser_state to ::ICALPARSER_ERROR.
 * -   For errors during parsing, the functions can set the ::icalparser_state to
 *     ::ICALPARSER_ERROR and/or return components of the type ICAL_XLICINVALID_COMPONENT,
 *     or components with properties of the type ICAL_XLICERROR_PROPERTY.
 *
 * @par Ownership
 * The returned icalcomponent is owned by the caller of the function, and
 * needs to be `free()`d with the appropriate method when no longer needed.
 *
 * @par Example
 * ```c
 * char* read_stream(char *s, size_t size, void *d)
 * {
       return fgets(s, (int)size, (FILE*)d);
 * }
 *
 * void parse()
 * {
 *     char* line;
 *     FILE* stream;
 *     icalcomponent *component;
 *
 *     icalparser *parser = icalparser_new();
 *     stream = fopen(argv[1],"r");
 *
 *     icalparser_set_gen_data(parser, stream);
 *
 *     // use the parse method to parse the input data
 *     component = icalparser_parse(parser, read_stream);
 *
 *     // once we parsed a component, print it
 *     printf("%s", icalcomponent_as_ical_string(c));
 *     icalcomponent_free(c);
 *
 *     icalparser_free(parser);
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalparser_parse(icalparser *parser,
                                                    icalparser_line_gen_func line_gen_func);

/**
 * @brief Sets the data that icalparser_parse will give to the line_gen_func
 * as the parameter 'd'.
 * @param parser The icalparser this applies to
 * @param data The pointer which will be passed to the line_gen_func as argument `d`
 *
 * If you use any of the icalparser_parser() or icalparser_get_line() functions,
 * the @a line_gen_func that they expect has a third `void *d` argument. This function
 * sets what will be passed to your @a line_gen_function as such argument.
 */
LIBICAL_ICAL_EXPORT void icalparser_set_gen_data(icalparser *parser, void *data);

/**
 * @brief Parses a string and returns the parsed icalcomponent.
 * @param str The iCal formatted data to be parsed
 * @return An icalcomponent representing the iCalendar
 *
 * @par Error handling
 * On error, returns `NULL` and sets ::icalerrno
 *
 * @par Ownership
 * The returned icalcomponent is owned by the caller of the function, and
 * needs to be free'd with the appropriate functions after use.
 *
 * @par Example
 * ```c
 * char *ical_string;
 *
 * // parse ical_string
 * icalcomponent *component = icalparser_parse_string(ical_string);
 *
 * if(!icalerrno || component != NULL) {
 *     // use component ...
 * }
 *
 * // release component
 * icalcomponent_free(component);
 * ```
 */
LIBICAL_ICAL_EXPORT icalcomponent *icalparser_parse_string(const char *str);

/**
 * @enum icalparser_ctrl
 * @brief Defines how to handle invalid CONTROL characters in content lines
 */
typedef enum icalparser_ctrl
{
    /** Keep CONTROL characters in content-line */
    ICALPARSER_CTRL_KEEP,
    /** Omit CONTROL characters from content-line */
    ICALPARSER_CTRL_OMIT,
    /** Insert a X-LIC-ERROR instead of content-line */
    ICALPARSER_CTRL_ERROR
} icalparser_ctrl;

/**
 * @brief Get the current parser setting how to handle CONTROL characters
 * @return The current parser setting
 */
LIBICAL_ICAL_EXPORT enum icalparser_ctrl icalparser_get_ctrl(void);

/**
 * @brief Set the parser setting how to handle CONTROL characters
 * @param ctrl The setting to use
 */
LIBICAL_ICAL_EXPORT void icalparser_set_ctrl(enum icalparser_ctrl ctrl);

/***********************************************************************
 * Parser support functions
 ***********************************************************************/

/**
 * @brief Given a line generator function, returns a single iCal content line.
 * @return A pointer to a single line of data or `NULL` if it reached
 *  end of file reading from the @a line_gen_func. Note that the pointer
 *  returned is owned by libical and must not be `free()`d by the user.
 * @param parser The parser object to use
 * @param line_gen_func The function to use for reading data
 *
 * This function uses the supplied @a line_gen_func to read data in,
 * until it has read a full line, and returns the full line.
 * It includes any continuation lines, which start with a space after a newline.
 * To supply arbitrary data (as the parameter @a d) to your @a line_gen_func,
 * call icalparser_set_gen_data().
 */
LIBICAL_ICAL_EXPORT char *icalparser_get_line(icalparser *parser,
                                              icalparser_line_gen_func line_gen_func);

/**
 * A callback function to use by icalparser_get_line.
 *
 * @param out a pointer to a char string to hold the concatenated output data
 * @param buf_size is the length of @p out
 * @param d is a pointer to the input data
 *
 * @return NULL if processing is complete; else a pointer to @p out.
 */
LIBICAL_ICAL_EXPORT char *icalparser_string_line_generator(char *out, size_t buf_size, void *d);

#endif /* !ICALPARSE_H */

/*======================================================================
 FILE: icalmemory.h
 CREATOR: eric 30 June 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 The Initial Developer of the Original Code is Eric Busboom
======================================================================*/

#ifndef ICALMEMORY_H
#define ICALMEMORY_H

/**
 * @file icalmemory.h
 * @brief Common memory management routines.
 *
 * libical often passes strings back to the caller. To make these
 * interfaces simple, I did not want the caller to have to pass in a
 * memory buffer, but having libical pass out newly allocated memory
 * makes it difficult to de-allocate the memory.
 *
 * The ring buffer in this scheme makes it possible for libical to pass out
 * references to memory which the caller does not own, and be able to
 * de-allocate the memory later. The ring allows libical to have several buffers
 * active simultaneously, which is handy when creating string representations of
 * components. Methods for working with these temporary buffers are marked with
 * `icalmemory_tmp_*()`.
 *
 * Other memory management routines include wrappers around the system
 * management routines like icalmemory_new_buffer() and icalmemory_free_buffer()
 * as well as routines to work with strings, like icalmemory_append_string().
 */

#include "libical_ical_export.h"

#include <stddef.h>

/**
 * @brief Creates a new temporary buffer on the ring and returns it.
 * @param size How big (in bytes) the buffer should be
 * @return A pointer to the newly created buffer on the ring
 *
 * Creates a temporary buffer on the ring. Regardless of what @a size you
 * specify, the buffer will always be at least MIN_BUFFER_SIZE big, and it
 * will be zeroed out.
 *
 * @par Error handling
 * If there is a problem allocating memory for the buffer, it sets ::icalerrno
 * to ::ICAL_NEWFAILED_ERROR and returns `NULL`.
 *
 * @par Ownership
 * The returned buffer is owned by icalmemory. It must not be freed by the
 * caller and the returned memory will be automatically reclaimed as more items
 * are added to the ring buffer.
 *
 * @par Usage
 * ```c
 * char *str = icalmemory_tmp_buffer(256);
 * strcpy(str, "some data");
 *
 * // use str
 * ```
 */
LIBICAL_ICAL_EXPORT void *icalmemory_tmp_buffer(size_t size);

/**
 * @brief Creates a copy of the given string, stored on the ring buffer, and
 *  returns it.
 * @param str The string to copy
 * @return A copy of @a str, which has been placed on the ring buffer for
 *  automatic reclamation.
 *
 * @par Error handling
 * The passed string @a str must not be `NULL`, otherwise a segfault might
 * ensue, since the routine calls `strlen()` on it.
 *
 * @par Ownership
 * The returned string is owned by icalmemory. It must not be freed by the
 * caller, and it will be automatically reclaimed as more items are added to the
 * buffer.
 *
 * @par Usage
 * ```c
 * const char *str = "Example string";
 * char *tmp_copy = icalmemory_tmp_copy(str);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icalmemory_tmp_copy(const char *str);

/**
 * @brief Adds an externally allocated buffer to the ring.
 * @param buf The externally allocated buffer to add to the ring
 *
 * Adds an externally allocated buffer to the ring. This ensures that libical
 * will `free()` the buffer automatically, either after BUFFER_RING_SIZE other
 * buffers have been created or added, or after ::icalmemory_free_ring() has
 * been called. Note that freeing the buffers is done using the
 * icalmemory_free_buffer() function, which by default is a wrapper around stdlib's
 * free() function. However, if the memory management functions are
 * customized by the user, the user must make sure to only pass in buffers
 * that have been allocated in a compatible manner.
 *
 * @par Error handling
 * No error is raised if @a buf is `NULL`.
 *
 * @par Ownership
 * After adding @a buf to the ring, it becomes owned by icalmemory and must not
 * be `free()`d manually anymore, it leads to a double-`free()` when icalmemory
 * reclaims the memory.
 *
 * @par Usage
 * ```c
 * char *buf = calloc(256, sizeof(char));
 *
 * icalmemory_add_tmp_buffer(buf);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalmemory_add_tmp_buffer(void *buf);

/**
 * @brief Frees all memory used in the ring
 *
 * Frees all memory used in the ring. If PTHREAD is used or thread-local mode is configured,
 * the ring buffer is allocated on a per-thread basis, meaning that if all
 * rings are to be released, it must be called once in every thread.
 *
 * @par Usage
 * ``` c
 * void *buf = icalmemory_tmp_buffer(256);
 *
 * // use buf
 *
 * // release buf and all other memory in the ring buffer
 * icalmemory_free_ring();
 * ```
 */
LIBICAL_ICAL_EXPORT void icalmemory_free_ring(void);

/// @cond PRIVATE
typedef void *(*icalmemory_malloc_f)(size_t);
typedef void *(*icalmemory_realloc_f)(void *, size_t);
typedef void (*icalmemory_free_f)(void *);
/// @endcond

/**
 * @brief Configures the functions to use for memory management.
 *
 * @param f_malloc The function to use for memory allocation.
 * @param f_realloc The function to use for memory reallocation.
 * @param f_free The function to use for memory deallocation.
 *
 * This function configures the library to use the specified functions for
 * memory management. By default the standard system memory management
 * functions malloc(), realloc() and free() are used.
 *
 * Note: The memory management functions configured via this
 * functions are used throughout the core libical component but not within
 * other components like libicalvcal.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalmemory_set_mem_alloc_funcs(icalmemory_malloc_f f_malloc,
                                                        icalmemory_realloc_f f_realloc,
                                                        icalmemory_free_f f_free);

/**
 * @brief Returns the functions used for memory management.
 *
 * @param f_malloc A pointer to the function to use for memory allocation.
 * @param f_realloc A pointer to the function to use for memory reallocation.
 * @param f_free A pointer to the function to use for memory deallocation.
 *
 * Retrieves the functions used by the library for memory management.
 * @since 4.0
 */
LIBICAL_ICAL_EXPORT void icalmemory_get_mem_alloc_funcs(icalmemory_malloc_f *f_malloc,
                                                        icalmemory_realloc_f *f_realloc, icalmemory_free_f *f_free);

/**
 * @brief Creates new buffer with the specified size.
 * @param size The size of the buffer that is to be created.
 * @return A pointer to the newly-created buffer.
 * @sa icalmemory_free_buffer()
 *
 * @par Error handling
 * If there is a problem allocating memory, it sets ::icalerrno to
 * ::ICAL_NEWFAILED_ERROR and returns `NULL`.
 *
 * @par Ownership
 * Buffers created with this method are owned by the caller. They must be
 * released with the icalmemory_free_buffer() method.
 *
 * This creates a new (non-temporary) buffer of the specified @a size. All
 * buffers returned by this method are zeroed-out.
 *
 * By default this function delegates to stdlib's malloc() but
 * the used function can be changed via icalmemory_set_mem_alloc_funcs().
 *
 * @par Usage
 * ```c
 * // create buffer
 * char *buffer = icalmemory_new_buffer(50);
 *
 * // fill buffer
 * strcpy(buffer, "some data");
 *
 * // release buffer
 * icalmemory_free_buffer(buffer);
 * ```
 */
LIBICAL_ICAL_EXPORT void *icalmemory_new_buffer(size_t size);

/**
 * @brief Resizes a buffer created with icalmemory_new_buffer().
 * @param buf The buffer to be resized.
 * @param size The new size of the buffer.
 * @return The new, resized buffer.
 * @sa icalmemory_new_buffer()
 * @warning This method may not be used for temporary buffers (buffers allocated
 * with icalmemory_tmp_buffer() and related functions)!
 *
 * @par Error handling
 * If there is a problem while reallocating the buffer, the method sets
 * ::icalerrno to ::ICAL_NEWFAILED_ERROR and returns `NULL`.
 *
 * @par Ownership
 * The returned buffer is owned by the caller and needs to be released with the
 * appropriate icalmemory_free_buffer() method. The old buffer, @a buf, can not
 * be used anymore after calling this method.
 *
 * By default this function delegates to stdlib's realloc() but
 * the used function can be configured via icalmemory_set_mem_alloc_funcs().
 *
 * @par Usage
 * ```c
 * // create new buffer
 * char *buffer = icalmemory_new_buffer(10);
 *
 * // fill buffer
 * strcpy(buffer, "some data");
 *
 * // expand buffer
 * buffer = icalmemory_resize_buffer(buffer, 20);
 *
 * // fill with more data
 * strcpy(buffer, "a lot more data");
 *
 * // release
 * icalmemory_free_buffer(buffer);
 * ```
 */
LIBICAL_ICAL_EXPORT void *icalmemory_resize_buffer(void *buf, size_t size);

/**
 * @brief Releases a buffer
 * @param buf The buffer to release
 * @sa icalmemory_new_buffer()
 *
 * Releases the memory of the buffer.
 *
 * By default this function delegates to stdlib's free() but
 * the used function can be configured via icalmemory_set_mem_alloc_funcs().
 */
LIBICAL_ICAL_EXPORT void icalmemory_free_buffer(void *buf);

/* THESE ROUTINES CAN NOT BE USED ON TMP BUFFERS. Only use them on
   normally allocated memory, or on buffers created from
   icalmemory_new_buffer, never with buffers created by
   icalmemory_tmp_buffer. If icalmemory_append_string has to resize a
   buffer on the ring, the ring will loose track of it and you will
   have memory problems. */

/**
 * @brief Appends a string to a buffer.
 * @param buf The buffer to append the string to.
 * @param pos The position to append the string at.
 * @param buf_size The size of the buffer (will be changed if buffer is
 * reallocated)
 * @param string The string to append to the buffer.
 * @warning This method may not be used for temporary buffers (buffers allocated
 *  with icalmemory_tmp_buffer() and related functions)!
 *
 * @par Error handling
 * Sets ::icalerrno to ::ICAL_BADARG_ERROR if @a buf, `*buf`, @a pos, `* pos`,
 * @a buf_size or @a string are `NULL`.
 *
 * This method will copy the string @a string to the buffer @a buf starting at
 * position @a pos, reallocing @a buf if it is too small. @a buf_size is the
 * size of @a buf and will be changed if @a buf is reallocated. @a pos will
 * point to the last byte of the new string in @a buf, usually a `'\0'`
 *
 * @par Example
 * ```c
 * // creates a new buffer
 * int buffer_len = 15;
 * char *buffer = icalmemory_new_buffer(buffer_len);
 * strcpy(buffer, "My name is: ");
 *
 * // append a string to the buffer
 * int buffer_end = strlen(buffer);
 * char *buffer_end_pos = buffer[buffer_str_end];
 * icalmemory_append_string(&buffer, &buffer_end_pos, &buffer_len, "John Doe");
 *
 * // print string
 * printf("%s\n", buffer);
 *
 * // release memory
 * icalmemory_free_buffer(buffer);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalmemory_append_string(char **buf, char **pos, size_t *buf_size,
                                                  const char *string);

/**
 * @brief Appends a character to a buffer.
 * @param buf The buffer to append the character to.
 * @param pos The position to append the character at.
 * @param buf_size The size of the buffer (will be changed if buffer is
 *  reallocated)
 * @param ch The character to append to the buffer.
 * @warning This method may not be used for temporary buffers (buffers allocated
 *  with icalmemory_tmp_buffer() and related functions)!
 *
 * @par Error handling
 * Sets ::icalerrno to ::ICAL_BADARG_ERROR if @a buf, `*buf`, @a pos, `* pos`,
 * or @a buf_size `NULL`.
 *
 * This method will copy the character @a ch and a `'\0'` character after it to
 * the buffer @a buf starting at position @a pos, reallocing @a buf if it is too
 * small. @a buf_size is the size of @a buf and will be changed if @a buf is
 * reallocated. @a pos will point to the new terminating `'\0'` character @a
 * buf.
 *
 * @par Example
 * ```c
 * // creates a new buffer
 * int buffer_len = 15;
 * char *buffer = icalmemory_new_buffer(buffer_len);
 * strcpy(buffer, "My number is: ");
 *
 * // append a char to the buffer
 * int buffer_end = strlen(buffer);
 * char *buffer_end_pos = buffer[buffer_str_end];
 * icalmemory_append_char(&buffer, &buffer_end_pos, &buffer_len, '7');
 *
 * // print string
 * printf("%s\n", buffer);
 *
 * // release memory
 * icalmemory_free_buffer(buffer);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalmemory_append_char(char **buf, char **pos, size_t *buf_size, char ch);

/**
 * @brief Creates a duplicate of a string.
 * @param s The string to duplicate.
 * @return A pointer to a string containing the same data as @a s
 *
 * @par Error handling
 * The string @a s must not be `NULL`, otherwise depending on the `libc` used,
 * it might lead to undefined behaviour (read: segfaults).
 *
 * @par Ownership
 * The returned string is owned by the caller and needs to be released with the
 * `icalmemory_free_buffer()` method.
 *
 * Replaces `strdup()`. The function uses icalmemory_new_buffer() for memory
 * allocation. It also helps trapping calls to `strdup()` and solves the
 * problem that in `-ansi`, `gcc` on Red Hat claims that `strdup()` is
 * undeclared.
 *
 * @par Usage
 * ```c
 * const char *my_str = "LibIcal";
 * char *dup = icalmemory_strdup(my_str);
 * printf("%s\n", dup);
 * icalmemory_free_buffer(dup);
 * ```
 */
LIBICAL_ICAL_EXPORT char *icalmemory_strdup(const char *s);

/**
 * Encodes a string per RFC 6868 and then appends it to the specified char string buffer.
 *
 * This function filters out the characters not permitted by the RFC.
 * paramtext    = *SAFE-CHAR
 * quoted-string= DQUOTE *QSAFE-CHAR DQUOTE
 *
 * Only use on normally allocated memory, or on buffers created from icalmemory_new_buffer,
 * never with buffers created by icalmemory_tmp_buffer. If icalmemory_append_encoded_string has
 * to resize a buffer on the ring, the ring will loose track of it and you will have memory problems.
 *
 * @param buf a pointer to a char string buffer to be appended. The associated memory should not
 * be part of the temporary memory managed by the library.
 * @param pos the position in @b buf in which the new string to be appended
 * @param buf_size the size of the buffer before appended
 * @param string a pointer to char string to be allocated
 */
LIBICAL_ICAL_EXPORT void icalmemory_append_encoded_string(char **buf, char **pos,
                                                          size_t *buf_size,
                                                          const char *string);
/**
 * Decodes a string as TEXT value and then appends it to the buffer.
 *
 * Only use on normally allocated memory, or on buffers created from icalmemory_new_buffer,
 * never with buffers created by icalmemory_tmp_buffer. If icalmemory_append_decoded_string has
 * to resize a buffer on the ring, the ring will loose track of it and you will have memory problems
 *
 * @param buf a pointer to a char string buffer to be appended. The associated memory should not
 * be part of the temporary memory managed by the library.
 * @param pos the position in @b buf in which the new string to be appended
 * @param buf_size the size of the buffer before appended
 * @param string a pointer to char string to be allocated
 */
LIBICAL_ICAL_EXPORT void icalmemory_append_decoded_string(char **buf, char **pos,
                                                          size_t *buf_size,
                                                          const char *string);

#endif /* !ICALMEMORY_H */

/*======================================================================
  FILE: icalerror.h
  CREATOR: eric 09 May 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/

/**
 * @file icalerror.h
 * @brief Error handling for libical
 *
 * Most routines will set the global error value ::icalerrno on errors.
 * This variable is an enumeration; permissible values can be found in
 * icalerror.h. If the routine returns an enum ::icalerrorenum, then the
 * return value will be the same as ::icalerrno. You can use icalerror_strerror()
 * to get a string that describes the error, or icalerror_perror() to
 * get a string describing the current error set in ::icalerrno.
 */

#ifndef ICALERROR_H
#define ICALERROR_H

#include "libical_ical_export.h"

#include <stdbool.h>

#ifndef _MSC_VER
#pragma GCC visibility push(default)
#endif
/**
 * @typedef icalerrorenum
 * @enum icalerrorenum
 * @brief Represents the different types of errors that
 *  can be triggered in libical
 *
 * Each of these values represent a different type of error, which
 * is stored in ::icalerrno on exit of the library function (or
 * can be returned, but if it is, ::icalerrno is also set).
 */
typedef enum icalerrorenum
{
    /** No error happened. */
    ICAL_NO_ERROR = 0,

    /** A bad argument was passed to a function. */
    ICAL_BADARG_ERROR,

    /** An error occurred while creating a new object with a `*_new()` routine. */
    ICAL_NEWFAILED_ERROR,

    /** An error occurred while allocating some memory. */
    ICAL_ALLOCATION_ERROR,

    /** An error occurred with threading. */
    ICAL_THREADING_ERROR,

    /** Malformed data was passed to a function. */
    ICAL_MALFORMEDDATA_ERROR,

    /** An error occurred while parsing part of an iCal component. */
    ICAL_PARSE_ERROR,

    /** An internal error happened in library code. */
    ICAL_INTERNAL_ERROR, /* Like assert --internal consist. prob */

    /** An error happened while working with a file. */
    ICAL_FILE_ERROR,

    /** Failure to properly sequence calls to a set of interfaces. */
    ICAL_USAGE_ERROR,

    /** An unimplemented function was called. */
    ICAL_UNIMPLEMENTED_ERROR,

    /** An unknown error occurred. */
    ICAL_UNKNOWN_ERROR /* Used for problems in input to icalerror_strerror() */
} icalerrorenum;
#ifndef _MSC_VER
#pragma GCC visibility pop
#endif

/**
 * @enum icalerrorstate
 * @typedef icalerrorstate
 * @brief Determine if an error is fatal or non-fatal.
 */
typedef enum icalerrorstate
{
    /** Fatal. */
    ICAL_ERROR_FATAL,

    /** Non-fatal. */
    ICAL_ERROR_NONFATAL,

    /** Fatal if icalerror_errors_are_fatal(), non-fatal otherwise. */
    ICAL_ERROR_DEFAULT,

    /** Asked state for an unknown error type. */
    ICAL_ERROR_UNKNOWN
} icalerrorstate;

/**
 * @brief Returns the current ::icalerrno value
 * @return A pointer to the current ::icalerrno value
 *
 * Yields a pointer to the current ::icalerrno value. This can
 * be used to access (read from and write to) it.
 *
 * @par Examples
 * ```c
 * assert(*icalerror_icalerrno() == icalerrno);
 * ```
 */
LIBICAL_ICAL_EXPORT icalerrorenum *icalerror_icalerrno(void);

/**
 * @brief Access the current ::icalerrno value
 * @return The current ::icalerrno value
 * @note Pseudo-variable that can be used to access the current
 *  ::icalerrno.
 *
 * @par Usage
 * ```c
 * if(icalerrno == ICAL_PARSE_ERROR) {
 *     // ...
 * }
 *
 * // resets error
 * icalerrno = ICAL_NO_ERROR;
 * ```
 */
#define icalerrno (*(icalerror_icalerrno()))

/**
 * @brief Sets the ::icalerrno to a given error
 * @param x The error to set ::icalerrno to
 *
 * Sets ::icalerrno to the error given in @a x. Additionally, if
 * the error is an ::ICAL_ERROR_FATAL or if it's an ::ICAL_ERROR_DEFAULT
 * and icalerror_get_errors_are_fatal() is true, it prints a warning to
 * @a stderr and aborts the process.
 *
 * @par Usage
 * ```c
 * icalerror_set_errno(ICAL_PARSE_ERROR);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_set_errno(icalerrorenum x);

/**
 * @brief Finds the description string for error
 * @param e The type of error that occurred
 * @return A string describing the error that occurred
 *
 * @par Error handling
 * If the type of error @a e wasn't found, it returns the description
 * for ::ICAL_UNKNOWN_ERROR.
 *
 * @par Ownership
 * The string that is returned is owned by the library and must not
 * be free'd() by the user.
 *
 * @par Usage
 * ```c
 * if(icalerrno != ICAL_NO_ERROR) {
 *     printf("%s\n", icalerror_strerror(icalerrno));
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT const char *icalerror_strerror(icalerrorenum e);

/**
 * Gets the description string for the current error in ::icalerrno
 *
 * @par Error handling
 * If the type of error wasn't found, it returns the description
 * for ::ICAL_UNKNOWN_ERROR.
 *
 * @par Ownership
 * The string that is returned is owned by the library and must not
 * be freed by the user.
 *
 * @par Usage
 * ```c
 * if(icalerrno != ICAL_NO_ERROR) {
 *     printf("%s\n", icalerror_perror());
 * }
 * ```
 *
 * @return a pointer to a char string containing the description of the current icalerror.
 */
LIBICAL_ICAL_EXPORT const char *icalerror_perror(void);

/**
 * @brief Sets the ::icalerrorstate for a given ::icalerrorenum @a error
 * @param error The error to change
 * @param state The new error state of the error
 *
 * Sets the severity of a given error. For example, it can be used to
 * set the severity of an ::ICAL_PARSE_ERROR to be an ::ICAL_ERROR_NONFATAL.
 *
 * @par Usage
 * ```c
 * icalerror_set_error_state(ICAL_PARSE_ERROR, ICAL_ERROR_NONFATAL);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_set_error_state(icalerrorenum error, icalerrorstate state);

/**
 * @brief Gets the error state (severity) for a given error
 * @param error The error to examine
 * @return Returns the severity of the error
 */
LIBICAL_ICAL_EXPORT icalerrorstate icalerror_get_error_state(icalerrorenum error);

/**
 * @brief Reads an error from a string
 * @param str The error name string
 * @return An ::icalerrorenum representing the error
 *
 * @par Error handling
 * If the error specified in @a str can't be found, instead
 * ::ICAL_UNKNOWN_ERROR is returned.
 *
 * @par Usage
 * ```c
 * assert(icalerror_error_from_string("PARSE") == ICAL_PARSE_ERROR);
 * assert(icalerror_error_from_string("NONSENSE") == ICAL_UNKNOWN_ERROR);
 * ```
 */
LIBICAL_ICAL_EXPORT icalerrorenum icalerror_error_from_string(const char *str);

/**
 * @brief Change if errors are fatal
 * @param fatal If true, libical aborts after a call to icalerror_set_error()
 * @warning NOT THREAD SAFE: it is recommended that you do not change
 *  this in a multithreaded program.
 *
 * @par Usage
 * ```c
 * icalerror_set_errors_are_fatal(true); // default
 * icalerror_set_errors_are_fatal(false);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_set_errors_are_fatal(bool fatal);

/**
 * @brief Determine if errors are fatal
 * @return True if libical errors are fatal
 *
 * @par Usage
 * ```c
 * if(icalerror_get_errors_are_fatal()) {
 *     // since errors are fatal, this will abort the
 *     // program.
 *     icalerror_set_errno(ICAL_PARSE_ERROR);
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalerror_get_errors_are_fatal(void);

/**
 * @brief Resets icalerrno to ::ICAL_NO_ERROR
 *
 * @par Usage
 * ```c
 * if(icalerrno == ICAL_PARSE_ERROR) {
 *     // ignore parsing errors
 *     icalerror_clear_errno();
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_clear_errno(void);
/* String interfaces to set an error to NONFATAL and restore it to its original value */

/**
 * @brief Suppresses a given error
 * @param error The name of the error to suppress
 * @return The previous icalerrorstate (severity)
 *
 * Calling this function causes the given error to be listed as
 * ::ICAL_ERROR_NONFATAL, and thus suppressed. Error states can be
 * restored with icalerror_restore().
 *
 * @par Usage
 * ```c
 * // suppresses internal errors
 * icalerror_supress("INTERNAL");
 * ```
 */
LIBICAL_ICAL_EXPORT icalerrorstate icalerror_supress(const char *error);

/**
 * Assigns the given error the given icalerrorstate (severity).
 * @param error The error in question
 * @param es The icalerrorstate (severity) to set it to
 *
 * Calling the function changes the ::icalerrorstate of the given error.
 *
 * @par Usage
 * ```c
 * // suppress internal errors
 * icalerror_supress("INTERNAL");
 *
 * // ...
 *
 * // restore internal errors
 * icalerror_restore("INTERNAL", ICAL_ERROR_DEFAULT);
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_restore(const char *error, icalerrorstate es);

/**
 * @brief Prints backtrace
 * @note Only works on systems that support it (HAVE_BACKTRACE enabled).
 *
 * @par Usage
 * ```
 * if(icalerrno != ICAL_NO_ERROR) {
 *     icalerror_backtrace();
 * }
 * ```
 */
LIBICAL_ICAL_EXPORT void icalerror_backtrace(void);

#endif /* !ICALERROR_H */

/*
 *  SPDX-FileCopyrightText: Allen Winter <winter@kde.org>
 *  SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 */

/**
 * @file icallimits.h
 * @brief Defines the interface for getting/setting internal library limits.
 */

#ifndef LIBICAL_LIMITS_H
#define LIBICAL_LIMITS_H

#include "libical_ical_export.h"

#include <stddef.h>

/**
 * The types of limits
 */
typedef enum icallimits_kind
{
    /** Maximum number of parse failures allowed in a calendar file before processing halts */
    ICAL_LIMIT_PARSE_FAILURES,
    /** Maximum number of parse characters to search in a calendar component for the next parameter or property */
    ICAL_LIMIT_PARSE_SEARCH,
    /** Maximum number of parse failure messages inserted into the output (by `insert_error()`) */
    ICAL_LIMIT_PARSE_FAILURE_ERROR_MESSAGES,
    /** Maximum number of properties allowed in a calendar component */
    ICAL_LIMIT_PROPERTIES,
    /** Maximum number of parameters allowed for a property */
    ICAL_LIMIT_PARAMETERS,
    /** Maximum number of characters for a value */
    ICAL_LIMIT_VALUE_CHARS,
    /** Maximum number of values allowed for multi-valued properties */
    ICAL_LIMIT_PROPERTY_VALUES,
    /** Maximum number of times to search for the next recurrence before giving up */
    ICAL_LIMIT_RECURRENCE_SEARCH,
    /** Maximum number of times to search for the next recurrence before time is considered standing still */
    ICAL_LIMIT_RECURRENCE_TIME_STANDING_STILL,
    /** Maximum number of times to search vtimezone rrules for an occurrence before the specified end year */
    ICAL_LIMIT_RRULE_SEARCH,
} icallimits_kind;

/**
 * Gets the value for the corresponding internal library limit.
 *
 * @param kind is the icallimits_kind of limit to get.
 *
 * @returns The current value of the specified @p kind"
 */
LIBICAL_ICAL_EXPORT size_t icallimit_get(icallimits_kind kind);

/**
 * Sets the value for the corresponding internal library limit.
 *
 * @param kind is the icallimits_kind of limit to set.
 * @param limit is the limit value. Use SIZE_MAX (i.e. maximum value of size_t) to set an unlimited value.
 */
LIBICAL_ICAL_EXPORT void icallimit_set(icallimits_kind kind, size_t limit);

#endif

/*======================================================================
  FILE: icalrestriction.h
  CREATOR: eric 24 April 1999

 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 Contributions from:
    Graham Davison (g.m.davison@computer.org)
======================================================================*/

#ifndef ICALRESTRICTION_H
#define ICALRESTRICTION_H

/**
 * @file icalrestriction.h
 * @brief Functions to check if an icalcomponent meets the restrictions
 *  imposed by the standard.
 */

#include "libical_ical_export.h"


/**
 * @brief The kinds of icalrestrictions there are
 *
 * These must stay in this order for icalrestriction_compare to work
 */
typedef enum icalrestriction_kind
{
    /** No restriction. */
    ICAL_RESTRICTION_NONE = 0, /* 0 */

    /** Zero. */
    ICAL_RESTRICTION_ZERO, /* 1 */

    /** One. */
    ICAL_RESTRICTION_ONE, /* 2 */

    /** Zero or more. */
    ICAL_RESTRICTION_ZEROPLUS, /* 3 */

    /** One or more. */
    ICAL_RESTRICTION_ONEPLUS, /* 4 */

    /** Zero or one. */
    ICAL_RESTRICTION_ZEROORONE, /* 5 */

    /** Zero or one, exclusive with another property. */
    ICAL_RESTRICTION_ONEEXCLUSIVE, /* 6 */

    /** Zero or one, mutual with another property. */
    ICAL_RESTRICTION_ONEMUTUAL, /* 7 */

    /** Unknown. */
    ICAL_RESTRICTION_UNKNOWN /* 8 */
} icalrestriction_kind;

/**
 * @brief Checks if the given @a count is in accordance with the given
 *  restriction, @a restr.
 * @param restr The restriction to apply to the @a count
 * @param count The amount present that is to be checked against the restriction
 * @return true if the restriction is met, false if not
 *
 * @par Example
 * ```c
 * assert(icalrestriction_compare(ICALRESTRICTION_ONEPLUS, 5) == true);
 * assert(icalrestriction_compare(ICALRESTRICTION_NONE,    3) == false);
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalrestriction_compare(icalrestriction_kind restr, int count);

/**
 * @brief Checks if a given `VCALENDAR` meets all the restrictions imposed by
 *  the standard.
 * @param comp The `VCALENDAR` component to check
 * @return true if the restrictions are met, false if not
 *
 * @par Error handling
 * Returns false and sets ::icalerrno if `NULL` is passed as @a comp, or if the
 * component is not a `VCALENDAR`.
 *
 * @par Example
 * ```c
 * icalcomponent *component = // ...
 *
 * // check component
 * assert(icalrestriction_check(component) == true);
 * ```
 */
LIBICAL_ICAL_EXPORT bool icalrestriction_check(icalcomponent *comp);

#endif /* !ICALRESTRICTION_H */


#ifdef __cplusplus
}
#endif
#endif
#endif

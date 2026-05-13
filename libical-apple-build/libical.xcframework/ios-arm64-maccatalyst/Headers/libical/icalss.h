#ifndef LIBICAL_ICALSS_H
#define LIBICAL_ICALSS_H
#ifndef S_SPLINT_S
#ifdef __cplusplus
extern "C" {
#endif
/*======================================================================
 FILE: icalgauge.h
 CREATOR: eric 23 December 1999
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/
/**
 * @file icalgauge.h
 * @brief Routines implementing a filter for ical components
 */
#ifndef ICALGAUGE_H
#define ICALGAUGE_H
#include "libical_icalss_export.h"
/// @cond PRIVATE
typedef struct icalgauge_impl icalgauge;
/// @endcond
/**
 * Construct a new icalguage from SQL with a specified expand value.
 *
 * @param sql is a pointer to a char string containing a valid SQL command
 * @param expand some integer to associate with this icalgauge
 *
 * @return a pointer to the newly construct icalgauge or NULL if the SQL parser failed.
 */
LIBICAL_ICALSS_EXPORT icalgauge *icalgauge_new_from_sql(const char *sql, int expand);
/**
 * Returns the expand value for the specified icalgauge.
 *
 * @param gauge is a pointer to a valid icalgauge.
 *
 * @return the expanded @p gauge integer value. or -1 if @p gauge is NULL.
 */
LIBICAL_ICALSS_EXPORT int icalgauge_get_expand(const icalgauge *gauge);
/**
 * Frees memory for the specified icalgauge.
 *
 * @param gauge a non-NULL pointer to valid icalgauge
 */
LIBICAL_ICALSS_EXPORT void icalgauge_free(icalgauge *gauge);
/**
 * (Debug) Prints gauge information to STDOUT.
 *
 * @param gauge is a pointer to a vaid icalgauge.
 */
LIBICAL_ICALSS_EXPORT void icalgauge_dump(icalgauge *gauge);
/**
 * Returns true if comp matches the gauge.
 *
 * @param g a pointer to a valid icalgauge
 * @param comp a pointer to a valid icalcomponent
 *
 * The component @p comp must be in canonical form, i.e. a VCALENDAR with
 * either a VEVENT, VTODO or VJOURNAL sub-component.
 *
 * @return true if there's a match; false otherwise.
 */
LIBICAL_ICALSS_EXPORT bool icalgauge_compare(icalgauge *g, icalcomponent *comp);
#endif /* ICALGAUGE_H */
/*
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
*/
/**
 @file icalset.h
 @author eric 28 November 1999
 @brief Icalset is the "base class" for representations of a collection of iCal components.
 Derived classes (actually delegatees) include:
    icalfileset   Store components in a single file
    icaldirset    Store components in multiple files in a directory
    icalbdbset    Store components in a Berkeley DB File
    icalheapset   Store components on the heap
    icalmysqlset  Store components in a mysql database.
*/
#ifndef ICALSET_H
#define ICALSET_H
#include "libical_icalss_export.h"
typedef struct icalset_impl icalset;
/**
 * The kinds of supported sets.
 */
typedef enum icalset_kind
{
    ICAL_FILE_SET, /**< file based */
    ICAL_DIR_SET,  /**< directory based */
    ICAL_BDB_SET   /**< Berkely database based */
} icalset_kind;
struct icalcompiter;
typedef struct icalsetiter {
    icalcompiter iter; /* icalcomponent_kind, icalpvl_elem iter */
    icalgauge *gauge;
    icalrecur_iterator *ritr;      /*the last iterator */
    icalcomponent *last_component; /*the pending recurring component to be processed  */
    const char *tzid;              /* the calendar's timezone id */
} icalsetiter;
struct icalset_impl {
    icalset_kind kind;
    size_t size;
    char *dsn;
    icalset *(*init)(icalset *set, const char *dsn, void *options);
    void (*free)(icalset *set);
    const char *(*path)(icalset *set);
    void (*mark)(icalset *set);
    icalerrorenum (*commit)(icalset *set);
    icalerrorenum (*add_component)(icalset *set, icalcomponent *comp);
    icalerrorenum (*remove_component)(icalset *set, icalcomponent *comp);
    int (*count_components)(icalset *set, icalcomponent_kind kind);
    icalerrorenum (*select)(icalset *set, icalgauge *gauge);
    void (*clear)(icalset *set);
    icalcomponent *(*fetch)(icalset *set, icalcomponent_kind kind, const char *uid);
    icalcomponent *(*fetch_match)(icalset *set, const icalcomponent *comp);
    int (*has_uid)(icalset *set, const char *uid);
    icalerrorenum (*modify)(icalset *set, icalcomponent *old, icalcomponent *newc);
    icalcomponent *(*get_current_component)(icalset *set);
    icalcomponent *(*get_first_component)(icalset *set);
    icalcomponent *(*get_next_component)(icalset *set);
    icalsetiter (*icalset_begin_component)(icalset *set,
                                           icalcomponent_kind kind, icalgauge *gauge,
                                           const char *tzid);
    icalcomponent *(*icalsetiter_to_next)(icalset *set, icalsetiter *i);
    icalcomponent *(*icalsetiter_to_prior)(icalset *set, icalsetiter *i);
};
/**
 * Registers a new derived class.
 *
 * @param set a pointer to a valid icalset to register.
 *
 * @return true if the registration succeeded; false otherwise.
 */
LIBICAL_ICALSS_EXPORT bool icalset_register_class(icalset *set);
/**
 * Generic icalset constructor.
 *
 * @param kind the type of icalset to create
 * @param dsn the data Source Name - usually a pathname or DB handle
 * @param options any implementation specific options
 *
 * @return a valid icalset reference or NULL if error.
 *
 * This creates any of the icalset types available.
 */
LIBICAL_ICALSS_EXPORT icalset *icalset_new(icalset_kind kind, const char *dsn, void *options);
LIBICAL_ICALSS_EXPORT icalset *icalset_new_file(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalset_new_file_reader(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalset_new_file_writer(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalset_new_dir(const char *path);
/**
 * Frees the memory associated with this icalset
 * automatically calls the implementation specific free routine
 */
LIBICAL_ICALSS_EXPORT void icalset_free(icalset *set);
LIBICAL_ICALSS_EXPORT const char *icalset_path(icalset *set);
/**
 * Marks the cluster as changed, so it will be written to disk when it is freed.
 **/
LIBICAL_ICALSS_EXPORT void icalset_mark(icalset *set);
/**
 * Writes changes to disk immediately.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icalset_commit(icalset *set);
LIBICAL_ICALSS_EXPORT icalerrorenum icalset_add_component(icalset *set, icalcomponent *comp);
LIBICAL_ICALSS_EXPORT icalerrorenum icalset_remove_component(icalset *set, icalcomponent *comp);
LIBICAL_ICALSS_EXPORT int icalset_count_components(icalset *set, icalcomponent_kind kind);
/**
 * Restricts the component returned by icalset_first, _next to those that pass the gauge.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icalset_select(icalset *set, icalgauge *gauge);
/**
 * Gets a component by uid.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalset_fetch(icalset *set, const char *uid);
LIBICAL_ICALSS_EXPORT int icalset_has_uid(icalset *set, const char *uid);
LIBICAL_ICALSS_EXPORT icalcomponent *icalset_fetch_match(icalset *set, const icalcomponent *c);
/**
 * Modifies components according to the MODIFY method of CAP. Works on the
 * currently selected components.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icalset_modify(icalset *set,
                                                   icalcomponent *oldc, icalcomponent *newc);
/**
 * Iterates through the components. If a gauge has been defined, these will skip
 * over components that do not pass the gauge.
 */
/**
 * Gets the current component from the specified icalset.
 *
 * @param set is a pointer to a valid icalset
 *
 * @return a pointer to the current icalcomponent for the @p set; or NULL if there is none.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalset_get_current_component(icalset *set);
/**
 * Gets the first component from the specified icalset.
 *
 * @param set is a pointer to a valid icalset
 *
 * @return a pointer to the first icalcomponent of the @p set; or NULL if there is none.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalset_get_first_component(icalset *set);
/**
 * Gets the next component of the specified icalset.
 *
 * @param set is a pointer to a valid icalset
 *
 * @return a pointer to the next icalcomponent of the @p set; or NULL if there is none.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalset_get_next_component(icalset *set);
/** External Iterator with gauge - for thread safety */
LIBICAL_ICALSS_EXPORT extern icalsetiter icalsetiter_null;
LIBICAL_ICALSS_EXPORT icalsetiter icalset_begin_component(icalset *set,
                                                          icalcomponent_kind kind,
                                                          icalgauge *gauge, const char *tzid);
/** Default _next, _prior, _deref for subclasses that use single cluster */
LIBICAL_ICALSS_EXPORT icalcomponent *icalsetiter_next(icalsetiter *i);
LIBICAL_ICALSS_EXPORT icalcomponent *icalsetiter_prior(icalsetiter *i);
LIBICAL_ICALSS_EXPORT icalcomponent *icalsetiter_deref(icalsetiter *i);
/** for subclasses that use multiple clusters that require specialized cluster traversal */
LIBICAL_ICALSS_EXPORT icalcomponent *icalsetiter_to_next(icalset *set, icalsetiter *i);
LIBICAL_ICALSS_EXPORT icalcomponent *icalsetiter_to_prior(icalset *set, icalsetiter *i);
#endif /* !ICALSET_H */
/*======================================================================
 FILE: icalcluster.h
 CREATOR: acampi 13 March 2002
 SPDX-FileCopyrightText: 2002 Andrea Campi <a.campi@inet.it>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
======================================================================*/
/**
 * @file icalcluster.h
 * @brief Defines the data structure for calendar clusters.
 *
 * This is a utility class designed to manage clusters of icalcomponents
 * on behalf of an implementation of icalset. This is done in order to
 * split out common behavior different classes might need.
 *
 * The definition of what exactly a cluster will contain depends on the
 * icalset subclass. At the basic level, an icluster is just a tuple,
 * with anything as key and an icalcomponent as value.
 */
#ifndef ICALCLUSTER_H
#define ICALCLUSTER_H
#include "libical_icalss_export.h"
typedef struct icalcluster_impl icalcluster;
/**
 * @brief Create a cluster with a key/value pair.
 *
 * @todo Always do a deep copy.
 */
LIBICAL_ICALSS_EXPORT icalcluster *icalcluster_new(const char *key, icalcomponent *data);
/**
 * Deeply clone an icalcluster.
 * Returns a pointer to the memory for the newly cloned icalcluster.
 * @since 4.0
*/
LIBICAL_ICALSS_EXPORT icalcluster *icalcluster_clone(const icalcluster *old);
LIBICAL_ICALSS_EXPORT void icalcluster_free(icalcluster *cluster);
LIBICAL_ICALSS_EXPORT const char *icalcluster_key(const icalcluster *cluster);
LIBICAL_ICALSS_EXPORT int icalcluster_is_changed(const icalcluster *cluster);
LIBICAL_ICALSS_EXPORT void icalcluster_mark(icalcluster *cluster);
LIBICAL_ICALSS_EXPORT void icalcluster_commit(icalcluster *cluster);
LIBICAL_ICALSS_EXPORT icalcomponent *icalcluster_get_component(const icalcluster *cluster);
LIBICAL_ICALSS_EXPORT int icalcluster_count_components(icalcluster *cluster,
                                                       icalcomponent_kind kind);
LIBICAL_ICALSS_EXPORT icalerrorenum icalcluster_add_component(icalcluster *cluster,
                                                              icalcomponent *child);
LIBICAL_ICALSS_EXPORT icalerrorenum icalcluster_remove_component(icalcluster *cluster,
                                                                 icalcomponent *child);
LIBICAL_ICALSS_EXPORT icalcomponent *icalcluster_get_current_component(icalcluster *cluster);
LIBICAL_ICALSS_EXPORT icalcomponent *icalcluster_get_first_component(icalcluster *cluster);
LIBICAL_ICALSS_EXPORT icalcomponent *icalcluster_get_next_component(icalcluster *cluster);
#endif /* !ICALCLUSTER_H */
/*======================================================================
 FILE: icalfileset.h
 CREATOR: eric 23 December 1999
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/
/**
 * @file icalfileset.h
 * @brief Manages a database of ical components and offers interfaces for
 * reading, writing and searching for components.
 */
#ifndef ICALFILESET_H
#define ICALFILESET_H
#include "libical_icalss_export.h"
typedef struct icalfileset_impl icalfileset;
LIBICAL_ICALSS_EXPORT icalset *icalfileset_new(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalfileset_new_reader(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalfileset_new_writer(const char *path);
LIBICAL_ICALSS_EXPORT icalset *icalfileset_init(icalset *set, const char *path, void *options_in);
LIBICAL_ICALSS_EXPORT icalcluster *icalfileset_produce_icalcluster(const char *path);
LIBICAL_ICALSS_EXPORT void icalfileset_free(icalset *set);
LIBICAL_ICALSS_EXPORT const char *icalfileset_path(icalset *set);
/* Mark the cluster as changed, so it will be written to disk when it
   is freed. Commit writes to disk immediately. */
LIBICAL_ICALSS_EXPORT void icalfileset_mark(icalset *set);
LIBICAL_ICALSS_EXPORT icalerrorenum icalfileset_commit(icalset *set);
LIBICAL_ICALSS_EXPORT icalerrorenum icalfileset_add_component(icalset *set, icalcomponent *child);
LIBICAL_ICALSS_EXPORT icalerrorenum icalfileset_remove_component(icalset *set,
                                                                 icalcomponent *child);
LIBICAL_ICALSS_EXPORT int icalfileset_count_components(icalset *set, icalcomponent_kind kind);
/**
 * Restricts the component returned by icalfileset_first, _next to those
 * that pass the gauge. _clear removes the gauge.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icalfileset_select(icalset *set, icalgauge *gauge);
/** @brief Clears the gauge **/
LIBICAL_ICALSS_EXPORT void icalfileset_clear(icalset *set);
/** @brief Gets and searches for a component by uid **/
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_fetch(icalset *set,
                                                       icalcomponent_kind kind, const char *uid);
LIBICAL_ICALSS_EXPORT int icalfileset_has_uid(icalset *set, const char *uid);
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_fetch_match(icalset *set, const icalcomponent *c);
/**
 *  @brief Modifies components according to the MODIFY method of CAP.
 *
 *  Works on the currently selected components.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icalfileset_modify(icalset *set,
                                                       icalcomponent *oldcomp,
                                                       icalcomponent *newcomp);
/* Iterates through components. If a gauge has been defined, these
   will skip over components that do not pass the gauge */
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_get_current_component(icalset *set);
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_get_first_component(icalset *set);
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_get_next_component(icalset *set);
/* External iterator for thread safety */
LIBICAL_ICALSS_EXPORT icalsetiter icalfileset_begin_component(icalset *set,
                                                              icalcomponent_kind kind,
                                                              icalgauge *gauge, const char *tzid);
LIBICAL_ICALSS_EXPORT icalcomponent *icalfilesetiter_to_next(icalset *set, icalsetiter *iter);
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_form_a_matched_recurrence_component(icalsetiter *
                                                                                         itr);
/** Returns a reference to the internal component. **You probably should
   not be using this.** */
LIBICAL_ICALSS_EXPORT icalcomponent *icalfileset_get_component(icalset *set);
/**
 * @brief Options for opening an icalfileset.
 *
 * These options should be passed to the icalset_new() function
 */
typedef struct icalfileset_options {
    int flags;            /**< flags for open() O_RDONLY, etc  */
    int mode;             /**< file mode */
    int safe_saves;       /**< to lock or not */
    icalcluster *cluster; /**< use this cluster to initialize data */
} icalfileset_options;
extern icalfileset_options icalfileset_options_default;
#endif /* !ICALFILESET_H */
/*======================================================================
 FILE: icaldirset.h
 CREATOR: eric 28 November 1999
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/
/**
  @file icaldirset.h
  @brief Manages a database of ical components and offers interfaces for
  reading, writing and searching for components.
  icaldirset groups components in to clusters based on their DTSTAMP
  time -- all components that start in the same month are grouped
  together in a single file. All files in a store are kept in a single
  directory.
  The primary interfaces are icaldirset__get_first_component and
  icaldirset_get_next_component. These routine iterate through all of
  the components in the store, subject to the current gauge. A gauge
  is an icalcomponent that is tested against other components for a
  match. If a gauge has been set with icaldirset_select,
  icaldirset_first and icaldirset_next will only return components
  that match the gauge.
  The Store generated UIDs for all objects that are stored if they do
  not already have a UID. The UID is the name of the cluster (month &
  year as MMYYYY) plus a unique serial number. The serial number is
  stored as a property of the cluster.
*/
#ifndef ICALDIRSET_H
#define ICALDIRSET_H
#include "libical_icalss_export.h"
/* icaldirset Routines for storing, fetching, and searching for ical
 * objects in a database */
typedef struct icaldirset_impl icaldirset;
LIBICAL_ICALSS_EXPORT icalset *icaldirset_new(const char *dir);
LIBICAL_ICALSS_EXPORT icalset *icaldirset_new_reader(const char *dir);
LIBICAL_ICALSS_EXPORT icalset *icaldirset_new_writer(const char *dir);
LIBICAL_ICALSS_EXPORT icalset *icaldirset_init(icalset *set, const char *dir, void *options_in);
LIBICAL_ICALSS_EXPORT void icaldirset_free(icalset *set);
LIBICAL_ICALSS_EXPORT const char *icaldirset_path(icalset *set);
/* Marks the cluster as changed, so it will be written to disk when it
   is freed. Commit writes to disk immediately*/
LIBICAL_ICALSS_EXPORT void icaldirset_mark(icalset *set);
LIBICAL_ICALSS_EXPORT icalerrorenum icaldirset_commit(icalset *set);
/**
 * Adds a component to the current cluster.
 *
 * This assumes that the top level component is a VCALENDAR, and there is an
 * inner component of either VEVENT, VTODO or VJOURNAL. The inner component
 * must have a DTSTAMP property.
 *
 * @param set is a pointer to a valid icalset
 * @param comp is a pointer to the icalcomponent to add
 *
 * @return ::ICAL_NO_ERROR it @p comp was successfully added; if not, an error occurred.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icaldirset_add_component(icalset *set, icalcomponent *comp);
/**
 * Remove a component in the current cluster. HACK. This routine is a
 * "friend" of icalfileset, and breaks its encapsulation. It was
 * either do it this way, or add several layers of interfaces that had
 * no other use.
 *
 * @param set is a pointer to a valid icalset
 * @param comp is a pointer to the icalcomponent to remove
 *
 * @return ::ICAL_NO_ERROR it @p comp was successfully removed; if not, an error occurred.
 */
LIBICAL_ICALSS_EXPORT icalerrorenum icaldirset_remove_component(icalset *set,
                                                                icalcomponent *comp);
LIBICAL_ICALSS_EXPORT int icaldirset_count_components(icalset *store, icalcomponent_kind kind);
/* Restricts the component returned by icaldirset_first, _next to those
   that pass the gauge. _clear removes the gauge. */
LIBICAL_ICALSS_EXPORT icalerrorenum icaldirset_select(icalset *set, icalgauge *gauge);
LIBICAL_ICALSS_EXPORT void icaldirset_clear(icalset *set);
/* Gets a component by uid */
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirset_fetch(icalset *set,
                                                      icalcomponent_kind kind, const char *uid);
LIBICAL_ICALSS_EXPORT int icaldirset_has_uid(icalset *set, const char *uid);
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirset_fetch_match(icalset *set, const icalcomponent *c);
/* Modifies components according to the MODIFY method of CAP. Works on
   the currently selected components. */
LIBICAL_ICALSS_EXPORT icalerrorenum icaldirset_modify(icalset *set,
                                                      icalcomponent *oldcomp, icalcomponent *newcomp);
/* Iterates through the components. If a gauge has been defined, these
   will skip over components that do not pass the gauge */
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirset_get_current_component(icalset *set);
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirset_get_first_component(icalset *set);
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirset_get_next_component(icalset *set);
/* External iterator for thread safety */
LIBICAL_ICALSS_EXPORT icalsetiter icaldirset_begin_component(icalset *set,
                                                             icalcomponent_kind kind,
                                                             icalgauge *gauge, const char *tzid);
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirsetiter_to_next(icalset *set, icalsetiter *i);
LIBICAL_ICALSS_EXPORT icalcomponent *icaldirsetiter_to_prior(icalset *set, icalsetiter *i);
typedef struct icaldirset_options {
    int flags; /**< flags corresponding to the open() system call O_RDWR, etc. */
} icaldirset_options;
#endif /* !ICALDIRSET_H */
/*======================================================================
 FILE: icalcalendar.h
 CREATOR: eric 23 December 1999
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 The Original Code is eric. The Initial Developer of the Original
 Code is Eric Busboom
======================================================================*/
/**
 * @file icalcalendar.h
 * @brief Routines for storing calendar data in a file system.
 *
 * The calendar has two icaldirsets, one for incoming components and one for
 * booked components. It also has interfaces to access the free/busy list and a
 * list of calendar properties
 */
#ifndef ICALCALENDAR_H
#define ICALCALENDAR_H
#include "libical_icalss_export.h"
typedef struct icalcalendar_impl icalcalendar;
LIBICAL_ICALSS_EXPORT icalcalendar *icalcalendar_new(const char *dir);
LIBICAL_ICALSS_EXPORT void icalcalendar_free(icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT int icalcalendar_lock(const icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT int icalcalendar_unlock(const icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT int icalcalendar_islocked(const icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT int icalcalendar_ownlock(const icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT icalset *icalcalendar_get_booked(icalcalendar *calendar);
LIBICAL_ICALSS_EXPORT icalset *icalcalendar_get_incoming(icalcalendar *calendar);
/**
 * Gets the properties from the specified icalcalendar.
 *
 * @param calendar is a pointer to a valid icalendar
 *
 * @return a pointer to an icalset with the properties.
 */
LIBICAL_ICALSS_EXPORT icalset *icalcalendar_get_properties(icalcalendar *calendar);
/**
 * Gets the freebusy info from the specified icalcalendar.
 *
 * @param calendar is a pointer to a valid icalendar
 *
 * @return a pointer to an icalset with the freebusy info.
 */
LIBICAL_ICALSS_EXPORT icalset *icalcalendar_get_freebusy(icalcalendar *calendar);
#endif /* !ICALCALENDAR_H */
/*======================================================================
 FILE: icalclassify.h
 CREATOR: eric 21 Aug 2000
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 =========================================================================*/
/**
 * @file icalclassify.h
 * @brief Defines functions for classification.
 */
#ifndef ICALCLASSIFY_H
#define ICALCLASSIFY_H
#include "libical_icalss_export.h"
LIBICAL_ICALSS_EXPORT icalproperty_xlicclass icalclassify(icalcomponent *c,
                                                          icalcomponent *match, const char *user);
LIBICAL_ICALSS_EXPORT icalcomponent *icalclassify_find_overlaps(icalset *set,
                                                                icalcomponent *comp);
#endif /* ICALCLASSIFY_H */
/*======================================================================
 FILE: icalspanlist.h
 CREATOR: eric 21 Aug 2000
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
=========================================================================*/
#ifndef ICALSPANLIST_H
#define ICALSPANLIST_H
#include "libical_icalss_export.h"
/**
 * @file icalspanlist.h
 * @brief Code that supports collections of free/busy spans of time
 */
/// @cond PRIVATE
struct icalpvl_list_t;
struct icalspanlist_impl {
    struct icalpvl_list_t *spans; /**< list of icaltime_span data **/
    struct icaltimetype start;    /**< start time of span **/
    struct icaltimetype end;      /**< end time of span **/
};
typedef struct icalspanlist_impl icalspanlist;
/// @endcond
/**
 * Makes a free list from a set of VEVENT components.
 *
 *  @param set a pointer to valid icalset containing VEVENTS
 *  @param start  the free list starts at this date/time
 *  @param end the free list ends at this date/time
 *
 *  @return a spanlist corresponding to the VEVENTS
 *
 * Given a set of components, a start time and an end time
 * return a spanlist that contains the free/busy times.
 * @p start and @p end should be in UTC.
 */
LIBICAL_ICALSS_EXPORT icalspanlist *icalspanlist_new(icalset *set,
                                                     struct icaltimetype start,
                                                     struct icaltimetype end);
/**
 * Destructor.
 *
 * @param sl A valid icalspanlist
 *
 *  Frees the memory associated with the spanlist.
 */
LIBICAL_ICALSS_EXPORT void icalspanlist_free(icalspanlist *sl);
/**
 * Finds the next free time span in a spanlist.
 *
 * @param  sl a pointer to a valid icalspanlist to search
 * @param  t the time to start looking.
 *
 * Given a spanlist and a time, finds the next period of free time.
 *
 * @return an icalperiodtype representing the free type period; if no free time is
 * available then an invalid icalperiodtype is returned.
 */
LIBICAL_ICALSS_EXPORT struct icalperiodtype icalspanlist_next_free_time(icalspanlist *sl,
                                                                        struct icaltimetype t);
/**
 * (Debug) print out spanlist to STDOUT.
 *
 *  @param sl a pointer to a valid icalspanlist.
 */
LIBICAL_ICALSS_EXPORT void icalspanlist_dump(icalspanlist *sl);
/**
 * Returns a VFREEBUSY component for a spanlist.
 *
 * @param sl a pointer to a valid icalspanlist, from icalspanlist_new()
 * @param organizer  the organizer specified as "MAILTO:user@domain"
 * @param attendee the attendee specified as "MAILTO:user@domain"
 *
 * @return a pointer to an icalcomponent, NULL if the conversion failed.
 *
 * This function returns a VFREEBUSY component for the given spanlist.
 * The start time is mapped to DTSTART, the end time to DTEND.
 * Each busy span is represented as a separate FREEBUSY entry.
 * An attendee parameter is required, and organizer parameter is optional.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalspanlist_as_vfreebusy(icalspanlist *sl,
                                                               const char *organizer,
                                                               const char *attendee);
/**
 * Returns an hour-by-hour array of free/busy times over a given period.
 *
 *  @param spanlist a pointer to a valid icalspanlist
 *  @param delta_t  the time slice to divide by, in seconds.  Default 3600.
 *
 *  @return A pointer to an array of integers containing the number of
 *       busy events in each delta_t time period.  The final entry
 *       contains the value -1.
 *
 *  This calculation is somewhat tricky.  This is due to the fact that
 *  the time range contains the start time, but does not contain the
 *  end time.  To perform a proper calculation we subtract one second
 *  off the end times to get a true containing time.
 *
 *  Also note that if you supplying a spanlist that does not start or
 *  end on a time boundary divisible by delta_t you may get results
 *  that are not quite what you expect.
 */
LIBICAL_ICALSS_EXPORT int *icalspanlist_as_freebusy_matrix(icalspanlist *spanlist, int delta_t);
/**
 * Constructs an icalspanlist from the VFREEBUSY component of an icalcomponent.
 *
 *   @param comp a pointer to a valid icalcomponent
 *
 *   @return a pointer to an icalspanlist or NULL if no VFREEBUSY section.
 */
LIBICAL_ICALSS_EXPORT icalspanlist *icalspanlist_from_vfreebusy(icalcomponent *comp);
#endif
/*======================================================================
 FILE: icalmessage.h
 CREATOR: eric 07 Nov 2000
 SPDX-FileCopyrightText: 2000, Eric Busboom <eric@civicknowledge.com>
 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
 =========================================================================*/
/**
 * @file icalmessage.h
 * @brief Defines functions for creating component reply messages.
 */
#ifndef ICALMESSAGE_H
#define ICALMESSAGE_H
#include "libical_icalss_export.h"
/**
 * Constructs an icalcomponent for an accept reply.
 *
 * @param c is a pointer to a valid icalcomponent
 * @param user is a pointer to a char string containing a user from the attendee list
 * @param msg is a pointer to a char string containing the message
 *
 * @return a pointer to the newly constructed icalcomponent; or NULL if an error occurred
 * like the specified user was not included in the attendee list.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalmessage_new_accept_reply(const icalcomponent *c,
                                                                  const char *user,
                                                                  const char *msg);
/**
 * Constructs a new icalcomponent for a decline reply for an existing icalcomponent.
 *
 * @param c is a pointer to a valid icalcomponent
 * @param user is a pointer to a char string containing a user from the attendee list
 * @param msg is a pointer to a char string containing the message
 *
 * @return a pointer to the newly constructed icalcomponent; or NULL if an error occurred
 * like the specified user was not included in the attendee list.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalmessage_new_decline_reply(const icalcomponent *c,
                                                                   const char *user,
                                                                   const char *msg);
/**
 * Constructs a new icalcomponent for a counterproposal reply for an existing icalcomponent.
 *
 * @param oldc is a pointer to a valid icalcomponent for the current reply to modify
 * @param newc is a pointer to a valid icalcomponent for the newly modified version of @p oldc
 * @param user is a pointer to a char string containing a user from the attendee list
 * @param msg is a pointer to a char string containing the message
 *
 * @return a pointer to the newly constructed icalcomponent; or NULL if an error occurred
 * like the specified user was not included in the attendee list.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalmessage_new_counterpropose_reply(const icalcomponent *oldc,
                                                                          const icalcomponent *newc,
                                                                          const char *user,
                                                                          const char *msg);
/**
 * Constructs a new icalcomponent for a delegate-to reply for an existing icalcomponent.
 *
 * @param c is a pointer to a valid icalcomponent
 * @param user is a pointer to a char string containing a user from the attendee list
 * @param delegatee is a pointer to a char string containing a delegatee, possibly not
 * already included in the attendee list.
 * @param msg is a pointer to a char string containing the message
 *
 * @return a pointer to the newly constructed icalcomponent; or NULL if an error occurred
 * like the specified user was not included in the attendee list.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalmessage_new_delegate_reply(const icalcomponent *c,
                                                                    const char *user,
                                                                    const char *delegatee,
                                                                    const char *msg);
/**
 * Constructs a new icalcomponent for an error reply for an existing icalcomponent.
 *
 * @param c is a pointer to a valid icalcomponent
 * @param user is a pointer to a char string containing a user from the attendee list
 * @param msg is a pointer to a char string containing the error message
 * @param debug is a pointer to a char string to use the debug part of the icalreqstattype to use
 * @param code is a icalrequeststatus code part of the icalreqstattype to use
 *
 * @return a pointer to the newly constructed icalcomponent; or NULL if an error occurred
 * like the specified user was not included in the attendee list.
 */
LIBICAL_ICALSS_EXPORT icalcomponent *icalmessage_new_error_reply(const icalcomponent *c,
                                                                 const char *user,
                                                                 const char *msg,
                                                                 const char *debug,
                                                                 icalrequeststatus code);
#endif /* ICALMESSAGE_H */

#ifdef __cplusplus
}
#endif
#endif
#endif

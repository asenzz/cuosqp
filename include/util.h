#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "constants.h"

/******************
 * Versioning     *
 ******************/

/**
 * Return OSQP version
 * @return  OSQP version
 */
const char *osqp_version(void);


/**********************
 * Utility Functions  *
 **********************/

/**
 * Set default settings from constants.h file
 * assumes settings already allocated in memory
 * @param settings settings structure
 */
void set_default_settings(OSQPSettings * settings);


#ifndef EMBEDDED

/**
 * Copy settings creating a new settings structure (uses MALLOC)
 * @param  settings Settings to be copied
 * @return          New settings structure
 */
OSQPSettings * copy_settings(OSQPSettings * settings);

#endif // #ifndef EMBEDDED

/**
 * Custom string copy to avoid string.h library
 * @param dest   destination string
 * @param source source string
 */
void c_strcpy(char dest[], const char source[]);


#ifdef PRINTING
/**
 * Print Header before running the algorithm
 * @param data     problem data
 * @param settings osqp settings
 */
void print_setup_header(const OSQPData *data, const OSQPSettings *settings);

/**
 * Print header with data to be displayed per iteration
 */
void print_header(void);

/**
 * Print iteration summary
 * @param work current workspace
 */
void print_summary(OSQPWorkspace * work);

/**
 * Print information after polish
 * @param work current workspace
 */
void print_polish(OSQPWorkspace * work);

/**
 * Print footer when algorithm terminates
 * @param info   info structure
 * @param polish is polish enabled?
 */
void print_footer(OSQPInfo * info, c_int polish);

#endif


/*********************************
 * Timer Structs and Functions * *
 *********************************/
 /*! \cond PRIVATE */

#ifdef PROFILING

// Windows
#ifdef IS_WINDOWS

#include <windows.h>

struct OSQP_TIMER {
	LARGE_INTEGER tic;
	LARGE_INTEGER toc;
	LARGE_INTEGER freq;
};

// Mac
#elif defined IS_MAC

#include <mach/mach_time.h>

/* Use MAC OSX  mach_time for timing */
struct OSQP_TIMER {
	uint64_t tic;
	uint64_t toc;
	mach_timebase_info_data_t tinfo;
};

// Linux
#else

/* Use POSIX clocl_gettime() for timing on non-Windows machines */
#include <time.h>
#include <sys/time.h>


struct OSQP_TIMER {
	struct timespec tic;
	struct timespec toc;
};

#endif

/*! \endcond */

/**
 * Timer Methods
 */

/**
 * Start timer
 * @param t Timer object
 */
void tic(OSQPTimer* t);

/**
 * Report time
 * @param  t Timer object
 * @return   Reported time
 */
c_float toc(OSQPTimer* t);

#endif /* END #ifdef PROFILING */



/* ================================= DEBUG FUNCTIONS ======================= */

/*! \cond PRIVATE */


#ifndef EMBEDDED

/* Compare CSC matrices */
c_int is_eq_csc(csc *A, csc *B, c_float tol);

/* Convert sparse CSC to dense */
c_float * csc_to_dns(csc * M);

#endif  // #ifndef EMBEDDED


#ifdef PRINTING
#include <stdio.h>



/* Print a csc sparse matrix */
void print_csc_matrix(csc* M, const char * name);

/* Dump csc sparse matrix to file */
void dump_csc_matrix(csc * M, const char * file_name);

/* Print a triplet format sparse matrix */
void print_trip_matrix(csc* M, const char * name);

/* Print a dense matrix */
void print_dns_matrix(c_float * M, c_int m, c_int n, const char *name);

/* Print vector  */
void print_vec(c_float * v, c_int n, const char *name);

/* Dump vector to file */
void dump_vec(c_float * v, c_int len, const char * file_name);

// Print int array
void print_vec_int(c_int * x, c_int n, const char *name);

#endif

/*! \endcond */


#ifdef __cplusplus
}
#endif

#endif

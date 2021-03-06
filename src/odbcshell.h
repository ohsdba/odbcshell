/*
 *  ODBC Shell
 *  Copyright (C) 2011 Bindle Binaries <syzdek@bindlebinaries.com>.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *  @file src/odbcshell.h ODBC command line client
 */
#ifndef _ODBCSHELL_SRC_ODBCSHELL_H
#define _ODBCSHELL_SRC_ODBCSHELL_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef PMARK
#pragma mark Headers
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>

#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>
#ifdef HAVE_IODBCEXT_H
#include <iodbcext.h>
#endif


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef PMARK
#pragma mark -
#pragma mark Definitions & Macros
#endif

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "odbcshell"
#endif

#ifndef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "syzdek@bindlebinaries.com"
#endif

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "ODBC Shell"
#endif

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION ""
#endif

// runtime modes
#define ODBCSHELL_MODE_SHELL    0x00
#define ODBCSHELL_MODE_SCRIPT   0x01
#define ODBCSHELL_MODE_EXEC     0x02
#define ODBCSHELL_MODE_LISTDSN  0x03
#define ODBCSHELL_MODE_SHOW     0x04

// option types
#define ODBSHELL_OTYPE_MASK       0x0F
#define ODBSHELL_OTYPE_INT        0x01
#define ODBSHELL_OTYPE_BOOL       0x02
#define ODBSHELL_OTYPE_CHAR       0x03

// output formats
#define ODBCSHELL_FORMAT_CSV       0x00
#define ODBCSHELL_FORMAT_FIXED     0x01
#define ODBCSHELL_FORMAT_XML       0x02

// option IDs
#define ODBCSHELL_OPT_CONFFILE    (0x010 | ODBSHELL_OTYPE_CHAR)
#define ODBCSHELL_OPT_CONTINUE    (0x020 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_HISTFILE    (0x030 | ODBSHELL_OTYPE_CHAR)
#define ODBCSHELL_OPT_HISTORY     (0x040 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_NOSHELL     (0x050 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_PROMPT      (0x060 | ODBSHELL_OTYPE_CHAR)
#define ODBCSHELL_OPT_SILENT      (0x070 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_VERBOSE     (0x080 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_ODBCPROMPT  (0x090 | ODBSHELL_OTYPE_BOOL)
#define ODBCSHELL_OPT_FORMAT      (0x0A0 | ODBSHELL_OTYPE_CHAR)

// command IDs
#define ODBCSHELL_CMD             0x00
#define ODBCSHELL_CMD_CLEAR       (1L + ODBCSHELL_CMD)
#define ODBCSHELL_CMD_CLOSE       (1L + ODBCSHELL_CMD_CLEAR)
#define ODBCSHELL_CMD_CONNECT     (1L + ODBCSHELL_CMD_CLOSE)
#define ODBCSHELL_CMD_DISCONNECT  (1L + ODBCSHELL_CMD_CONNECT)
#define ODBCSHELL_CMD_ECHO        (1L + ODBCSHELL_CMD_DISCONNECT)
#define ODBCSHELL_CMD_HELP        (1L + ODBCSHELL_CMD_ECHO)
#define ODBCSHELL_CMD_QUIT        (1L + ODBCSHELL_CMD_HELP)
#define ODBCSHELL_CMD_ODBC        (1L + ODBCSHELL_CMD_QUIT)
#define ODBCSHELL_CMD_OPEN        (1L + ODBCSHELL_CMD_ODBC)
#define ODBCSHELL_CMD_RECONNECT   (1L + ODBCSHELL_CMD_OPEN)
#define ODBCSHELL_CMD_RESET       (1L + ODBCSHELL_CMD_RECONNECT)
#define ODBCSHELL_CMD_SEND        (1L + ODBCSHELL_CMD_RESET)
#define ODBCSHELL_CMD_SET         (1L + ODBCSHELL_CMD_SEND)
#define ODBCSHELL_CMD_SETENV      (1L + ODBCSHELL_CMD_SET)
#define ODBCSHELL_CMD_SHOW        (1L + ODBCSHELL_CMD_SETENV)
#define ODBCSHELL_CMD_SOURCE      (1L + ODBCSHELL_CMD_SHOW)
#define ODBCSHELL_CMD_UNSET       (1L + ODBCSHELL_CMD_SOURCE)
#define ODBCSHELL_CMD_UNSETENV    (1L + ODBCSHELL_CMD_UNSET)
#define ODBCSHELL_CMD_USE         (1L + ODBCSHELL_CMD_UNSETENV)
#define ODBCSHELL_CMD_VERSION     (1L + ODBCSHELL_CMD_USE)
//#define ODBCSHELL_CMD_ALIAS       0x01
//#define ODBCSHELL_CMD_LOADCONF    0x04
//#define ODBCSHELL_CMD_SAVECONF    0x09
//#define ODBCSHELL_CMD_UNALIAS     0x0C


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#ifdef PMARK
#pragma mark -
#pragma mark Datatypes
#endif

/// @brief internal map for switching between an directive's ASCII and numeric values
typedef struct odbcshell_option_data ODBCShellOption;
struct odbcshell_option_data
{
   long long     val;        ///< option ID
   long long     min_arg;    ///< minimum arguments allowed
   long long     max_arg;    ///< maximum arguments allowed
   const char  * name;       ///< option description
   const char  * desc;       ///< option description
   const char ** usage;      ///< option usage
};


/// @brief information describing a column returned with a result
typedef struct odbcshell_column ODBCShellColumn;
struct odbcshell_column
{
   SQLSMALLINT   type;
   SQLSMALLINT   scale;
   SQLSMALLINT   nullable;
   SQLSMALLINT   pad;
   SQLULEN       precision;
   size_t        width;   ///< width of display required to print value
   SQLTCHAR      name[64];    ///< name of column
};


/// @brief ODBC connection information
typedef struct odbcshell_connection ODBCShellConn;
struct odbcshell_connection
{
   char             * name;
   char             * dsn;
   HDBC               hdbc;
   HSTMT              hstmt;
   long long          col_count;
   ODBCShellColumn  * cols;
};


/// @brief contains configuration data
typedef struct odbcshell_config_data ODBCShell;
struct odbcshell_config_data
{
   long long          mode;        ///< run mode for ODBC Shell
   long long          continues;   ///< toggle for continue one error mode
   long long          history;     ///< disables storing history
   long long          noshell;     ///< disables ability to call shell commands
   long long          silent;      ///< toggle for silent mode
   long long          verbose;     ///< toggle for verbose mode
   long long          noprofile;   ///< disables loading of profile
   long long          odbcprompt;  ///< instructs ODBC to not prompt for information
   long long          format;      ///< output format of ODBC results
   long long          conns_count; ///< toggle for verbose mode
   long long          exec_count;  ///< toggle for verbose mode
   FILE             * output;      ///< file to save results
   char             * outputfile;  ///< name of file to save results
   char             * conffile;    ///< odbcshell configuration file
   char             * histfile;    ///< GNU readline history file
   char             * prompt;      ///< shell prompt
   const char       * dflt_dsn;    ///< default DSN to use for "autoconnect"
   const char       * dflt_output; ///< default DSN to use for "autoconnect"
   const char       * dflt_show;   ///< default DSN to use for show data
   char            ** exec_strs;   ///< list of strings to execute
   ODBCShellOption  * active_cmd;  ///< command being actively executed
   HENV               henv;        ///< iODBC environment state
   HDBC               hdbc;        ///< iODBC connection state
   ODBCShellConn    * current;     ///< current connection to use for SQL
   ODBCShellConn   ** conns;       ///< list of active connections
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef PMARK
#pragma mark -
#pragma mark Prototypes
#endif

// displays version information
void odbcshell_version(void);

#endif
/* end of header */

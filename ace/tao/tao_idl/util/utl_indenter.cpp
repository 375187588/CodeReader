// utl_indenter.cpp,v 1.5 1998/08/03 17:40:04 gonzo Exp

/*

COPYRIGHT

Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.

This product is protected by copyright and distributed under the following
license restricting its use.

The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").

The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.

This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.

SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.

IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.

Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.

SunSoft, Inc.  
2550 Garcia Avenue 
Mountain View, California  94043

NOTE:

SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.

 */

// utl_indenter.cc - Implementation of indenter for dumping IDL AST
//

#include	"idl.h"
#include	"idl_extern.h"

ACE_RCSID(util, utl_indenter, "utl_indenter.cpp,v 1.5 1998/08/03 17:40:04 gonzo Exp")

/*
 * Constructors
 */
UTL_Indenter::UTL_Indenter ()
  : pd_indent_level (0)
{
}

/*
 * Private operations
 */

/*
 * Public operations
 */

// Reset indentation level
void
UTL_Indenter::reset ()
{
  pd_indent_level = 0;
}

// Increase indentation level
void
UTL_Indenter::increase ()
{
  pd_indent_level++;
}

// Decrease indentation level
void
UTL_Indenter::decrease ()
{
  if (pd_indent_level > 0)
    pd_indent_level--;
}

// Produce white space to indent to current indentation level on ostream o
void
UTL_Indenter::skip_to (ostream &o)
{
  long i;

  for (i = 0; i < pd_indent_level; i++)
    o << "  ";
}

// Produce white space to indent to current indentation level on ostream o
void
UTL_Indenter::skip_to (FILE *fp)
{
  long i;

  for (i = 0; i < pd_indent_level; i++)
    ACE_OS::fprintf (fp, "  ");
}

/*
 * Redefined virtual operations
 */

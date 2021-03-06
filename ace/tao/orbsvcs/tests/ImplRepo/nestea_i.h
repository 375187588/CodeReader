// -*- C++ -*-

//=============================================================================
/**
 *  @file    nestea_i.h
 *
 *  nestea_i.h,v 1.7 2000/11/10 20:51:20 brunsch Exp
 *
 *  This class is an implementation of the Nestea Bookshelf interface.
 *
 *
 *  @author Darrell Brunsch <brunsch@cs.wustl.edu>
 */
//=============================================================================


#if !defined (NESTEA_I_H)
#define	NESTEA_I_H

#include "NesteaS.h"

// Forward declarations.
class Nestea_i;

// Typedefs.
typedef Nestea_i *Nestea_i_ptr;
typedef Nestea_i_ptr Nestea_i_ref;

/**
 * @class Nestea_i:
 *
 * @brief Nestea Bookshelf Implementation
 *
 * Implements the Nestea Bookshelf server, which keeps track of the
 * number of nestea cans in a bookshelf.  You can drink Nestea to add
 * it to the bookshelf or crush the cans to remove them.
 */
class Nestea_i: public POA_Nestea_Bookshelf
{
public:
  /// Constructor
  Nestea_i (const char *filename = "nestea.dat");

  /// Destructor
  virtual ~Nestea_i (void);

  /// Add <cans> number of cans to the bookshelf.
  virtual void drink (CORBA::Long cans,
                      CORBA::Environment &ACE_TRY_ENV =
                        TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Removes <cans> number of cans from the bookshelf.
  virtual void crush (CORBA::Long cans,
                      CORBA::Environment &ACE_TRY_ENV =
                        TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Returns the number of cans in the bookshelf.
  virtual CORBA::Long bookshelf_size (CORBA::Environment &ACE_TRY_ENV =
                                        TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Returns comments about your collection.
  virtual char *get_praise (CORBA::Environment &ACE_TRY_ENV = 
                              TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Saves bookshelf data to a file.
  int save_data (void);

  /// Loads bookshelf data from a file.
  int load_data (void);

  /// The name of the file to store the data in.
  char *data_filename_;

  /// Number of cans in the bookshelf.
  ACE_UINT32 cans_;
};

#endif /* NESTEA_I_H */

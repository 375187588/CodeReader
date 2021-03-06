// Service_Type_Exporter.h,v 1.8 1999/06/30 08:19:35 nanbor Exp

// ========================================================================
//
// = FILE
//     Offer_Exporter.h
//
// = DESCRIPTION
//    Class that tests the Trading Service's Service Type Repository
//
// = AUTHOR
//     Seth Widoff <sbw1@cs.wustl.edu>
//
// =======================================================================

#ifndef TAO_SERVICE_TYPE_EXPORTER_H
#define TAO_SERVICE_TYPE_EXPORTER_H

#include "TT_Info.h"

class TAO_Service_Type_Exporter
{
public:

  TAO_Service_Type_Exporter (CosTrading::Lookup_ptr lookup_if,
                             CORBA::Boolean verbose,
                             CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void remove_all_types (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosTrading::IllegalServiceType,
                     CosTrading::UnknownServiceType,
                     CosTradingRepos::ServiceTypeRepository::HasSubTypes));
  // Remove all service types from the trading service instance.

  void add_all_types (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosTrading::IllegalServiceType,
                     CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
                     CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
                     CosTrading::IllegalPropertyName,
                     CosTrading::DuplicatePropertyName,
                     CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                     CosTrading::UnknownServiceType,
                     CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
  // Add all the generated service types to the trading service instance.

  void add_all_types_to_all (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosTrading::IllegalServiceType,
                     CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
                     CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
                     CosTrading::IllegalPropertyName,
                     CosTrading::DuplicatePropertyName,
                     CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                     CosTrading::UnknownServiceType,
                     CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
  // Add all the generated service types to all the trading service
  // instances linked to the trading service we bootstrapped to.

  void list_all_types (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // List all the service types registered with the trading service
  // instance.

  void describe_all_types (CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   CosTrading::IllegalServiceType,
                   CosTrading::UnknownServiceType));
  // Describe all the service types registered with the trading
  // service instance.

  void fully_describe_all_types (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosTrading::IllegalServiceType,
                     CosTrading::UnknownServiceType));
  // Same as describe_all_types, but fully describe lists the
  // properties of all service types the described service type
  // inherits from.

private:

  void create_types (void);
  // Generate the service type description structures.

  void add_all_types_to (CosTradingRepos::ServiceTypeRepository_ptr repos,
                         CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosTrading::IllegalServiceType,
                     CosTradingRepos::ServiceTypeRepository::ServiceTypeExists,
                     CosTradingRepos::ServiceTypeRepository::InterfaceTypeMismatch,
                     CosTrading::IllegalPropertyName,
                     CosTrading::DuplicatePropertyName,
                     CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition,
                     CosTrading::UnknownServiceType,
                     CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName));
  // Add all types to a sepcified service type repository reference.

  void
  dump_typestruct (const char* type_name,
                   const CosTradingRepos::ServiceTypeRepository::TypeStruct& type_struct) const;
  // Dump the contents of a service type description to standard
  // output.

  CORBA::Boolean verbose_;
  // True if the user want profuse output.

  CosTrading::Lookup_ptr lookup_;
  // A reference to the lookup interface of the trading service
  // instance.

  CosTradingRepos::ServiceTypeRepository_var repos_;
  // A reference to a service type repository instance.

  CosTradingRepos::ServiceTypeRepository::TypeStruct type_structs_[NUM_TYPES];
  // Descriptions of all the service types whose property names are
  // defined in TT_Info.
};

#endif /* TAO_SERVICE_TYPE_EXPORTER_H */

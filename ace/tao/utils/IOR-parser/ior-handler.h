// ior-handler.h,v 1.4 1999/12/14 15:44:50 schmidt Exp

// ============================================================================
//
// = LIBRARY
//    TAO/utils/IOR-parser
//
// = FILENAME
//    ior-handler.h
//
// = DESCRIPTION
//    Provides the definition of a class that parses real (valid) IORs.
//
// = AUTHORS
//    Priya Narasimhan <priya@lambda.ece.ucsb.edu>
//
// ============================================================================

#ifndef __IORPARSER_H__
#define __IORPARSER_H__

#include "ace/OS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Basic_Types.h"    // To determine BYTE_ORDER

// Maximum length of the stringified IOR, the type_id, and the
// object_key and hostname fields. Tentatively assigned.
#define MAX_IOR_LEN         600
#define MAX_IOR_FIELD_LEN   200
#define MAX_TYPE_ID_LEN     100
#define MAX_OBJ_KEY_LEN     100
#define MAX_HOSTNAME_LEN     64

struct IOR
{
  // = TITLE
  //     This is the useful information obtained from parsing an IOR.
  //
  // = DESCRIPTION
  //     This structure assumes that the profile_id is
  //     TAG_INTERNET_IOP and that there is only one TaggedProfile in
  //     the IOR.
public:
  u_long typeIdLen;
  // The length of the type_id field of the IOR

  char typeId[MAX_TYPE_ID_LEN];
  // The string in the type_id field of the IOR

  char idlInterface[MAX_TYPE_ID_LEN];
  // The IDL interface of the server that published the IOR (can be extracted
  // from the type_id field)

  u_long profileBodyLen;
  // The length of the body of the profile field of the IOR

  u_long hostLen;
  // The length of the hostname embedded in the IOR

  char HostName[MAX_HOSTNAME_LEN];
  // The server's hostname embedded in the IOR

  u_long portNum;
  // The server's port number embedded in the IOR

  u_long objectKeyLen;
  // The length of the object_key field of the IOR

  char objectKey[MAX_OBJ_KEY_LEN];
  // The object_key field of the IOR
};

class IorHandler
{
  // = TITLE
  //     This is the class that takes in a real (valid) IOR and
  //     parses it.
  //
  // = DESCRIPTION
  //     This class prints out the useful information in the
  //     IORs generated by VisiBroker, Orbix and TAO
public:
  IorHandler (void);
  // Constructor

  void interpretIor (char *thisIor, struct IOR *thisIorInfo);
  // The main IOR parsing routine

  char *getIdlInterface (char *typeId, int *validTypeId);
  // Extracts the IDL interface from the type_id field in the IOR

  void readIorFromFile (char *filename);
  // Reads in the IOR from a specified file

  char stringIOR[MAX_IOR_LEN];
  // Holds the stringified IOR during parsing

  struct IOR parsedIOR;
  // Holds the parsed IOR

private:
  int hexChar2int (char thisChar);
  // Converts a pair of hexadecimal-encoded characters in the stringified
  // IOR into their integer value

  u_long getOctet8Field (char *readPtr, int *hexCharsRead);
  // Interpret the next 8 octets into an unsigned long

  u_long getOctet4Field (char *readPtr, int *hexCharsRead);
  // Interpret the next 4 octets into an unsigned long

  u_long getOctet2Field (char *readPtr, int *hexCharsRead);
  // Interpret the next 2 octets into an unsigned long

  void skipSpaceIfAny (char *readPtr, int *hexCharsRead);
  // Skip the space character encountered while parsing the IOR

  void skipNullOctets (char *readPtr, int *hexCharsRead, int expectingStr);
  // Skip the null octets encountered while parsing the IOR

  int findIfVisiIor (char *readPtr, int *hexCharsRead);
  // Finds out if VisiBroker generated this IOR

  char getCharacter (char *readPtr, int *offset);
  // Extracts a single character from the IOR

  char *getString (char *readPtr, int givenLen);
  // Extracts a character string of a given length from the IOR

};

#endif /* __IORPARSER_H__ */

// test_SV.cpp,v 4.6 2001/05/09 18:35:28 schmidt Exp

#include "ace/Shared_Memory_SV.h"
#include "ace/Log_Msg.h"

ACE_RCSID(Shared_Memory, test_SV, "test_SV.cpp,v 4.6 2001/05/09 18:35:28 schmidt Exp")

#define SHMSZ 27
#define SHM_KEY (key_t) 5678

static void
client (void)
{
  ACE_Shared_Memory_SV shm_client (SHM_KEY, SHMSZ);
  char *shm = (char *) shm_client.malloc ();

  for (char *s = shm; *s != '\0'; s++)
    putchar (*s);

  putchar ('\n');
  *shm = '*';
}

static void
server (void)
{
  ACE_Shared_Memory_SV shm_server (SHM_KEY, SHMSZ, 
				   ACE_Shared_Memory_SV::ACE_CREATE);
  char *shm = (char *) shm_server.malloc ();
  char *s   = shm;

  for (char c = 'a'; c <= 'z'; c++)
    *s++ = c;

  *s = '\0';

  while (*shm != '*')
    ACE_OS::sleep (1);

  if (shm_server.remove () < 0)
    ACE_ERROR ((LM_ERROR, "%p\n", "remove"));
}

int
main (int, char *[])
{
  switch (ACE_OS::fork ())
    {
    case -1:
      ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "fork"), 1);
    case 0: 
      // Make sure the server starts up first.
      ACE_OS::sleep (1); 
      client ();
      break;
    default:
      server ();
      break;
    }

  return 0;
}


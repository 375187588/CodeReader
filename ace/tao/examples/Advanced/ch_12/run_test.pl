eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.1 1999/08/24 21:35:18 mm4 Exp
# -*- perl -*-

use lib "../../../../bin";

require ACEutils;
require Process;

$status = 0;
$iorfile = "chapter_test.ior";
unlink $iorfile;



# Hacked call
$server = Process::Create ("exec ".$EXEPREFIX."server".$EXE_EXT.">$iorfile",
                           "");
# Proper call
#$server = Process::Create ($EXEPREFIX."server".$EXE_EXT, ">$iorfile");

if (ACE::waitforfile_timed ($iorfile, 15) == -1) {
  print STDERR "ERROR: timedout waiting for file <$iorfile>\n";
  $server->Kill (); $server->TimedWait (1);
  exit 1;
}

open(ior_handle, "$iorfile");
$ior_content = <ior_handle>;

$client = Process::Create($EXEPREFIX."client$EXE_EXT", "$ior_content");

if ($client->TimedWait (60) == -1) {
  print STDERR "ERROR: client timedout\n";
  $status = 1;
  $client->Kill (); $client->TimedWait (1);
}




$server->Terminate (); 
if ($server->TimedWait (5) == -1) {
  print STDERR "ERROR: cannot terminate the server\n";
  $server->Kill (); $server->TimedWait (1);
  $status = 1;
}

unlink $iorfile;

exit $status;

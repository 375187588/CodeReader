eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# run_test.pl,v 1.3 2001/08/28 13:25:54 oci Exp
# -*- perl -*-

use lib '../../../bin';
use PerlACE::Run_Test;

$iorfile = PerlACE::LocalFile ("server.ior");
unlink $iorfile;
$status = 0;

foreach $i ("-n", "-t", "-s", "-r") {
  $SV = new PerlACE::Process ("server", "-o $iorfile");
  $CL = new PerlACE::Process ("client", " -k file://$iorfile $i");

  $SV->Spawn ();

  if (PerlACE::waitforfile_timed ($iorfile, 10) == -1) {
    print STDERR "ERROR: cannot find file <$iorfile>\n";
    $SV->Kill (); $SV->TimedWait (1);
    exit 1;
  }

  $client = $CL->SpawnWaitKill (200);

  if ($client != 0) {
    print STDERR "ERROR: client returned $client\n";
    $status = 1;
  }

  $server = $SV->WaitKill (10);

  if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
  }

  unlink $iorfile;
}

exit $status;

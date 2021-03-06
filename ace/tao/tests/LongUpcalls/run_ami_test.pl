eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# run_ami_test.pl,v 1.2 2001/07/07 03:06:42 bala Exp
# -*- perl -*-

use lib '../../../bin';
use PerlACE::Run_Test;

$iorfile = PerlACE::LocalFile ("server.ior");
unlink $iorfile;

$SV  = new PerlACE::Process ("ami_server", "-o $iorfile");
$CL = new PerlACE::Process ("ami_client", " -k file://$iorfile");

print STDERR "Running the ami tests that used to block \n";
$SV->Spawn ();

if (PerlACE::waitforfile_timed ($iorfile, 15) == -1) {
    print STDERR "ERROR: cannot find file <$iorfile>\n";
    $SV->Kill (); $SV->TimedWait (1);
    exit 1;
}

$CL->Spawn (60);

$client = $CL->WaitKill (60);

if ($client1 != 0) {
    print STDERR "ERROR: client 1 returned $client1\n";
    $status = 1;
}


$server = $SV->TerminateWaitKill (5);

if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
}

unlink $iorfile;

exit $status;

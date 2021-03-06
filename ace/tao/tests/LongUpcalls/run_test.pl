eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.3 2001/05/08 03:31:14 coryan Exp
# -*- perl -*-

use lib '../../../bin';
use PerlACE::Run_Test;

$status = 0;

$iorfile = PerlACE::LocalFile ("test.ior");
$svcfile = PerlACE::LocalFile ("svc.conf");

$BSV = new PerlACE::Process ("blocking_server", "-ORBSvcConf $svcfile -o $iorfile");
$ASV = new PerlACE::Process ("ami_server", "-ORBSvcConf $svcfile -o $iorfile");
$BCL = new PerlACE::Process ("blocking_client", "-ORBSvcConf $svcfile -k file://$iorfile");

print STDERR "==== Server upcall waits for operations on other threads\n";

unlink $iorfile;

$BSV->Spawn ();

if (PerlACE::waitforfile_timed ($iorfile, 30) == -1) {
    print STDERR "ERROR: cannot find file <$iorfile>\n";
    $BSV->Kill ();
    exit 1;
}

$client = $BCL->SpawnWaitKill (240);

if ($client != 0) {
    print STDERR "ERROR: client returned $client\n";
    $status = 1;
}

$server = $BSV->WaitKill (30);

if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
}

print STDERR "==== Server upcall waits for AMI operations on other threads\n";

unlink $iorfile;
$ASV->Spawn ();

if (PerlACE::waitforfile_timed ($iorfile, 30) == -1) {
    print STDERR "ERROR: cannot find file <$iorfile>\n";
    $ASV->Kill ();
    exit 1;
}

$client = $BCL->SpawnWaitKill (30);

if ($client != 0) {
    print STDERR "ERROR: client returned $client\n";
    $status = 1;
}

$server = $ASV->WaitKill (30);

if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
}

unlink $iorfile;

exit $status;

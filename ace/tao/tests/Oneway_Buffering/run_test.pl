eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# run_test.pl,v 1.3 2001/08/28 13:25:54 oci Exp
# -*- perl -*-

use lib '../../../bin';
use PerlACE::Run_Test;

$admin_iorfile = PerlACE::LocalFile ("admin.ior");
$server_iorfile = PerlACE::LocalFile ("server.ior");
$status = 0;

foreach $test_type ("-c", "-t", "-b", "-r") {
  unlink $admin_iorfile;
  unlink $server_iorfile;

  my $AD = new PerlACE::Process ("admin", "-o $admin_iorfile");
  my $SV = new PerlACE::Process ("server", "-o $server_iorfile " .
                                           "-k file://$admin_iorfile");
  my $CL = new PerlACE::Process ("client",
				 " -k file://$server_iorfile "
				 ."-a file://$admin_iorfile "
				 .$test_type);

  $AD->Spawn ();

  if (PerlACE::waitforfile_timed ($admin_iorfile, 10) == -1) {
    print STDERR "ERROR: cannot find file <$admin_iorfile>\n";
    $AD->Kill (); $AD->TimedWait (1);
    exit 1;
  }

  $SV->Spawn ();

  if (PerlACE::waitforfile_timed ($server_iorfile, 10) == -1) {
    print STDERR "ERROR: cannot find file <$server_iorfile>\n";
    $AD->Kill (); $AD->TimedWait (1);
    $SV->Kill (); $SV->TimedWait (1);
    exit 1;
  }

  $client = $CL->SpawnWaitKill (300);

  if ($client != 0) {
    print STDERR "ERROR: client returned $client\n";
    $status = 1;
  }

  $server = $SV->WaitKill (10);

  if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
  }

  $admin = $AD->WaitKill (10);

  if ($admin != 0) {
    print STDERR "ERROR: admin returned $admin\n";
    $status = 1;
  }
}

unlink $server_iorfile;
unlink $admin_iorfile;

exit $status;

eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.27 2001/09/06 20:00:05 doccvs Exp
# -*- perl -*-

# This is a Perl script that runs all Naming Service tests.  It starts
# all the servers and clients as necessary.

use lib '../../../../bin';
use PerlACE::Run_Test;

# Amount of delay (in seconds) between starting a server and a client
# to allow proper server initialization.
$sleeptime = 8;

$quiet = 0;

# check for -q flag
if ($ARGV[0] eq '-q') {
    $quiet = 1;
}

# Variables for command-line arguments to client and server
# executables.
$ns_multicast_port = 10001 + PerlACE::uniqueid (); # Can not be 10000 on Chorus 4.0
$ns_orb_port = 12000 + PerlACE::uniqueid ();
$iorfile = PerlACE::LocalFile ("ns.ior");
$persistent_ior_file = PerlACE::LocalFile ("pns.ior");
$persistent_log_file = PerlACE::LocalFile ("test_log");
$data_file = PerlACE::LocalFile ("test_run.data");

$status = 0;

sub name_server
{
    my $args = "@_ "."-ORBNameServicePort $ns_multicast_port -o $iorfile -m 1";
    my $prog = "../../Naming_Service/Naming_Service";

    $NS = new PerlACE::Process ($prog, $args);

    unlink $iorfile;

    $NS->Spawn ();

    if (PerlACE::waitforfile_timed ($iorfile, $sleeptime) == -1) {
        print STDERR "ERROR: cannot find IOR file <$iorfile>\n";
        $NS->Kill (); 
        exit 1;
    }
}

sub client
{
    my $args = "@_"." ";
    my $prog = "client";

    $CL = new PerlACE::Process ($prog, $args);

    $client = $CL->SpawnWaitKill (60);

    if ($client != 0) {
        print STDERR "ERROR: client returned $client\n";
        $status = 1;
    }
}

# Options for all simple tests recognized by the 'client' program.
@opts = ("-s -ORBInitRef NameService=file://$iorfile",
         "-s -ORBInitRef NameService=mcast://:$ns_multicast_port\::/NameService",
         "-t -ORBInitRef NameService=file://$iorfile",
         "-i -ORBInitRef NameService=file://$iorfile",
         "-e -ORBInitRef NameService=file://$iorfile",
         "-y -ORBInitRef NameService=file://$iorfile",
         "-p $persistent_ior_file -ORBInitRef NameService=file://$iorfile",
         "-c file://$persistent_ior_file -ORBInitRef NameService=file://$iorfile");

@server_opts = ("", "", "", "", "", "",
                "-ORBEndpoint iiop://$TARGETHOSTNAME:$ns_orb_port -f $persistent_log_file",
                "-ORBEndpoint iiop://$TARGETHOSTNAME:$ns_orb_port -f $persistent_log_file");

@comments = ("Simple Test: \n",
             "Simple Test (using multicast to locate the server): \n",
             "Tree Test: \n",
             "Iterator Test: \n",
             "Exceptions Test: \n",
             "Destroy Test: \n",
             "Persistent Test (Part 1): \n",
             "Persistent Test (Part 2): \n");

$test_number = 0;

unlink $persistent_ior_file, $persistent_log_file;

# Run server and client for each of the tests.  Client uses ior in a
# file to bootstrap to the server.
foreach $o (@opts) {
    name_server ($server_opts[$test_number]);

    print STDERR "\n          ".$comments[$test_number];

    client ($o);

    $NS->Kill ();
    $test_number++;
}

unlink $persistent_ior_file, $persistent_log_file;

# Now run the multithreaded test, sending output to the file.
print STDERR "\n          Multithreaded Test:\n";
unlink $data_file;

open (OLDOUT, ">&STDOUT");
open (STDOUT, ">$data_file") or die "can't redirect stdout: $!";
open (OLDERR, ">&STDERR");
open (STDERR, ">&STDOUT") or die "can't redirect stderror: $!";

# just here to quiet warnings
$fh = \*OLDOUT;
$fh = \*OLDERR;

name_server ();

client ("-ORBInitRef NameService=file://$iorfile", "-m15");

close (STDERR);
close (STDOUT);
open (STDOUT, ">&OLDOUT");
open (STDERR, ">&OLDERR");

$NS->Kill ();

unlink $iorfile;


$errors = system ("perl process-m-output.pl $data_file 15") >> 8;

if ($errors > 0) {
    $status = 1;

    if (!$quiet) {
        print STDERR "Errors Detected, printing output\n";
        if (open (DATA, "<$data_file")) {
            print STDERR "================================= Begin\n";
            print STDERR <DATA>;
            print STDERR "================================= End\n";
            close (DATA);
        }
        else {
            print STDERR "ERROR: Could not open $data_file\n";
        }
        unlink $data_file;
    }
}

unlink $iorfile;

exit $status;

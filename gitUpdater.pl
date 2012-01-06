#! /usr/bin/perl


use File::stat;
use Time::localtime;
use Data::Dumper;

my $startTime = time();

my @previousList;

sub list {

	my ($dir) = @_;
	return unless -d $dir;

	my @files;
	if (opendir my $dh, $dir) {
		my @list;
		my $file;

		while ($file = readdir $dh) { 
			push @list, $file;
		}

		closedir $dh;

		for $file (@list) {
			next if $file eq '.' || $file eq '..';

			push @files, "$dir/$file" if -f "$dir/$file";
			push @files, list ("$dir/$file") if -d "$dir/$file";
		}
	}

	return @files;
}


sub checkDate {
	open FILE, $_;


	if ($startTime < stat(FILE)->mtime) {
		update();	
	}

}

sub update {

	system("git commit -a -m \"update\"");
	system("git push -u origin master");

	$startTime = time();
}


@previousList = list("/home/shower/hades_software");


while (true) {
	my @t = list("/home/shower/hades_software");

	if(scalar(@t) != scalar(@previousList)) { system("git add ."); }
	
	checkDate($_) for list ("/home/shower/hades_software");

	print "sleep\n";
	sleep(20);
}



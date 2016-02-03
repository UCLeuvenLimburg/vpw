#!/usr/bin/perl
use 5.18.0;
use strict;
use warnings;

my $cases = <STDIN>;

for my $case (1..$cases){
    my $line = <STDIN>
    my ($x, $word) = split " ", $line;
    print substr($word, $x -1, 1) . "\n";
}
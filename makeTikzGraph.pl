#!/usr/bin/perl

use strict;
use warnings;
use Math::Trig;
use Text::Template;

# open up a variable as a file for easy output of latex code
my $tikz;
open(my $fh, '>', \$tikz) or die "Failed to open pipe: $!";

# REPL of the graph which is just a csv
my $last = 'A';
my $color = getRndStr();
print $fh "\\definecolor{", $color, "}{rgb}{", getRndRGB() , ',',
    getRndRGB(), ',', getRndRGB(), "}\n";
while(<>){
    chomp;
    my @arr = split /,/;
    if(!($arr[0] eq $arr[1])){
        print $fh "\\Edge[label=", $arr[2], ',style={', $color,
            ',->,thick}](', $arr[0], ")(", $arr[1], ")\n";
    }else{
        my @dir = direction($arr[0]);
        print $fh "\\Loop[dist=10cm, dir=", $dir[0], ", label=",
            $arr[2], ',style={', $color, ',->,very thick}](',
            $arr[0], ".", $dir[1], ")\n";
    }
    # change color on letter change
    if(!($last eq $arr[0])){
        $color = getRndStr();
        print $fh "\\definecolor{", $color, "}{rgb}{", getRndRGB() , ',',
            getRndRGB(), ',', getRndRGB(), "}\n";
    }
    $last = $arr[0];
}
close $fh;

# Fill in the LaTeX templete
my $TemplateString = do{local $/; <main::DATA>};
my $templ = Text::Template->new(
    SOURCE => $TemplateString,
    TYPE => 'string',
    DELIMITERS => ['{!', '!}']
);
my %vars = (
    tikzPictureString => \$tikz,
    graphUnit => '18'
);
my $result = $templ->fill_in(HASH => \%vars);
print $result;

sub direction {
    #$_ = (ord($_) - ord('A'));
    #return ('NO', 'north') if($_ >= 0 && $_ <= 13);
    #return ('SO', 'south') if($_ > 13);
    $_ = (2 * pi * ((ord($_) - ord('A')) / 26));
    return ('EA','east') if (($_ >= 7*pi/4 && $_ <= 2*pi) or ($_ >= 0 && $_ < pi/4));
    return ('NO', 'north') if ($_ >= (pi/4) &&  $_ <= (3*pi/4));
    return ('WE', 'west') if ($_ >= (3*pi/4) && $_ <= (5*pi/4));
    return ('SO', 'south') if ($_ >= (5*pi/4) && $_ <= (7*pi/4));
}

sub getRndStr {
    my $string;
    for (0..7) { $string .= chr( int(rand(25) + 65) ); }
    return $string;
}

sub getRndRGB {
    return rand() * 0.45  + 0.25;
}

__DATA__
\documentclass[border=10pt]{standalone}

\usepackage{color}
\usepackage{tkz-graph}

\tikzset{
  LabelStyle/.style = { rectangle, rounded corners, draw,
                        minimum width = 1em, fill = yellow!50,
                        text = red, font = \bfseries },
  VertexStyle/.append style = { inner sep=3pt,
                                font = \Large\bfseries},
  EdgeStyle/.append style = {->} }
\thispagestyle{empty}
\begin{document}
\begin{tikzpicture}
  \SetGraphUnit{{! $graphUnit !}}
  \Vertices{circle}{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}
  {! $tikzPictureString !}
\end{tikzpicture}
\end{document}

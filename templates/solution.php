<?PHP
$nrOfTestcases = trim(fgets(STDIN));
for ($i=0;$i<$nrOfTestcases;$i++)
{
        $line = trim(fgets(STDIN));
        $words = explode(" ", $line, 2);
        print $words[1][$words[0]-1] . "\n";
}
?>
{$mode objfpc}
{$h+}

uses
  sysutils, classes;

var
  aantal,
  i,
  letternr : longint;
  lijn, woord: string;
  delen: tstringlist;
begin
  readln(aantal);
  for i := 1 to aantal do
    begin
      // onderstaande kan in dit geval eenvoudigweg worden vervangen door
      // "readln(letternr,woord)", maar dat werkt enkel als de string op het
      // einde van de lijn komt. Deze manier werkt in alle gevallen waar
      // spatie als scheidingsteken wordt gebruikt.
      readln(lijn);
      delen:=tstringlist.create;
      extractstrings([' '],[],pchar(lijn),delen);
      letternr:=strtoint(delen[0]);
      woord:=delen[1];
      // schrijf de gevraagde letter uit
      writeln(woord[letternr]);
    end;
end.
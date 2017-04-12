program err18b;
  var a,b,c: integer;
begin
 c:= 4213;
 a:= funcionNoDef();
 case a of
  1,2: b:= 0;
  c: procNoDef;
{tiene q ir un nro, no un id(c)}

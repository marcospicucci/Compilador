program ej3; {ejemplo extraido de la teoría de MEPA}
 var k:integer;
  procedure p(n:integer;g:integer);
   var h:integer;
  begin
   if n<2 then 
    h:=g+n
   else 
    begin
     h:=g;
     p(n-1,h);
     k:=h;
     p(n-2,g)
    end;
  write(n);
  write(g)
  end;
begin
k:=0; 
p(3,k)
end.

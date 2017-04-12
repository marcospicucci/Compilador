program ej5;{ejemplo extraido de la teoría de MEPA}
 var m:integer;
  function f(n:integer;k:integer):integer;
   var p,q:integer;
  begin
   if n<2 then
    begin 
     q:= -1; 
     f:=n; 
     p:=0 
    end
   else 
    begin
     f:= f(n-1,p)+f(n-2,q);
     p:= p+q+1
    end;
  write(n);
  write(k)
  end;
begin
 read(m);
 write(f(3,m));
 write(m)
end.

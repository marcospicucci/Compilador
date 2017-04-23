program ej7;
 var a: integer;
 
 function factorial(x:integer):integer;
  begin
   if x > 0 then
    factorial := x * factorial(x-1)
   else
    factorial := 1
  end;
  
begin
 read(a);
 write(factorial(a))
end.

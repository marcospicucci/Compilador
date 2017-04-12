program ej4;
 var x:integer; 
  procedure p1(v:integer);
   var f,g:integer;	
    function f1:integer;
     begin
	  f1:= g*12 -(-1/f)
     end;
    function f2:integer;
     function f1: boolean; {puedo usar f1 como id}
      begin    
       f1:= -(-g) <> 0
      end;
    begin {de f2}
     if f1() then
      f2:= f*24 /(5)
     else
      f2 := --maxint
    end;  
  begin {de p1}
   f:= f2() / f1();
   write(f)
  end;
begin {de ej4}
 read(x);
 p1(x)
end.

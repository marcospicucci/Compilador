program ej3;{anidados}
 var x,y:integer;
  function f1(a,b:boolean;c:integer):integer;
	var x:boolean;{redefine x}
	 procedure p1;
	  var k,j:integer;		
		procedure p2;
		begin
		  k:= 22 {k de p1}
		end;
		procedure p3;
		 begin
		   j:= 33 {j de p1}
		 end;		
	 begin {de p1}
	  k:= k + j;
	  x:= succ(y) <> 0; {x de f1 y de pp}
	  p3();
	  write(j*5)
	 end;	
  begin {de f1}
   x := (y<>0+c) or (a and b);
   p1();
   f1:= c
  end;	
begin
 read(x);
 y:= f1(false,false,x)
end.

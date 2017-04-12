program ej4;{anidados}
  var x, y: integer;
   function f1(a,b:boolean; c:integer): integer;
	 var x:boolean;		
	  procedure p1;
		var k,j:integer;		
		 procedure p2;
		 begin
		   k:= 22
		 end;
		 procedure p3;
		 begin
		   j:= 33
		 end;		
	  begin {de p1}
	   k:= k + j
	  end;	
   begin {de f1}
	c:= 44	
   end;	
begin
 x:= f1(true,true,99)
end.	

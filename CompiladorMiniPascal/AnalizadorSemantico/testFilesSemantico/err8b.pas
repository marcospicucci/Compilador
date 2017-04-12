program err8b;
 var x,y:integer;
  procedure p1(a:integer);
   var q:integer;
    function f1(x:boolean):integer;
     var z:integer;
    begin
     q:=0;
     z := q;
     f1:= z
    end;   
 begin {de p1}  
  q:= f1(a>5);
  z:= 123;
  {z es local a f1}

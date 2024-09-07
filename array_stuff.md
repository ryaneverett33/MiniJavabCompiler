i32 Test_blah (%Test* %this)
%entry:
	%this.local = alloc %Test**
	store %Test* %this, %Test** %this.local
	%c = alloc i32*
    %0 = call mj.new_array(i32 5)
    store i32* %0, i32** %c
    %1 = load i32*, i32** %c
    %2 = call mj.array_length(i32* %1)
    ret i32 %2
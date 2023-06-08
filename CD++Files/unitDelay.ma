[top]
components : unitDelay@UnitDelay

in : theIn
out : theOut

Link : theIn theIn@unitDelay
Link : theOut@unitDelay theOut


[unitDelay]
distribution : normal
mean : 2
deviation : 1


[top]
components : genControl@GenControl

in : Yrin Ypin Ypdin Em1in Em2in Em3in
out : Uout

Link : Yrin Yrin@genControl
Link : Ypin Ypin@genControl
Link : Ypdin Ypdin@genControl
Link : Em1in Em1in@genControl
Link : Em2in Em2in@genControl
Link : Em3in Em3in@genControl
Link : Uout@genControl Uout


[genControl]
distribution : normal
mean : 2
deviation : 1


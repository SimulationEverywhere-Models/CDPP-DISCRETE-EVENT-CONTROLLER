[top]
components : model3@Model3

in : Uin Ypin Ypdin Ypddin 
out : Ymout Eout

Link : Uin Uin@model3
Link : Ypin Ypin@model3
Link : Ypdin Ypdin@model3
Link : Ypddin Ypddin@model3
Link : Ymout@model3 Ymout
Link : Eout@model3 Eout


[model3]
distribution : normal
mean : 2
deviation : 1


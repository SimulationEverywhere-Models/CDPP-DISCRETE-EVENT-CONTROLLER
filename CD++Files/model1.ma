[top]
components : model1@Model1

in : Uin Ypin Ypdin Ypddin 
out : Ymout Eout

Link : Uin Uin@model1
Link : Ypin Ypin@model1
Link : Ypdin Ypdin@model1
Link : Ypddin Ypddin@model1
Link : Ymout@model1 Ymout
Link : Eout@model1 Eout


[model1]
distribution : normal
mean : 2
deviation : 1


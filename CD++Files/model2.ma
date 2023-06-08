[top]
components : model2@Model2

in : Uin Ypin Ypdin Ypddin 
out : Ymout Eout

Link : Uin Uin@model2
Link : Ypin Ypin@model2
Link : Ypdin Ypdin@model2
Link : Ypddin Ypddin@model2
Link : Ymout@model2 Ymout
Link : Eout@model2 Eout


[model2]
distribution : normal
mean : 2
deviation : 1


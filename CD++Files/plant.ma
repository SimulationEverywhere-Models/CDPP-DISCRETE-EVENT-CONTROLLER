[top]
components : plant@Plant

in : Uin Ypdin Ypddin Trigger plantState
out : Ypout

Link : Uin Uin@plant
Link : Ypdin Ypdin@plant
Link : Ypddin Ypddin@plant
Link : Trigger Trigger@plant
Link : plantState plantState@plant
Link : Ypout@plant Ypout

[plant]
distribution : normal
mean : 2
deviation : 1


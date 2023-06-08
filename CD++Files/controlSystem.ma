[top]
components : ControlSystem
in : Yrin xTin plantState
out : Ypout modelSelect observeU
Link : Yrin Yrin@controlSystem
Link : xTin xTin@controlSystem
Link : plantState plantState@controlSystem
Link : Ypout@controlSystem Ypout
Link : modelSelect@controlSystem modelSelect
Link : observeU@controlSystem observeU



[ControlSystem]
components : plant1@Plant interpLast1@InterpLast interpLast2@InterpLast genControl1@GenControl unitDelay1@UnitDelay model1@Model1 model2@Model2 model3@Model3
in : Yrin xTin plantState
out : Ypout modelSelect observeU

Link : plantState plantState@plant1
Link : Uout@genControl1 Uin@plant1
Link : xTin theIn@unitDelay1
Link : theOut@unitDelay1 Trigger@plant1
Link : xTin xTin@interpLast1
Link : xdout@interpLast1 Ypdin@plant1
Link : xddout@interpLast1 Ypddin@plant1
Link : Ypout@plant1 evXin@interpLast1
Link : Yrin Yrin@genControl1
Link : Ypout@plant1 Ypin@genControl1
Link : xdout@interpLast1 Ypdin@genControl1

Link : Uout@genControl1 Uin@model1
Link : Uout@genControl1 Uin@model2
Link : Uout@genControl1 Uin@model3
Link : Ypout@plant1 Ypin@model1 
Link : Ypout@plant1 Ypin@model2 
Link : Ypout@plant1 Ypin@model3 
Link : Ypout@plant1 evXin@interpLast2
Link : theOut@unitDelay1 xTin@interpLast2
Link : xdout@interpLast2 Ypdin@model1
Link : xdout@interpLast2 Ypdin@model2
Link : xdout@interpLast2 Ypdin@model3
Link : xddout@interpLast2 Ypddin@model1
Link : xddout@interpLast2 Ypddin@model2
Link : xddout@interpLast2 Ypddin@model3
Link : Eout@model1 Em1in@genControl1
Link : Eout@model2 Em2in@genControl1
Link : Eout@model3 Em3in@genControl1
Link : Uout@genControl1 observeU
//Link : Ypout@plant1 Ypout
//Link : modelSelect@genControl1 modelSelect

[plant1]
distribution : normal
mean : 2
deviation : 1

[interpLast1]
distribution : normal
mean : 2
deviation : 1

[genControl1]
distribution : normal
mean : 2
deviation : 1

[unitDelay1]
distribution : normal
mean : 2
deviation : 1

[interpLast2]
distribution : normal
mean : 2
deviation : 1

[model1]
distribution : normal
mean : 2
deviation : 1

[model2]
distribution : normal
mean : 2
deviation : 1

[model3]
distribution : normal
mean : 2
deviation : 1



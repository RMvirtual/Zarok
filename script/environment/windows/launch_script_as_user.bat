@ECHO OFF
SET user_login=%USERDOMAIN%\%USERNAME% 
RUNAS /profile /user:%user_login%  "CMD /k %~1 %2 %3"
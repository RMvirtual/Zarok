@ECHO OFF
SET user_login=%USERDOMAIN%\%USERNAME% 
RUNAS /noprofile /user:%user_login%  "CMD /k %~1"
@echo off

javac -cp .;jna-5.2.0.jar com/test/*.java

jar -cvf LibOpusInterface.jar com/test/*.class

del com\test\*.class

pause


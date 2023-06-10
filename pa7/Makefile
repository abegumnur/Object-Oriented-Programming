JC = javac
R = java
SUPER = BegumNur_interface/*.java
SUB = BegumNur_src/*.java
JFlags =
Classes =

muo:
	$(JC) $(JFlags) $(SUPER) $(SUB) Test.java
	$(R) Test

javadoc:
	javadoc BegumNur_interface/*.java BegumNur_src/*.java -d javadoc

clean:
	rm BegumNur_interface/*.class BegumNur_src/*.class *.class javadoc/ -r

// Lecture 26 | Wednesday, Week 10

// class Class, Type Introspection and Reflection

// the class Object has the method
public Class<?> getClass()
// the return type is java.lang.Class<?>
	// Remember that Class<?> is a superclass of Class<T> for any type T
	// the method signature says T.getClass() returns a Class<?>
	// specifically, it returns a Class<T>, but as a Class<?>
	// the class Class simply contains some information about the type

// find out what class your object is with getClass() and toString()
String s = "";
Class<?> c1 = s.getClass();
System.out.println(c1.getClass());
	// output class java.lang.String
// if we know s is a string and want the Class<String> object,
Class<String> c2 = (Class<String>) s.getCLass();
	// this is a narrowing reference conversion from the parent class Class<?> to the child class Class<String>

// in programming, "type introspection" is examining the type or properties of an object at runtime
// "Reflection", which goes one step further, is manipulating the values, metadata, properties and/or functions of an object at runtime
// C++ only supports type introspection and not reflection; Java supports both

// write a class with a method called printField()
class SomeClass {
	public int feld;
	public SomeClass(int field) {
		this.field = field;
	}
	public void printField() {
		System.out.println(field);
	}
}

// you can do "if a method named printField exists, call the method named printField"
public class Test {
	public static void main(String[] args) throws Exception {
		SomeClass obj = new SomeClass(4);
		Class<?> c = obj.getClass();
		try {
			Method m = c.getMethod("printField");	// creates a reference to the method named printField of Class<?> c, if any
				// getMethod can throw the NoSuchMethodException at runtime if the method does not exist
			m.invoke(obj);	// equivalent to saying "invoke that method m on this object obj"
		} catch (NoSuchMethodException e) {
			System.out.println("SomeClass does not have that method")
		}
	}

	// checking whether a method named printField exists is type introspection
	try {
		c.getMethod("printField");
	} catch (NoSuchMethodException e) {
		System.out.println("SomeClass does not ahve that method");
	}

	// calling the method named printField itself is reflection, as in the first try-catch block
}

// type introspection is a very useful debugging tool
// as a tool for production code, type introspection and reflection are advanced tools that are rarely helpful
// type introspection and reflection are interesting, but you should rarely use them outside of debugging

